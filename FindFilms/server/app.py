from flask import Flask, render_template, redirect, url_for, request

app = Flask(__name__)
app.jinja_env.add_extension('pyjade.ext.jinja.PyJadeExtension')

@app.route('/')
def home():
    return render_template('home.jade')

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        if request.form['username'] != 'admin' or request.form['password'] != 'admin':
            error = 'Invalid Credentials. Please Try Again'
            return render_template('login.jade', error = error)
        else:
            return redirect(url_for('search'))
    return render_template('login.jade')

@app.route('/register', methods=['GET', 'POST'])
def register():
    if request.method == 'POST':
        return redirect(url_for('login'))
    return render_template('register.jade')

@app.route('/search', methods=['GET', 'POST'])
def search():
    ratings = range(1, 11)
    rawLengths = range(60, 180, 30)
    lengths = [str(x) + ' - ' + str(x + 30) + ' min' for x in rawLengths]
    lengths = ['< ' + str(rawLengths[0]) + ' min'] + lengths + ['> ' + str(rawLengths[-1] + 30) + ' min']
    if request.method == 'POST':
        return redirect(url_for('results'))
    return render_template('search.jade', numericRatings=ratings, movieLengths=lengths)

@app.route('/results')
def results():
    return render_template('results.jade')

@app.route('/details')
def details():
    return render_template('details.jade')
