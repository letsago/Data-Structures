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
    'img': 'https://upload.wikimedia.org/wikipedia/en/8/8a/Dark_Knight.jpg', 
    'imdb': 9, 
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
    'img': 'https://upload.wikimedia.org/wikipedia/en/d/d1/Five_hundred_days_of_summer.jpg', 
    'imdb': 7.7, 
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
    'img': 'https://upload.wikimedia.org/wikipedia/en/d/db/Spirited_Away_Japanese_poster.png', 
    'imdb': 8.6, 
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
    'img': 'https://upload.wikimedia.org/wikipedia/en/1/1c/The_Grand_Budapest_Hotel.png', 
    'imdb': 8.1, 
    'rottenTomatoes': 9.1, 
    'cast': ['Ralph Fiennes', 'F. Murray Abraham', 'Tony Revolori'], 
    'director': 'Wes Anderson', 
    'genre': 'Comedy'}
]
theaterData = [{
    'id': 0,
    'theater': 'AMC',
    'address': '101 Main St.'
    },
    {
    'id': 1,
    'theater': 'Regal',
    'address': '1 Hallow Rd.'
    },
    {
    'id': 2,
    'theater': 'Cinemark',
    'address': '8 Haku Blvd.'
    }
]
showingData = [{
    'id': 0,
    'theaterId': 0,
    'movieId': 0,
    'times': ['8:00 pm', '10:00 pm'], 
    'price': '$8.00'},
    {
    'id': 1,
    'theaterId': 1,
    'movieId': 1,
    'times': ['5:00 pm', '7:30 pm', '9:00 pm'], 
    'price': '$6.00'},
    {
    'id': 2,
    'theaterId': 2,
    'movieId': 2,
    'times': ['2:00 pm'], 
    'price': '$7.00'}
]

def errorMessage(attributes, data):
    error = ''
    for attribute in attributes:
        if any(login[attribute] == data[attribute] for login in loginData):
            error = attribute.capitalize() + ' already exists. Please register with a different ' + attribute + '.'
    return error

def movieSearch(formData):
    output = movieData
    searchKeys = []
    for key, value in formData.items():
        if value != '':
            searchKeys.append(key)
    for key in searchKeys:
        if key == 'length' or key == 'imdb' or key == 'rottenTomatoes':
            try:
                if key == 'length':
                    output = [movie for movie in output if movie[key] <= float(formData[key])]
                else:
                    output = [movie for movie in output if movie[key] >= float(formData[key])]
            except ValueError:
                return []              
        elif key == 'cast':
            output = [movie for movie in output if formData[key].lower() in map(lambda actor:actor.lower(), movie[key])]
        else:
            output = [movie for movie in output if movie[key].lower() == formData[key].lower()]
    return output  

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
    rawScores = range(1, 11)
    scores = [''] + rawScores
    rawLengths = range(60, 210, 30)
    lengths = [''] + rawLengths
    if request.method == 'POST':
        return render_template('results.jade', movieData=movieSearch(request.form))
    return render_template('search.jade', numericScores=scores, movieLengths=lengths)

@app.route('/results')
def results():
    return render_template('results.jade', movieData=movieData)

@app.route('/details/<movieId>')
def details(movieId):
    id = int(movieId)
    movieInfo = next((movie for movie in movieData if movie['id'] == id), None)
    if movieInfo == None:
        abort(404)
    showingInfo = next((showing for showing in showingData if showing['movieId'] == id), None)
    if showingInfo == None:
        showingInfo = {}
        theaterInfo = {}
    else:
        theaterInfo = next((theater for theater in theaterData if theater['id'] == showingInfo['theaterId']), None)
    return render_template('details.jade', movie=movieInfo, showing=showingInfo, theater=theaterInfo)

