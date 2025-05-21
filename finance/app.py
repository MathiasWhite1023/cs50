import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]
    rows = db.execute("""
    SELECT
        users.cash AS money,
        purchases.symbol,
        SUM(purchases.shares) AS total_shares,
        purchases.price,
        SUM(purchases.shares * purchases.price) AS total_invested
    FROM users
    JOIN purchases ON users.id = purchases.user_id
    WHERE users.id = ?
    GROUP BY purchases.symbol
""", user_id)

#O group by vai juntar todas as acoes com symbols iguais

    total_sum = 0
    for row in rows:
        quote = lookup(row["symbol"])
        row["price"] = round(quote["price"], 2)#ira atualizar os valores para os atuais
        row["total"] = round(row["price"] * row["total_shares"], 2)  #atualizara os totais tbm
        total_sum = round(total_sum + row["total"], 2)

    cash = round(rows[0]["money"], 2) if rows else 0

    total_dinheiro = round(total_sum + cash, 2) if rows else 0
    # Se o usuario nao tiver a acao, o valor dela sera 0

    return render_template("index.html", cash=cash, rows=rows, total_dinheiro=total_dinheiro)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":

        symbol_buy = request.form.get("symbol")
        result = lookup(symbol_buy)
        if result is None:
            return apology("This symbol does not exist", 400)

        shares_buy = request.form.get("shares")
        if not shares_buy or not shares_buy.isdigit() or int(shares_buy) <= 0:
            return apology("Shares must be a positive integer", 400)

        shares_buy = int(shares_buy)

        result = lookup(symbol_buy)
        total_shares = round(result["price"] * shares_buy, 2)

        user_id = session["user_id"]
        rows = db.execute("SELECT cash FROM users WHERE id = ?", user_id)

        if not rows:
            return apology("User not found", 400)

        cash = rows[0]["cash"]

        if cash < total_shares:
            return apology("Not enough money", 400)
        db.execute("INSERT INTO purchases (user_id, symbol, shares, price) VALUES (?, ?, ?, ?)", user_id, symbol_buy, shares_buy, result["price"])

        new_cash = round(cash - total_shares, 2)
        db.execute("UPDATE users SET cash = ? WHERE id = ?", new_cash, user_id)

        flash(f"Bought {shares_buy} shares of {symbol_buy} for ${total_shares:.2f}")

        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    user_id = session["user_id"]
    rows = db.execute("SELECT symbol, shares, price, timestamp FROM purchases WHERE user_id = ? ORDER BY timestamp DESC", user_id)

    return render_template("history.html", rows=rows)

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 400)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        #todo
        symbol = request.form.get("symbol")

        result = lookup(symbol)

        if result is None:
            return apology("This quote does not exist", 400)

        name = result["name"]
        price = result["price"]
        symbol = result["symbol"]

        return render_template("quoted.html", name=name, price=price, symbol=symbol )

    else:
        #todo GET
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username")
        if not username:
            return apology("must provide username", 400)

        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if not password or not confirmation:
            return apology("must provide password", 400)

        if password != confirmation:
            return apology("passwords must match", 400)

        hash_pass = generate_password_hash(password)

        try:
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash_pass)
        except ValueError:
                return apology("username already exists, try another one", 400)

        return render_template("login.html")

    else:
        return render_template("register.html")



@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():

    user_id = session["user_id"]

    # Recupera todas as ações que o usuário possui (para o GET e para preencher o select)
    rows = db.execute("""
        SELECT purchases.symbol,
               SUM(purchases.shares) AS total_shares
        FROM purchases
        WHERE user_id = ?
        GROUP BY purchases.symbol
    """, user_id)

    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        if not symbol or not shares:
            return apology("must provide symbol and shares", 400)

        try:
            shares = int(shares)
        except ValueError:
            return apology("shares must be a positive integer", 400)

        # Verifica quantas ações desse símbolo o usuário tem
        result = db.execute("""
            SELECT SUM(shares) as total_shares
            FROM purchases
            WHERE user_id = ? AND symbol = ?
        """, user_id, symbol)

        total_shares = result[0]["total_shares"] or 0
        if shares > total_shares:
            return apology("not enough shares", 400)

        quote = lookup(symbol) # Obtém o preço atual da ação
        if not quote:
            return apology("This symbol does not exist", 400)
        price = quote["price"]
        total = shares * price

        # Inserir a venda como shares negativos na tabela purchases
        db.execute("""
            INSERT INTO purchases (user_id, symbol, shares, price, timestamp)
            VALUES (?, ?, ?, ?, datetime('now'))
        """, user_id, symbol, -shares, price)

        # Atualizar o cash do usuário
        db.execute("""
            UPDATE users
            SET cash = cash + ?
            WHERE id = ?
        """, total, user_id)

        flash(f"Sold {shares} shares of {symbol} for ${total:.2f}")

        return redirect("/")

    else:
        # Renderiza o formulário com os símbolos disponíveis para o usuário vender
        return render_template("sell.html", rows=rows)
