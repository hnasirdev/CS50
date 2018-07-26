from cs50 import get_string
import sys

def main():

    if len(sys.argv)==2:
        key = int(sys.argv[1])

        plaintext = get_string("plaintext: ")
        #  ciphertext = plaintext
        ciphertext=  list(plaintext)

        for i, char in enumerate(plaintext):
            if char.isalpha():

                if char.isupper():
                    number = ord(char)-65
                    number = (number + key)%26
                    number = number + 65
                    ciphertext[i] = chr(number)
                elif char.islower():
                    number = ord(char)-97
                    number = (number + key)%26
                    number = number + 97
                    ciphertext[i] = chr(number)
            else:
                ciphertext[i]= plaintext[i]

        ciphertext = ''.join(ciphertext)

        print("ciphertext: {}".format(ciphertext))
        return 0

    else:
        print("Error, incorrect input")
        return 1

if __name__=='__main__':
    main()






