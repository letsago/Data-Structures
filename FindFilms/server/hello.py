from flask import Flask, render_template

app = Flask(__name__)
app.jinja_env.add_extension('pyjade.ext.jinja.PyJadeExtension')

@app.route("/")
def hello():
    return "Hello Patrick!"

@app.route("/world")
def hello_world():
    return render_template("hello.jade", youAreUsingJade = True, pageTitle = "Hola!")
