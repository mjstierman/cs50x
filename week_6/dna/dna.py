""" 
Your task is to write a program that will take a sequence of DNA and a CSV file
containing STR counts for a list of individuals and then output to whom the DNA 
(most likely) belongs. 
"""

import csv
import sys


def main():
    """ Main function """
    # GATACA

    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: ./dna.py FILE database FILE sequence")
        return

    # Store the sysarg vars
    database_file = sys.argv[1]
    sequence_file = sys.argv[2]

    # Read database file into a variable (dictionary)
    # A dictionary in a dictionary
    database = {}
    with open(database_file, encoding="utf=8") as file:
        reader = csv.DictReader(file)
        for row in reader:
            key = row.pop('name')
            database[key] = row

    # Read DNA sequence file into a variable
    with open(sequence_file, encoding="utf-8") as file:
        sequence = file.read()

    # Find longest match of each STR in DNA sequence
    str_counts = {}
    # Get the STR keys from the first person
    # doesn't matter which person, all have same keys
    # this allows the program to do both short + long w/o hardcoding STRs
    first_person = list(database.keys())[0] 
    for str_key in database[first_person]: # iterate over they keys
        str_counts[str_key] = longest_match(sequence, str_key) # record the matches

    # Check database for matching profiles
    for name, counts in database.items():
        # using `all()` prevents have to use a bunch of `and`s
        if all(int(counts[str_key]) == str_counts[str_key] for str_key in str_counts):
            print(f"Match: {name}")
            return
    print("No match")

def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
