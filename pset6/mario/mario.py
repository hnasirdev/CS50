from cs50 import get_int


height = get_int("Height: ")

while height>23 or height<0:
    height = get_int("Height: ")
for i in range(height):
    blankSpace = height - (i+1)
    for x in range(blankSpace):
        print(" ", end='')
    for x in range(i+2):
        print("#", end='')
    print();