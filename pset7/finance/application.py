import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Ensure environment variable is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    stocks=db.execute("SELECT stock, SUM(quantity) FROM transactions WHERE name= :name GROUP BY stock HAVING SUM(quantity)>0 ORDER BY stock",name=session["user_name"])
    cash=db.execute("SELECT cash FROM users WHERE id= :id", id=session["user_id"])
    currentCash=cash[0]["cash"]
    grandtotal = currentCash

    for stock in stocks:
        symbol=str(stock["stock"])
        quantity=int(stock["SUM(quantity)"])
        quote = lookup(symbol)
        stock["price"] = usd(quote["price"])
        stock['total']=usd(quote['price']*quantity)
        stock["grandtotal"]=quote['price']*quantity
        grandtotal += stock["grandtotal"]



    return render_template("index.html", stocks=stocks, cash = usd(int(currentCash)), grandtotal=usd(int(grandtotal)))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "POST":

        #Load up the stock detail in quote
        quote = lookup(request.form.get("symbol"))
        if quote == None:
            return apology("invalid symbol")
        if not request.form.get("shares").isdigit():
            return apology("must provide positive integer")

        quantity=int(request.form.get("shares"))

        if not request.form.get("symbol"):
            return apology("symbol required")

        if not request.form.get("shares"):
            return apology("quantity required")


        if quantity < 1:
            return apology("Positive quantity required")

        #The cost of buying a single share
        currentPrice = round(float(quote['price']),2)


        #currentPrice = usd(quote['price'])

        #cost = usd(quantity*currentPrice)
        #Total cost of transaction
        cost = round(float(quantity * currentPrice),2)


        stockName = quote['symbol']

        rows = db.execute("SELECT * FROM users WHERE id= :id",
                          id=session["user_id"])

        #currentCash= usd(rows[0]["cash"])
        currentCash= rows[0]["cash"]


        userName= rows[0]["username"]

        #if(currentCash<currentPrice*quantity):
        if(currentCash<cost):
            return apology("Insufficient funds")

        else:
            rows = db.execute("""INSERT into transactions("name","stock","price","quantity")VALUES(:n,:s,:p,:q)""",n=userName,s=stockName,p=currentPrice, q=quantity)
            #currentCash=usd(currentCash-(currentPrice*quantity))
            currentCash=currentCash-cost
            rows=db.execute("UPDATE users SET cash = :c where id=:id ",c=currentCash,id=session["user_id"])
            history=db.execute("""INSERT into history("symbol","quantity","price","date","username")VALUES(:s,:q,:p,datetime('now'),:u)""", s=stockName, q=quantity, p=currentPrice, u=userName)
            flash('Bought!')
            return index()


    else:
        return render_template("buy.html")



@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    rows = db.execute("SELECT * FROM users WHERE id= :id",
                          id=session["user_id"])

    userName= rows[0]["username"]
    history = db.execute("SELECT symbol, quantity, price, date, username FROM history WHERE  username= :u ORDER BY date DESC", u=userName)

    for transaction in history:

        symbol = transaction["symbol"]
        shares = transaction["quantity"]
        price = transaction["price"]
        date = transaction["date"]

    return render_template("history.html", history=history)

@app.route("/credit", methods=["GET", "POST"])
@login_required
def credit():
    """Show history of transactions"""
    if request.method == "POST":
        credit = int(request.form.get("money"))

        if not request.form.get("money"):
                return apology("Quantity not specified")

        elif credit<0:
            return apology("Bad input")

        rows = db.execute("SELECT * FROM users WHERE id= :id", id=session["user_id"])
        currentCash= rows[0]["cash"]
        currentCash +=credit

        rows=db.execute("UPDATE users SET cash = :c where id=:id ",c=currentCash,id=session["user_id"])

        return index()




    else:
        return render_template("credit.html")





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
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]
        session["user_name"]=rows[0]["username"]

        # Redirect user to home page
        flash('Successfully logged in!')
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

    if request.method == "GET":
        return render_template("quote.html")

    # User reached route via POST (as by submitting a form via POST)
    elif request.method == "POST":
        if not request.form.get("symbol"):
            return apology("symbol required", 400)
        quote = lookup(request.form.get("symbol"))
        if quote == None:
            return apology("invalid symbol")
       # """Get stock quote."""
        else:
            return render_template("quoted.html", symbol=quote["symbol"], price=usd(quote["price"]))



