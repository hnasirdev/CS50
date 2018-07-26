from cs50 import get_float

cents = get_float("Change owed: ")
while cents<0:
    cents = get_float("Change owed: ")
cents = cents*100
counter =0

while cents>0:
    counter  = counter +1
    if cents>24:
        cents = cents-25
    elif cents>9:
        cents = cents-10
    elif cents>4:
        cents = cents-5
    elif cents>0:
        cents = cents-1
print(counter)