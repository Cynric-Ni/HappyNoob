from flask import Flask
from flask import render_template
from flask import request


app = Flask(__name__)

@app.route("/")
def hello():
    chdata = [50, 20, 30, 40, 50, 60, 70, 80]
    return render_template("index.html",chdata=chdata)
if __name__ == 'main':
    app.run()