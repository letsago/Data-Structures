from scrapers.AMCShowingUrls_scraper import AMCShowingUrls
import pytest

# testing that .get_showing_urls() extracts all showing urls for Alita Battle Angle in amc-seattle-10 theater for next week
def test_showing_urls():
    dates = AMCShowingUrls.get_next_week_dates()
    showing_urls = AMCShowingUrls('https://www.amctheatres.com/movie-theatres/seattle-tacoma/amc-seattle-10').get_showing_urls()
    for date in dates:
        test_url = 'https://www.amctheatres.com/showtimes/alita-battle-angel-43118/%s/amc-seattle-10/all' % (date.strftime('%Y-%m-%d'))
        assert test_url in showing_urls
