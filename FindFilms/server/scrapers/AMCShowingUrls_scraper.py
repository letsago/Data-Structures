from common import get_response
import datetime

# finds all showing urls to all movies showing at a specific theater url for all dates within next week
class AMCShowingUrls:
    def __init__(self, theater_url):
        self.__base_url = 'https://www.amctheatres.com/showtimes'
        self.__theater_url = theater_url
        self.__movie_url_ids = self.get_movie_url_ids()
    
    def get_theater_url_id(self):
        # theater url format is 'https://www.amctheatres.com/movie-theatres/seattle-tacoma/amc-pacific-place-11'
        return self.__theater_url.split('/')[-1]
        
    def get_movie_url_ids(self):
        response = get_response(self.__theater_url)
        movie_section = response.find_all('div', 'PosterContent')
        if movie_section == []:
            raise LookupError('%s movie section not found' % (self.__theater_url))
        tag = 'href'
        movie_url_ids = []
        for movie in movie_section:
            movie_url_id_section = movie.find('a', 'Btn Btn--primary')
            if movie_url_id_section == None:
                raise LookupError('%s movie tag not found' % (self.__theater_url))
            try:
                # movie tag format '/movies/movie-id/showtimes'
                movie_url_id = movie_url_id_section[tag].split('/')[2].encode('utf-8')
                movie_url_ids.append(movie_url_id)
            except:
                raise KeyError('Tag %s not found in %s' % (tag, movie_url_id_section))
        return movie_url_ids

    @staticmethod
    def get_next_week_dates():
        today = datetime.datetime.today()
        num_days = 7
        next_week = [today + datetime.timedelta(days = i) for i in range(num_days)]
        return next_week
    
    def get_showing_urls(self):
        showing_urls = set()
        theater_url_id = self.get_theater_url_id()
        for movie_url_id in self.__movie_url_ids:
            for date in AMCShowingUrls.get_next_week_dates():
                showing_url = '%s/%s/%s/%s/all' % (self.__base_url, movie_url_id, date.strftime('%Y-%m-%d'), theater_url_id)
                showing_urls.add(showing_url)
        return showing_urls
