from scrapers.RT_scraper import RTMovie
from server.models import Movie, Cast, Genre, Director
from sqlalchemy.orm.exc import NoResultFound
import pytest

def movie_scraper_for_testing(title):
    movie = RTMovie(title) 
    movie_data = {}
    movie_data.update(movie.get_general_info())
    movie_data['cast'] = movie.get_cast()
    return movie_data

def assert_movie_attr_exists(table, db_attr, db_movie, test_attr, test_movie):
    data = table.query.filter(table.movieId == db_movie.id).all()
    assert len(test_movie[test_attr]) == len(data)
    for i in range(len(test_movie[test_attr])):
        assert test_movie[test_attr][i] == getattr(data[i], db_attr)   

@pytest.mark.parametrize('title', [
    ('The Dark Knight'),
    ('500 Days of Summer'),
    ('Spirited Away'),
    ('The Grand Budapest Hotel'),
    ('American Psycho')
])

def test_movie_info(title):
    # test_movie does not account for score, img url, or synopsis as all those attributes are more subject to change
    # however, the existence of the tags they are found by are tested for
    try:
        db_movie = Movie.query.filter(Movie.title == title).one()
    except NoResultFound:
        raise LookupError('%s not found in test database' % (title))
    test_movie = movie_scraper_for_testing(title)
    for attr in test_movie:
        # cast, genre, and director also test for specific order of data scraping
        if attr == 'cast':
            assert_movie_attr_exists(Cast, 'name', db_movie, attr, test_movie)    
        elif attr == 'genre':
            assert_movie_attr_exists(Genre, 'category', db_movie, attr, test_movie)    
        elif attr == 'director':
            assert_movie_attr_exists(Director, 'name', db_movie, attr, test_movie)
        else:
            assert test_movie[attr] == getattr(db_movie, attr)
