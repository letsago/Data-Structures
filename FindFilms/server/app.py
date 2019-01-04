from flask import Flask, render_template, redirect, url_for, request, abort

app = Flask(__name__)
app.jinja_env.add_extension('pyjade.ext.jinja.PyJadeExtension')

loginData = [{'username': 'admin', 'email': 'admin@admin.com', 'password':'admin'}]
movieData = [{
    'id': 0, 
    'url': 'https://www.imdb.com/title/tt0468569/', 
    'title': 'The Dark Knight', 
    'rating': 'PG-13', 
    'length': 150, 
    'theater': 'AMC', 
    'address': '101 Main St.', 
    'times': ['8:00 pm', '10:00 pm'], 
    'price': '$8.00', 
    'img': 'https://upload.wikimedia.org/wikipedia/en/8/8a/Dark_Knight.jpg', 
    'imdbRating': 9, 
    'rottenTomatoes': 9, 
    'cast': ['Christian Bale', 'Heath Ledger', 'Aaron Eckhart'], 
    'director': 'Christopher Nolan', 
    'genre': 'Thriller'},
    {
    'id': 1, 
    'url': 'https://www.imdb.com/title/tt1022603/', 
    'title': '500 Days of Summer', 
    'rating': 'PG-13', 
    'length': 95, 
    'theater': 'Regal Cinema', 
    'address': '1 Hallow Rd.', 
    'times': ['5:00 pm', '7:30 pm', '9:00 pm'], 
    'price': '$6.00', 
    'img': 'https://upload.wikimedia.org/wikipedia/en/d/d1/Five_hundred_days_of_summer.jpg', 
    'imdbRating': 7.7, 
    'rottenTomatoes': 8.5, 
    'cast': ['Joseph Gordon-Levitt', 'Zooey Deschanel'], 
    'director': 'Marc Webb', 
    'genre': 'Romantic Comedy'},
    {
    'id': 2, 
    'url': 'https://www.imdb.com/title/tt0245429/', 
    'title': 'Spirited Away', 
    'rating': 'PG', 
    'length': 125, 
    'theater': 'Cinemark', 
    'address': '8 Haku Blvd.', 
    'times': ['2:00 pm'], 
    'price': '$7.00', 
    'img': 'https://upload.wikimedia.org/wikipedia/en/d/db/Spirited_Away_Japanese_poster.png', 
    'imdbRating': 8.6, 
    'rottenTomatoes': 9.7, 
    'cast': ['Rumi Hiiragi', 'Miyu Irino'], 
    'director': 'Hayao Miyazaki', 
    'genre': 'Fantasy'},
    {
    'id': 3, 
    'url': 'https://www.imdb.com/title/tt2278388/', 
    'title': 'The Grand Budapest Hotel', 
    'rating': 'R', 
    'length': 99, 
    'theater': 'Cinemark', 
    'address': '10 Main St.', 
    'times': ['2:00 pm'], 
    'price': '$7.00', 
    'img': 'https://upload.wikimedia.org/wikipedia/en/1/1c/The_Grand_Budapest_Hotel.png', 
    'imdbRating': 8.1, 
    'rottenTomatoes': 9.1, 
    'cast': ['Ralph Fiennes', 'F. Murray Abraham', 'Tony Revolori'], 
    'director': 'Wes Anderson', 
    'genre': 'Comedy'}
    ]

def errorMessage(attributes, data):
    error = ''
    for attribute in attributes:
        if any(login[attribute] == data[attribute] for login in loginData):
            error = attribute.capitalize() + ' already exists. Please register with a different ' + attribute + '.'
    return error

@app.route('/')
def home():
    return render_template('home.jade')

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        if not any(request.form['username'] == login['username'] and request.form['password'] == login['password'] for login in loginData):
            error = 'Invalid Credentials. Please Try Again'
            return render_template('login.jade', message=error)
        return redirect(url_for('search'))
    return render_template('login.jade')

@app.route('/register', methods=['GET', 'POST'])
def register():
    if request.method == 'POST':
        data = request.form
        attributes = ['username', 'email']
        error = errorMessage(attributes, data)
        if error != '':    
            return render_template('register.jade', message=error)
        if data['password'] != data['confirmPassword']:
            error = 'Passwords do not match. Please enter your information again.'
            return render_template('register.jade', message=error, username=data['username'], email=data['email'])
        loginData.append(data)
        success = 'Registration successful! Please login now.'
        return render_template('login.jade', message=success)
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
    return render_template('results.jade', movieData=movieData)

@app.route('/details/<movieId>')
def details(movieId):
    id = int(movieId)
    data = next((movie for movie in movieData if movie['id'] == id), None)
    if data == None:
        abort(404)
    return render_template('details.jade', movie=data)

