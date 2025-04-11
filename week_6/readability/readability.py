""" A program to calucate the educational attainment of a given phrase """
import re

def main():
    """ Do the needful """
    # Get the phrase from the user
    phrase = get_string("Please enter a text to evaluate: ")

    # Calculate the number of sentences, words, letters
    sentences = count_sentences(phrase)
    words = count_words(phrase)
    letters = count_letters(phrase)

    # Print the grade level
    grade = get_gradelevel(sentences, words, letters)

    if grade <= 1:
        print("Before grade 1.")
    elif grade >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {int(grade)}")

def get_string(ask):
    """ Query the user for an int """
    out = input(ask)
    return out

def count_sentences(phrase):
    """ Count the sentences in a phrase by splitting by punctuation marks """
    # Use a regular expression to split by '.', '?', or '!'
    sentences = re.split(r'[.!?]+', phrase)  # Split on one or more punctuation marks
    # Filter out any empty strings that may result from splitting
    sentences = [s for s in sentences if s.strip()]  # Remove empty sentences
    return len(sentences)  # Return the number of sentences


def count_words(phrase):
    """ Count the words in a phrase by splitting by spaces """
    words = phrase.split()  # Split the phrase into words based on whitespace
    return len(words)  # Return the number of words

def count_letters(phrase):
    """ Count the letters """
    letters = 0
    for char in phrase:
        if char.isalpha():
            letters += 1
    return letters

def get_gradelevel(sentences, words, letters):
    """ Maths to calculate grade level """
    # L = average number of letters per 100 words
    l = letters / words * 100.0
    # S = average number of sentences per 100 words
    s = sentences / words * 100.0
    # Turn input string into a vector of sentences, count, divide by 100
    index = (0.0588 * l) - (0.296 * s) - 15.8
    return index

main()
