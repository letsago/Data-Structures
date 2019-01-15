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
    url = Column(String(200), unique=True)
    title = Column(String(100))
    rating = Column(String(10))
    length = Column(Integer)
    img = Column(String(200), unique=True)
    imdb = Column(Float)
    rottenTomatoes = Column(Integer)
    genre = Column(String(20))
    cast1 = Column(String(50))
    cast2 = Column(String(50))
    cast3 = Column(String(50))
    director = Column(String(50))

    def __init__(self, url, title, rating, length, img, imdb, rottenTomatoes, genre, cast1, director, cast2=None, cast3=None):
        self.url = url
        self.title = title
        self.rating = rating
        self.length = length
        self.img = img
        self.imdb = imdb
        self.rottenTomatoes = rottenTomatoes
        self.genre = genre
        self.cast1 = cast1
        self.director = director
        self.cast2 = cast2
        self.cast3 = cast3

class Theater(Base):
    __tablename__ = 'theater'
    id = Column(Integer, primary_key=True)
    name = Column(String(10))
    address = Column(String(200))

    def __init__(self, name, address):
        self.name = name
        self.address = address

class Showing(Base):
    __tablename__ = 'showing'
    id = Column(Integer, primary_key=True)
    movieId = Column(Integer, ForeignKey('movie.id'))
    theaterId = Column(Integer, ForeignKey('theater.id'))
    pDate = Column(String(20))
    time1 = Column(String(10))
    time2 = Column(String(10))
    time3 = Column(String(10))
    price = Column(String(10))
    distance = Column(Integer)

    def __init__(self, movieId, theaterId, pDate, time1, price, distance, time2=None, time3=None):
        self.movieId = movieId
        self.theaterId = theaterId
        self.pDate = pDate
        self.time1 = time1
        self.price = price
        self.distance = distance
        self.time2 = time2
        self.time3 = time3
