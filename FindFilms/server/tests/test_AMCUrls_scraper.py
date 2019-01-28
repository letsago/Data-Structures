from scrapers.AMCUrls_scraper import AMCUrls
import pytest

# testing that .get_theater_urls() extracts all theater urls for seattle area only
theater_url_ids = [ 
    'amc-pacific-place-11',
    'amc-oak-tree-6',
    'amc-southcenter-16',
    'amc-kitsap-8',
    'amc-factoria-8',
    'amc-cascade-mall-14',
    'amc-woodinville-12',
    'amc-alderwood-mall-16',
    'amc-kent-station-14',
    'amc-classic-gateway-8',
    'amc-lakewood-mall-12',
    'amc-seattle-10'
]

def test_theater_url_count():
    assert len(AMCUrls().get_theater_urls()) == len(theater_url_ids)

def test_theater_url_existence():
    test_theater_urls = AMCUrls().get_theater_urls()
    for url_id in theater_url_ids:
        url = 'https://www.amctheatres.com/movie-theatres/seattle-tacoma/%s' % (url_id)
        assert url in test_theater_urls
