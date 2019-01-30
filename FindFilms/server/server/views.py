from server import app
from flask import render_template, request, redirect, url_for, abort
from server.models import Movie, Theater, Showing, Genre, Cast, Director, User
from sqlalchemy import and_, or_, func
from server.database import db_session
from sqlalchemy.orm.exc import MultipleResultsFound, NoResultFound

def errorMessage(attributes, data):
    error = ''
    for attribute in attributes:
        if any(User.query.filter(getattr(User, attribute) == data[attribute])):
            error = attribute.capitalize() + ' already exists. Please register with a different ' + attribute + '.'
    return error

def movieSearch(formData):
    constraints = []
    searchKeys = []
    for key, value in formData.items():
        if value != '':
            searchKeys.append(key)
    for key in searchKeys:
        if key == 'length' or key == 'imdb' or key == 'rottenTomatoes':
            try:
                if key == 'length':
                    constraints.append(getattr(Movie, key) <= float(formData[key]))
                else:
                    constraints.append(getattr(Movie, key) >= float(formData[key]))
            except ValueError:
                return []
        elif key == 'cast':
            constraints.append(Cast.name == formData[key].lower().title())
        elif key == 'rating':
            constraints.append(getattr(Movie, key) == formData[key].upper())
        elif key == 'genre':
            constraints.append(Genre.category == formData[key].lower().title())
        elif key == 'director':
            constraints.append(Director.name == formData[key].lower().title())
        else:
            constraints.append(getattr(Movie, key) == formData[key].lower().title())
    return [movie.__dict__ for movie in Movie.query.join(Genre, Cast, Director).filter(and_(*constraints))]

def findOneRowById(table, targetId, strObject):
    try:
        info = table.query.filter(table.id == targetId).one()
    except MultipleResultsFound:
        print('Multiple ' + strObject + ' found with same id')
        abort(404)  
    except NoResultFound:
        print('No ' + strObject + ' found')
        abort(404)
    return info.__dict__

@app.route('/')
def home():
    return render_template('home.jade')

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        if not list(User.query.filter(User.username == request.form['username'], User.password == request.form['password'])):
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
        db_session.add(User(data['username'], data['email'], data['password']))
        db_session.commit()
        success = 'Registration successful! Please login now.'
        return render_template('login.jade', message=success)
    return render_template('register.jade')

@app.route('/search', methods=['GET', 'POST'])
def search():
    rawScores = range(1, 11)
    imdbScores = [''] + rawScores
    rottenTomatoes = [''] + [score * 10 for score in rawScores]
    rawLengths = range(60, 210, 30)
    lengths = [''] + rawLengths
    if request.method == 'POST':
        return render_template('results.jade', movieData=movieSearch(request.form))
    return render_template('search.jade', imdbScores=imdbScores, rottenTomatoes=rottenTomatoes, movieLengths=lengths)

@app.route('/results')
def results():
    return render_template('results.jade', movieData=Movie.query.all())

@app.route('/details/<movieId>')
def details(movieId):
    id = int(movieId)
    movieInfo = findOneRowById(Movie, id, 'movies')
    movieInfo['genres'] = [genre.category for genre in Genre.query.filter(Genre.movieId == movieInfo['id']).all()]
    movieInfo['cast'] = [actor.name for actor in Cast.query.filter(Cast.movieId == movieInfo['id']).all()]
    movieInfo['directors'] = [director.name for director in Director.query.filter(Director.movieId == movieInfo['id']).all()]
    # for now theater, only select theater id 3, as theater
    # once location feature is integrated, theater will be selected based on calculated minimum distance from user location
    theaterId = 3
    allShowings = Showing.query.filter(Showing.movieId == id, Showing.theaterId == theaterId).all()
    if allShowings != []:
        theaterInfo = findOneRowById(Theater, theaterId, 'theaters')
        # once search by date feature is integrated, all showings displayed will be on the same date
        # thus only time attribute is unique in allShowings
        showingInfo = {}
        showingInfo['date'] = allShowings[0].pDate
        times = [showing.time for showing in allShowings]
        showingInfo['times'] = times
        return render_template('details.jade', movie=movieInfo, showing=showingInfo, theater=theaterInfo)
    return render_template('details.jade', movie=movieInfo)
