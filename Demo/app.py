from flask import Flask,render_template,request
import webbrowser
import os
from threading import Timer,Thread,Event
import webview

app = Flask(__name__)

app_title = "数字航道质量分析"
host = "http://127.0.0.1"
port = 5000

stop_event = Event()

def run():
    while not stop_event.is_set():
        app.run(port=port)



""" def open_browser():
    webbrowser.open_new("http://127.0.0.1:5000/") """
""" try:
        browser = os.environ.get('BROWSER')
        webbrowser.get(browser).open(url)
    except Exception as e:
        print(f"oh~Fuck,somewrong with browser:{e}") """

@app.route("/")
def index():
    f_excellent_data = [5,2,3,3,3,0,3,3]
    f_good_data = [0,0,0,0,0,0,0,0]
    f_average_data = [0,0,0,0,0,0,0,0]
    f_poor_data = [0,0,0,0,0,0,0,0]

    i_excellent_data = []
    i_good_data = []
    

    return render_template("index.html",
                           f_excellent_data = f_excellent_data,
                           f_good_data = f_good_data,
                           f_average_data = f_average_data,
                           f_poor_data = f_poor_data,
                           i_excellent_data = i_excellent_data,
                           i_good_data = i_good_data,
                           )

if __name__ == '__main__':
    t = Thread(target=run)
    t.daemon = True
    t.start()

    webview.create_window(
        app_title,
        f"{host}:{port}",
        resizable=False,
        height=1000,
        width=1980
    )

    webview.start()
    """ Timer(1,open_browser).start() """

    """ threading.Thread(target=open_browser,args=(local_url,)).start() """
   
    