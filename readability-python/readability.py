from cs50 import get_string

text = get_string("text: ")

Wor = 1
Sen = 0
Let = 0

# checks every caracter in text
for char in text:
    if char.isalnum():
        Let += 1
    elif char.isspace():
        Wor += 1
    elif char in ['.', '?', '!']:
        Sen += 1

L = (Let / Wor) * 100
S = (Sen / Wor) * 100
index = 0.0588 * L - 0.296 * S - 15.8

if index < 1:
    print("Before Grade 1")
elif index > 16:
    print("Grade 16+")
else:
    print("Grade", round(index))
