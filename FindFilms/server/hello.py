from flask import Flask
app = Flask(__name__)

@app.route("/")
def hello():
    return "Hello Patrick!"

@app.route("/world")
def hello_world():
    return "Hello vaibhav!"
