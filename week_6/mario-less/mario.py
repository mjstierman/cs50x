""" Module for printing one half of a Mario block pyramid """

def print_halfblock():
    """ Print one half of a pyramid """
    height = 0
    while height < 1 or height > 10:
        height = int(input("How high should Mario jump?: "))

    for row in range(height):
        # Print spaces
        for space in range(height - row - 1):
            print(" ", end="")
        # Print hashes
        for hash in range(row + 1):
            print("#", end="")
        # Move to the next line after each row
        print()

print_halfblock()