@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        #Do the initial checks:
        if not username:
            return apology("must provide username", 400)
        elif not password:
            return apology("must provide password", 400)
        elif not confirmation:
            return apology("must retype password", 400)
        elif password != confirmation:
            return apology("passwords dont match", 400)


        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=username)
        #username already exists
        if(len(rows)==1):
            return apology("Username already exists")

        hashed = generate_password_hash(password)
        rows = db.execute("""INSERT INTO users("username","hash") VALUES (:u,:h)""",u=username,h=hashed)
        flash('Successfully registered!')
        return render_template("login.html")

    return render_template("register.html")
  #  return apology("TODO")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    #This will bring up all the stocks user owns so that they can be displayed in the select list
    stocks=db.execute("SELECT stock, SUM(quantity) FROM transactions WHERE name= :name GROUP BY stock HAVING SUM(quantity)>0 ORDER BY stock",name=session["user_name"])

    if request.method == "POST":

        symbol = request.form.get("symbol")
         #How much am i selling
        quantity=int(request.form.get("shares"))
        if not symbol:
            return apology("Missing Symbol")

        elif not request.form.get("shares"):
            return apology("quantity required")

        elif quantity<1:
            return apology("Positive quantity required")

        #get the quote for the stock you're after
        quote = lookup(symbol)
        #this is the symbol selected from menu
        #symbol=quote['symbol']
        stockName=quote["symbol"]
        #this should narrow down search to the stock you asked for
        rows=db.execute("SELECT stock, SUM(quantity) FROM transactions WHERE name= :name AND stock= :stock GROUP BY stock ORDER BY stock",name=session["user_name"],stock=stockName)
        #if no stock found
        if(len(rows)==0):
            return apology("Stock not found", 400)

        #How much of the stock do i possess
        quantityowned=int(rows[0]['SUM(quantity)'])



        if(quantityowned<quantity):
            return apology("Insufficient stocks", 400)


        currentPrice = quote["price"]
        fundsgained= currentPrice*quantity
        #change it to negative so added in transaction like that
        quantity = quantity * -1

        rows2=db.execute("SELECT * FROM users WHERE id= :id", id=session["user_id"])
        currentCash = rows2[0]['cash']
        currentCash = currentCash + fundsgained
        #grandtotal=currentCash
        userName = rows2[0]['username']
        history=db.execute("""INSERT into history("symbol","quantity","price","date", "username")VALUES(:s,:q,:p,datetime('now'), :u)""", s=stockName, q=quantity, p=currentPrice, u=userName)
        rows=db.execute("UPDATE users SET cash = :c where id=:id ",c=currentCash,id=session["user_id"])
        rows = db.execute("""INSERT into transactions("name","stock","price","quantity")VALUES(:n,:s,:p,:q)""",n=userName,s=stockName,p=currentPrice, q=quantity)

        stocks=db.execute("SELECT stock, SUM(quantity) FROM transactions WHERE name= :name GROUP BY stock HAVING SUM(quantity)>0 ORDER BY stock",name=session["user_name"])
        flash('Sold!')
        return index()

        #for stock in stocks:
        #    symbol=str(stock['stock'])
        #    quote = lookup(symbol)
        #    quantity=int(stock['SUM(quantity)'])
        #    stock["price"] = "{:.2f}".format(quote["price"])
        #    stock['total']="{:.2f}".format(quote['price']*quantity)
        #    #grandtotal+=(quote['price']*quantity)


        #return render_template("index.html", stocks=stocks, cash = currentCash)




    return render_template("sell.html", stocks=stocks)


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
