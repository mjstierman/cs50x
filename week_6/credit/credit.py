""" A small program to validate credit card numbers """

def check_digit(ccnum) -> bool:
    """ Calculate the check digit and verify """

    # Initialize the variables
    cclen = len(ccnum)
    checksum = 0

    # Start with the penultimate digit and work backward adding the values
    for i in range(cclen - 2, -1, -2):  # Start from the second to last digit
        digit = int(ccnum[i])
        product = digit * 2

        # Add the digits to the product of the checksum
        if product < 10:
            checksum += product
        else:
            checksum += product - 9

    # Add the sum of the other digits
    for i in range(cclen - 1, -1, -2):  # Start from the last digit
        checksum += int(ccnum[i])

    # If the totals last digit is 0, return true
    return checksum % 10 == 0

def id_bank(ccnum):
    """ Identify the bank """

    # if array pos[1,2] are [3,4], [3,7]; print AmEx
    if (ccnum[0] == '3' and ccnum[1] == '4') or (ccnum[0] == '3' and ccnum[1] == '7'):
        print("AMEX")

    # if array pos[1,2] are 51, 52, 53, 54, or 55; print MC
    elif (ccnum[0] == '5' and (ccnum[1] >= '1' and ccnum[1] <= '5')):
        print("MASTERCARD")

    # if array pos[1] is 4 print Visa
    elif ccnum[0] == '4':
        print("VISA")

    # else invalid
    else:
        print("INVALID")

def get_string(ask):
    """ Query the user for an int """
    out = input(ask)
    return out

def main():
    """ Do the needful """
    ccn = " "
    while len(ccn) < 12 or len(ccn) > 16:
        ccn = get_string("Enter Credit Card Number to verify: ")
    if check_digit(ccn):
        id_bank(ccn)
    else: print("INVALID")

main()
