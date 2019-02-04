from server.database import db_session
from server.models import Movie, Theater, Showing, Genre, Cast, Director
from RT_scraper import RTMovie
from AMCShowingInfo_scraper import AMCShowingInfo
from AMCShowingUrls_scraper import AMCShowingUrls
from AMCTheaters_scraper import AMCTheaters
from AMCUrls_scraper import AMCUrls
import datetime
import requests

def get_RT_url(movie_title):
    # RT url format is 'https://www.rottentomatoes.com/m/movie_name*_release_year*'
    # note release year is only necessary for movies with same names
    # priority checking valid, unique RT urls for same name movies released in 2019, then in 2018, then with no year stamp 
    movie_url_id = movie_title.lower().translate(None, '.!?:').replace(' ', '_').replace('-', '_')
    year_increments = 1
    year_url_ids = ['_%d' % (datetime.datetime.today().year - i) for i in range(year_increments)]
    year_url_ids.append('')
    for year_url_id in year_url_ids:
        RT_url = 'https://www.rottentomatoes.com/m/%s%s' % (movie_url_id, year_url_id)
        response = requests.get(RT_url)
        if response.status_code == 200:
            return RT_url
    return None

def get_seattle_theaters():
    # only choose theaters in Seattle for now
    seattle_theaters =[]
    AMC_theater_urls = AMCUrls().get_theater_urls()
    for theater_url in AMC_theater_urls:
        theater_info = AMCTheaters(theater_url).get_theater_info()
        if theater_info['city'] == 'Seattle':
            seattle_theaters.append(theater_info)
    return seattle_theaters

def create_theater_data(theater_info):
    # theater name is unique so first will return unique row if found
    theater_db = Theater(theater_info['url'], theater_info['name'], theater_info['street'], theater_info['city'], theater_info['state'], theater_info['zipCode'])
    db_session.add(theater_db)
    db_session.commit()
    return theater_db

def get_or_create_movie_data(RT_url, movie_title):
    # gets movie from database if exists, otherwise commits new movie to database and returns it
    # RT_url is a unique key so first will return unique row
    movie_db = Movie.query.filter(Movie.RT_url == RT_url).first()
    if movie_db == None:
        movie = RTMovie(RT_url)
        movie_general_info = movie.get_general_info()
        movie_db = Movie(RT_url, 
                        # using RT_url as filler for imbd_url since every imdb_url needs to be unique
                        # will add actual imdb_url later
                        RT_url, 
                        movie_title, 
                        movie_general_info['rating'],
                        movie_general_info['length'],
                        movie.get_img(),
                        # add actual imdb_score later
                        9.0,
                        movie.get_RT_score(),
                        movie.get_synopsis())
        db_session.add(movie_db)
        db_session.commit()

        for genre in movie_general_info['genre']:
            db_session.add(Genre(movie_db.id, genre))
        for cast in movie.get_cast():
            db_session.add(Cast(movie_db.id, cast))
        for director in movie_general_info['director']:
            db_session.add(Director(movie_db.id, director))
        db_session.commit()
    return movie_db

def commit_db_showings(theater_db):
    AMC_showing_urls = AMCShowingUrls(theater_db.url).get_showing_urls()
    for showing_url in AMC_showing_urls:
        showing_info = AMCShowingInfo(showing_url).get_showing_info()
        # will not commit to database if showing info section is not found when scraping
        if showing_info != None:
            RT_url = get_RT_url(showing_info['movie'])
            # noting an edge case where get_RT_url will return no valid RT_url and subsequently will not commit showings... 
            # for that movie if it was released more than a year ago, is indistinguishable by name only, and is currently showing in theaters
            if RT_url != None:
                movie_db = get_or_create_movie_data(RT_url, showing_info['movie'])
                for time in showing_info['times']:
                    db_session.add(Showing(movie_db.id, theater_db.id, showing_info['date'], time))
                db_session.commit()

def update_prod_showings():
    # updates showings database and adds any new movies and related info to their appropriate databases using preexisting theater database info
    Showing.query.delete()

    theaters = Theater.query.all()
    for theater in theaters:
        commit_db_showings(theater)

def update_prod_theaters():
    Theater.query.delete()

    seattle_theaters = get_seattle_theaters()
    for theater_info in seattle_theaters:
        create_theater_data(theater_info)

def init_prod_db():
    # performs a full initialization of the entire production database after deleting all tables
    update_prod_theaters()
    Movie.query.delete()
    Genre.query.delete()
    Cast.query.delete()
    Director.query.delete()
    update_prod_showings()
