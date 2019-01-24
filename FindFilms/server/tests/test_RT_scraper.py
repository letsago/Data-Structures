from scrapers.RT_scraper import RTMovie
from server.models import Movie
from sqlalchemy.orm.exc import NoResultFound
import pytest

def movie_scraper_for_testing(title):
    movie = RTMovie(title) 
    movie_data = {}
    movie_data.update(movie.get_general_info())
    movie_data['cast'] = movie.get_cast()
    return movie_data

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
        if attr == 'cast' or attr =='genre':
            for i in range(len(test_movie[attr])):
                assert test_movie[attr][i] == getattr(db_movie, attr + str(i + 1))
        else:
            assert test_movie[attr] == getattr(db_movie, attr)
