""" Finance app backend """
import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)
port = 5000

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Configure the SQLite database schema
try:
    db.execute("CREATE TABLE users (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, username TEXT NOT NULL, hash TEXT NOT NULL, cash NUMERIC NOT NULL DEFAULT 10000.00)")
except RuntimeError:
    print("An error occurred creating user table.")
try:
    db.execute("CREATE TABLE sqlite_sequence(name, seq)")
except RuntimeError:
    print("An error occurred creating sqlite_sequence table.")
try:
    db.execute("CREATE TABLE records (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, user_id INTEGER NOT NULL, date DEFAULT CURRENT_TIMESTAMP NOT NULL, symbol TEXT(4) NOT NULL, price DECIMAL(30, 2) NOT NULL, quantity INT NOT NULL, total DECIMAL(30,2), FOREIGN KEY(user_id) REFERENCES users(id))")
except RuntimeError:
    print("An error occurred creating records table.")
try:
    db.execute("CREATE UNIQUE INDEX username ON users (username)")
except RuntimeError:
    print("An error occurred creating username index.")
try:
    db.execute("CREATE UNIQUE INDEX records ON records (id)")
except RuntimeError:
    print("An error occurred creating records index.")
try:
    db.execute("CREATE INDEX date ON records (date)")
except RuntimeError:
    print("An error occurred creating date index.")

@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    name = db.execute("SELECT username FROM users WHERE id=?", session["user_id"])
    # display the user’s current cash balance
    cash = db.execute("SELECT cash FROM users WHERE id=?", session["user_id"])
    # which stocks the user owns, 
    stocks = db.execute("SELECT DISTINCT symbol FROM records WHERE user_id=?", session["user_id"])
    print(stocks)
    # A list of holdings e.g. [[symbol1, quantity1, price1], [symbol2, quantity2, price2], etc...]
    user_holdings = []
    stocks_net = 0
    # the numbers of shares owned
    for stock in stocks:
        symbol = stock['symbol']
        symbol_qty = db.execute("SELECT SUM(quantity) FROM records WHERE symbol=? AND user_id=?", symbol, session["user_id"])
        symbol_qty = symbol_qty[0]['SUM(quantity)']
        # the current price of each stock
        symbol_data = lookup(symbol)
        symbol_val = symbol_data['price']
        # and the total value of each holding (i.e., shares times price)
        symbol_net = symbol_val * int(symbol_qty)
        stocks = [symbol, symbol_qty, symbol_val, symbol_net]
        user_holdings.append(stocks)
        # display the user's net worth
        stocks_net += symbol_net
    net_worth = usd(stocks_net + cash[0]['cash'])
    return render_template("index.html", name=name[0]["username"], cash=usd(cash[0]["cash"]), user_holdings=user_holdings, stocks=usd(stocks_net), net_worth=net_worth)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        # Lookup symbol
        symbol = request.form.get("symbol")
        quoted = lookup(symbol)
        if not quoted:
            return render_template("buy.html", invalid=True, symbol=symbol)
        # Check number of shares
        try:
            quantity = int(request.form.get("quantity"))
        except TypeError:
            return render_template("buy.html", sharerror=True)
        if quantity < 1:
            return render_template("buy.html", sharerror=True)
        # Calculate the purchase
        net_price = quantity * quoted["price"]
        old_balance = db.execute("SELECT cash FROM users WHERE id=?", session["user_id"])
        old_balance = int(old_balance[0]["cash"])
        if net_price > old_balance:
            return apology("Not enough funds")
        # Record the purchase
        new_balance = old_balance - net_price
        try:
            db.execute("UPDATE users SET cash=? WHERE id=? ", new_balance, session["user_id"])
        except RuntimeError:
            return apology("A database error occurred")
        # Update the user's history
        try:
            db.execute("INSERT INTO records (user_id, symbol, price, quantity, total) VALUES (:user_id, :symbol, :price, :quantity, :total)", user_id=session["user_id"], symbol=symbol, price=quoted["price"], quantity=quantity, total=net_price)
        except RuntimeError:
            return apology("A database error occurred")
        return redirect("/")
    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        quoted = lookup(symbol)
        if not quoted:
            return render_template("quote.html", invalid=True, symbol=symbol)
        return render_template("quote.html", name = quoted["name"],
            price = usd(quoted["price"]), symbol = quoted["symbol"])
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure a correctly-entered password was submitted
        if not request.form.get("password0") == request.form.get("password1"):
            return apology("passwords must match", 403)
        elif not request.form.get("password1"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )
        # Ensure username does not exist
        if len(rows) != 0:
            return apology("Username already exists", 403)
        # INSERT the new user into users: hash the password
        username = request.form.get("username")
        hashword = generate_password_hash(request.form.get("password1"))
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hashword)
        return render_template("login.html")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        # Lookup symbol
        symbol = request.form.get("symbol")
        quoted = lookup(symbol)
        if not quoted:
            return render_template("sell.html", invalid=True, symbol=symbol)
        # check shares owned
        owned = db.execute("SELECT SUM(quantity) FROM records WHERE symbol=? AND user_id=?", symbol, session["user_id"])
        owned = owned[0]['SUM(quantity)']
        if owned < 1: 
            return render_template("sell.html", invalid=True, symbol=symbol)
        try:
            quantity = int(request.form.get("quantity"))
        except TypeError:
            return render_template("sell.html", sharerror=True)
        if quantity < 1:
            return render_template("sell.html", sharerror=True)
        # Calculate the sale
        net_price = quantity * quoted["price"]
        old_balance = db.execute("SELECT cash FROM users WHERE id=?", session["user_id"])
        old_balance = int(old_balance[0]["cash"])
        # Record the purchase
        new_balance = old_balance + net_price
        try:
            db.execute("UPDATE users SET cash=? WHERE id=? ", new_balance, session["user_id"])
        except RuntimeError:
            return apology("A database error occurred")
        # Update the user's history
        try:
            db.execute("INSERT INTO records (user_id, symbol, price, quantity, total) VALUES (:user_id, :symbol, :price, :quantity, :total)", user_id=session["user_id"], symbol=symbol, price=quoted["price"], quantity=-quantity, total=net_price)
        except RuntimeError:
            return apology("A database error occurred")
        return redirect("/")
    return render_template("sell.html")

if __name__ == '__main__':
    app.run(host="0.0.0.0", port=port)