from cs50 import get_int

height = -1

while height <= 0 or height > 8:
    height = get_int("Height (0-8: ")

# add spaces with height-1
# by the end of that line star by
# adding 1 # and on the next add 1 # to the counter

i = 0
counter = 1
while i < height:
    print(" " * (height - 1), end="")
    print("#" * counter)
    height = height - 1
    counter = counter + 1
