from scrapers.AMCShowingInfo_scraper import AMCShowingInfo
from server.models import Showing, Theater, Movie
from sqlalchemy.orm.exc import MultipleResultsFound, NoResultFound
import pytest

def find_id(table, db_attr, test_info, test_attr):
    try:
        obj_id = table.query.filter(getattr(table, db_attr) == test_info[test_attr]).one().id
    except MultipleResultsFound:
        raise LookupError('Multiple %s found in %s test database' % (test_info[test_attr], test_attr))
    except NoResultFound:
        raise LookupError('%s not found in %s test database' % (test_info[test_attr], test_attr))
    return obj_id

# these tests contain AMC showing info that need to be updated every Wednesday - the day AMC updates their showings
@pytest.mark.parametrize('existent_showings_url_id', [
    # amc pacific place 11 showings
    ('spider-man-into-the-spider-verse-48153/2019-01-30/amc-pacific-place-11/all'),
    ('glass-51215/2019-01-30/amc-pacific-place-11/all'),

    # amc oak tree 6 showings
    ('spider-man-into-the-spider-verse-48153/2019-01-30/amc-oak-tree-6/all'),
    ('glass-51215/2019-01-30/amc-oak-tree-6/all'),

    # amc seattle 10 showings
    ('spider-man-into-the-spider-verse-48153/2019-01-30/amc-seattle-10/all'),
    ('glass-51215/2019-01-30/amc-seattle-10/all')
])

def test_existent_showing_info(existent_showings_url_id):
    # because each showing in the db has a unique time, .first() will return a unique showing if that showing exists else it returns None
    # thus by filtering for every database attribute, verifying existence can show if all attributes between test_showing and database showing match
    test_showing = AMCShowingInfo('https://www.amctheatres.com/showtimes/%s' % (existent_showings_url_id)).get_showing_info()
    assert test_showing != None
    
    # gets unique theater_id and movie_id in Theater and Movie test databases
    # will raise LookupError if movie_id or theater_id are not found in test databases
    theater_id = find_id(Theater, 'name', test_showing, 'theater')
    movie_id = find_id(Movie, 'title', test_showing, 'movie')

    for time in test_showing['times']:
        assert Showing.query.filter(Showing.movieId == movie_id, 
                                        Showing.theaterId == theater_id, 
                                        Showing.pDate == test_showing['date'], 
                                        Showing.time == time).first() != None

@pytest.mark.parametrize('nonexistent_showings_url_id', [
    ('spider-man-into-the-spider-verse-48153/2020-01-30/amc-seattle-10/all'),
    ('glass-51215/2020-01-30/amc-seattle-10/all')
])

def test_nonexistent_showing_info(nonexistent_showings_url_id):
    test_showing = AMCShowingInfo('https://www.amctheatres.com/showtimes/%s' % (nonexistent_showings_url_id)).get_showing_info()
    assert test_showing == None
