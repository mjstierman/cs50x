# Week 9: Flask
A collection of Flask web site practice problems. 

This problem set requires the use of the [CS50 Python](https://cs50.readthedocs.io/libraries/cs50/python/) SQL library, which allows for direct SQL commands and database modification. The cs50 library is published in pip: `pip install cs50`

To test these sites, the CS50 python library must be installed.
Then download this repo, cd into the project, and `flask run`

## Birthdays
This is a practice problem (the code is provided) to familiarize the student with some basic functionality and structure. The finished code is provided.

## Finance
Build the C$50 finance page. 

Requirements:
- Complete the implementation of register in such a way that it allows a user to register for an account via a form.
- Complete the implementation of quote in such a way that it allows a user to look up a stock’s current price.
- Complete the implementation of buy in such a way that it enables a user to buy stocks.
- Complete the implementation of index in such a way that it displays an HTML table summarizing, for the user currently logged in, which stocks the user owns, the numbers of shares owned, the current price of each stock, and the total value of each holding (i.e., shares times price). Also display the user’s current cash balance along with a grand total (i.e., stocks’ total value plus cash).
- Complete the implementation of sell in such a way that it enables a user to sell shares of a stock (that he or she owns).
- Complete the implementation of history in such a way that it displays an HTML table summarizing all of a user’s transactions ever, listing row by row each and every buy and every sell.

Personal touches:
Implement at least one personal touch of your choice:
- Allow users to change their passwords.
- Allow users to add additional cash to their account.
- Allow users to buy more shares or sell shares of stocks they already own via index itself, without having to type stocks’ symbols manually.
- Implement some other feature of comparable scope.

