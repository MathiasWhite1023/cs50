from cs50 import get_float

cents = -1
while cents < 0:
    cents = get_float("change: ")

cents = round(cents * 100)

quarters = 0
while cents >= 25:
    quarters += 1
    cents = cents - 25

dimes = 0
while cents >= 10:
    dimes += 1
    cents = cents - 10

nickels = 0
while cents >= 5:
    nickels += 1
    cents = cents - 5

pennies = 0
while cents >= 1:
    pennies += 1
    cents = cents - 1

print(quarters + dimes + nickels + pennies)
