from scrapers.AMCTheaters_scraper import AMCTheaters
from server.models import Theater
from sqlalchemy.orm.exc import NoResultFound
import pytest

@pytest.mark.parametrize('theater_url_id', [
    ('amc-pacific-place-11'),
    ('amc-oak-tree-6'),
    ('amc-seattle-10')
])

def test_theater_info(theater_url_id):
    test_theater = AMCTheaters('https://www.amctheatres.com/movie-theatres/seattle-tacoma/%s' % (theater_url_id)).get_theater_info()
    try:
        db_theater = Theater.query.filter(Theater.name == test_theater['name']).one()
    except NoResultFound:
        raise LookupError('%s not found in test database' % (test_theater['name']))
    for attr in test_theater:
        assert test_theater[attr] == getattr(db_theater, attr)

