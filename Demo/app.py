from flask import Flask
from flask import render_template
from flask import request
import webbrowser
import os
from threading import Timer

app = Flask(__name__)

def open_browser():
    webbrowser.open_new("http://127.0.0.1:5000/")

    """ try:
        browser = os.environ.get('BROWSER')
        webbrowser.get(browser).open(url)
    except Exception as e:
        print(f"oh~Fuck,somewrong with browser:{e}") """

@app.route("/")
def hello():
    chdata = [50, 20, 30, 40, 50, 60, 70, 80]
    return render_template("index.html",chdata=chdata)
if __name__ == '__main__':
    local_url = f"http://127.0.0.1:5000/"
    Timer(1,open_browser).start()

    """ threading.Thread(target=open_browser,args=(local_url,)).start() """
   
    app.run()