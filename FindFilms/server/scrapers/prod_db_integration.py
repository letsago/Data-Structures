from server.database import db_session, Base, engine
from server.models import Movie, Theater, Showing, Genre, Cast, Director
from RT_scraper import RTMovie
from AMCShowingInfo_scraper import AMCShowingInfo
from AMCShowingUrls_scraper import AMCShowingUrls
from AMCTheaters_scraper import AMCTheaters
from AMCUrls_scraper import AMCUrls
import datetime
import requests
import time
from multiprocessing.dummy import Pool as ThreadPool
from functools import partial
from tqdm import tqdm

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

def get_theater_info(theater_url):
    theater_info = AMCTheaters(theater_url).get_theater_info()
    return theater_info

def get_theaters():
    AMC_theater_urls = AMCUrls().get_theater_urls()
    pool = ThreadPool(12)
    theaters = tqdm(pool.map(get_theater_info, AMC_theater_urls), total=len(AMC_theater_urls))
    theaters.set_description('Fetching theater info')
    pool.close()
    pool.join()
    return list(theaters)

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
                        None,
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

def get_showing_info(showing_url, theater_db):
    showing_info = AMCShowingInfo(showing_url).get_showing_info()
    # will not commit to database if showing info section is not found when scraping
    if showing_info != None:
        RT_url = get_RT_url(showing_info['movie'])
        return {'RT_url': RT_url, 'theater': theater_db.name, 'theater_id': theater_db.id, 'movie': showing_info['movie'], 'url': showing_url, 'date': showing_info['date'], 'times': showing_info['times']}
    return None

def get_theater_showings(theater_db):
    AMC_showing_urls = AMCShowingUrls(theater_db.url).get_showing_urls()
    pool = ThreadPool(12)
    showings = tqdm(pool.map(partial(get_showing_info, theater_db=theater_db), AMC_showing_urls), total=len(AMC_showing_urls))
    for showing in showings:
        if showing != None:
            showings.set_description('Fetching showing info for theater %s' % (showing['theater']))
    pool.close()
    pool.join()
    return showings

def get_all_showings(theaters):
    pool = ThreadPool(12)
    showings = pool.map(get_theater_showings, theaters)
    pool.close()
    pool.join()
    return showings

def commit_db_showings(theater_showings):
    pbar = tqdm(range(len(theater_showings)))
    pbar.set_description('Committing showings into database')
    for i in pbar:
        for showing in theater_showings[i]:
            if showing != None and showing['RT_url'] != None:
                movie_db = get_or_create_movie_data(showing['RT_url'], showing['movie'])
                for time in showing['times']:
                    db_session.add(Showing(movie_db.id, showing['theater_id'], showing['url'], showing['date'], time))
                    db_session.commit()

def update_prod_showings():
    # updates showings database and adds any new movies and related info to their appropriate databases using preexisting theater database info
    start = time.time()
    Showing.query.delete()

    theaters = Theater.query.all()
    theater_showings = get_all_showings(theaters)
    commit_db_showings(theater_showings)
    
    end = time.time()
    print 'Updating showings took %f seconds' % (end - start) 

def update_prod_theaters():
    start = time.time()
    Theater.query.delete()

    theaters = get_theaters()
    pbar = tqdm(range(len(theaters)))
    pbar.set_description('Committing theaters into database')
    for i in pbar:
        if theaters[i] != None:
            create_theater_data(theaters[i])

    end = time.time()
    print 'Updating theaters took %f seconds' % (end - start)

def init_prod_db():
    # performs a full initialization of the entire production database after deleting all tables
    # added Base back into this function otherwise can't reinitialize database after deleting db file due to schema changes
    Base.metadata.create_all(bind=engine)
    update_prod_theaters()
    Movie.query.delete()
    Genre.query.delete()
    Cast.query.delete()
    Director.query.delete()
    update_prod_showings()
