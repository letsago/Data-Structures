from sqlalchemy import create_engine
from sqlalchemy.orm import scoped_session, sessionmaker
from sqlalchemy.ext.declarative import declarative_base

hostname = ''
path = 'findFilms.db'
engine = create_engine('sqlite://%s/%s' % (hostname, path), convert_unicode=True)
db_session = scoped_session(sessionmaker(autocommit=False,
                                         autoflush=False,
                                         bind=engine))
Base = declarative_base()
Base.query = db_session.query_property()


def init_db():
    from server.database import db_session
    from server.models import Movie, Theater, Showing, User
    Base.metadata.create_all(bind=engine)

    Movie.query.delete()
    Theater.query.delete()
    Showing.query.delete()
    User.query.delete()

    movie_one = Movie('https://www.imdb.com/title/tt0468569/', 'The Dark Knight', 'PG-13', 150, 'https://upload.wikimedia.org/wikipedia/en/8/8a/Dark_Knight.jpg',
                9.0, 90, 'Thriller', 'Christian Bale', 'Christopher Nolan', 'Heath Ledger', 'Aaron Eckhart')
    movie_two = Movie('https://www.imdb.com/title/tt1022603/', '500 Days of Summer', 'PG-13', 95,
                'https://upload.wikimedia.org/wikipedia/en/d/d1/Five_hundred_days_of_summer.jpg', 7.7, 85, 'Romantic', 'Joseph Gordon-Levitt', 'Marc Webb', 'Zooey Deschanel')
    movie_three = Movie('https://www.imdb.com/title/tt0245429/', 'Spirited Away', 'PG', 125,
                'https://upload.wikimedia.org/wikipedia/en/d/db/Spirited_Away_Japanese_poster.png', 8.6, 97, 'Fantasy', 'Rumi Hiiragi', 'Hayao Miyazaki', 'Miyu Irino')
    movie_four = Movie('https://www.imdb.com/title/tt2278388/', 'The Grand Budapest Hotel', 'R', 99,
                'https://upload.wikimedia.org/wikipedia/en/1/1c/The_Grand_Budapest_Hotel.png', 8.1, 91, 'Comedy', 'Ralph Fiennes', 'Wes Anderson', 'F. Murray Abraham', 'Tony Revolori')
    movie_five = Movie('https://www.imdb.com/title/tt0144084/', 'American Psycho', 'R', 101,
                'https://upload.wikimedia.org/wikipedia/en/0/0c/American_Psycho.png', 7.6, 68, 'Drama', 'Willem Dafoe', 'Mary Harron', 'Christian Bale', 'Jared Leto')
    theater_one = Theater('AMC', '101 Main St.')
    theater_two = Theater('Regal', '1 Hallow Rd.')
    theater_three = Theater('Cinemark', '8 Haku Blvd.')
    user_one = User('admin', 'admin@admin.com', 'admin')
    db_session.add_all([movie_one, movie_two, movie_three, movie_four, movie_five, theater_one, theater_two, theater_three, user_one])
    db_session.commit()

    db_session.add_all([
        Showing(movie_one.id, theater_one.id, '2013-01-02', '7:00 pm', '$7.00', 5, '9:00 pm', '11:00 pm'),
        Showing(movie_two.id, theater_two.id, '2013-04-06', '5:00 pm', '$8.00', 2),
        Showing(movie_three.id, theater_three.id, '2013-05-09', '7:00 pm', '$6.00', 8, '8:30 pm')])
    db_session.commit()

