from sqlalchemy import Column, Integer, String, Float, ForeignKey
from server.database import Base

class User(Base):
    __tablename__ = 'user'
    id = Column(Integer, primary_key=True)
    username = Column(String(100), unique=True)
    email = Column(String, unique=True)
    password = Column(String)

    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password

class Movie(Base):
    __tablename__ = 'movie'
    id = Column(Integer, primary_key=True)
    RT_url = Column(String(200), unique=True)
    imdb_url = Column(String(200), unique=True)
    title = Column(String(100))
    rating = Column(String(10))
    length = Column(Integer)
    img = Column(String(200), unique=True)
    imdb = Column(Float)
    rottenTomatoes = Column(Integer)
    synopsis = Column(String)

    def __init__(self, RT_url, imdb_url, title, rating, length, img, imdb, rottenTomatoes, synopsis):
        self.RT_url = RT_url
        self.imdb_url = imdb_url
        self.title = title
        self.rating = rating
        self.length = length
        self.img = img
        self.imdb = imdb
        self.rottenTomatoes = rottenTomatoes
        self.synopsis = synopsis

class Genre(Base):
    __tablename__ = 'genre'
    id = Column(Integer, primary_key=True)
    movieId = Column(Integer, ForeignKey('movie.id'))
    category = Column(String(50))

    def __init__(self, movieId, category):
        self.movieId = movieId
        self.category = category

class Cast(Base):
    __tablename__ = 'cast'
    id = Column(Integer, primary_key=True)
    movieId = Column(Integer, ForeignKey('movie.id'))
    name = Column(String(50))  

    def __init__(self, movieId, name):
        self.movieId = movieId
        self.name = name

class Director(Base):
    __tablename__ = 'director'
    id = Column(Integer, primary_key=True)
    movieId = Column(Integer, ForeignKey('movie.id'))
    name = Column(String(50))    
    
    def __init__(self, movieId, name):
        self.movieId = movieId
        self.name = name

class Theater(Base):
    __tablename__ = 'theater'
    id = Column(Integer, primary_key=True)
    url = Column(String(200), unique=True)
    name = Column(String(100))
    street = Column(String(200))
    city = Column(String(50))
    state = Column(String(50))
    zipCode = Column(Integer)

    def __init__(self, url, name, street, city, state, zipCode):
        self.url = url
        self.name = name
        self.street = street
        self.city = city
        self.state = state
        self.zipCode = zipCode

class Showing(Base):
    __tablename__ = 'showing'
    id = Column(Integer, primary_key=True)
    movieId = Column(Integer, ForeignKey('movie.id'))
    theaterId = Column(Integer, ForeignKey('theater.id'))
    pDate = Column(String(20))
    time = Column(String(10))

    def __init__(self, movieId, theaterId, pDate, time):
        self.movieId = movieId
        self.theaterId = theaterId
        self.pDate = pDate
        self.time = time
