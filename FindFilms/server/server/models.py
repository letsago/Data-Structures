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
    genre1 = Column(String(20))
    genre2 = Column(String(20))
    genre3 = Column(String(20))
    genre4 = Column(String(20))
    cast1 = Column(String(50))
    cast2 = Column(String(50))
    cast3 = Column(String(50))
    cast4 = Column(String(50))
    cast5 = Column(String(50))
    cast6 = Column(String(50))
    director = Column(String(50))
    synopsis = Column(String)

    def __init__(self, RT_url, imdb_url, title, rating, length, img, imdb, rottenTomatoes, genre1, cast1, director, synopsis, cast2=None, cast3=None, cast4=None, cast5=None, cast6=None, genre2=None, genre3=None, genre4=None):
        self.RT_url = RT_url
        self.imdb_url = imdb_url
        self.title = title
        self.rating = rating
        self.length = length
        self.img = img
        self.imdb = imdb
        self.rottenTomatoes = rottenTomatoes
        self.genre1 = genre1
        self.cast1 = cast1
        self.director = director
        self.synopsis = synopsis
        self.cast2 = cast2
        self.cast3 = cast3
        self.cast4 = cast4
        self.cast5 = cast5
        self.cast6 = cast6
        self.genre2 = genre2
        self.genre3 = genre3
        self.genre4 = genre4

class Theater(Base):
    __tablename__ = 'theater'
    id = Column(Integer, primary_key=True)
    name = Column(String(100))
    street = Column(String(200))
    city = Column(String(50))
    state = Column(String(50))
    zipCode = Column(Integer)

    def __init__(self, name, street, city, state, zipCode):
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
