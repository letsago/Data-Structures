from common import get_response

# gets showing info (movie, theater, date, and times) given a showing url to a unique movie, theater, and date
class AMCShowingInfo:
    def __init__(self, showing_url):
        # showing url format is https://www.amctheatres.com/showtimes/movie-title/date/amc-movie-theater/all
        self.__url = showing_url

    def extract_date(self):
        return self.__url.split('/')[-3]
    
    def extract_theater(self):
        # theater part of url format is amc-movie-theater
        unformatted_theater = self.__url.split('/')[-2].replace('-', ' ')
        formatted_theater = unformatted_theater[:4].upper() + unformatted_theater[4:].title()
        return formatted_theater
    
    @staticmethod
    def extract_showtimes(times_section):
        showtimes_section = times_section.find_all('div', 'Showtime')
        tag = 'aria-label'
        showtimes = []
        for showtime in showtimes_section:
            try:
                showtimes.append(showtime[tag].encode('utf-8'))
            except:
                raise KeyError('Tag %s not found in %s' % (tag, showtime))          
        return showtimes

    def get_showing_info(self):
        response = get_response(self.__url)
        movie_section = response.find('a', 'MovieTitleHeader-title')
        if movie_section == None:
            raise LookupError('%s movie section not found' % (self.__url))
        movie_title = movie_section.find('h2')
        if movie_title == None:
            raise LookupError('%s movie title not found' % (self.__url))
        showtimes_section = response.find('section', 'ShowtimeButtons')
        # attempts to locate showtimes sections by number of maxAttempts
        maxAttempts = 3
        attemptNum = 0
        while showtimes_section == None and attemptNum < maxAttempts:
            response = get_response(self.__url)
            showtimes_section = response.find('section', 'ShowtimeButtons')
            attemptNum += 1
        if attemptNum == maxAttempts:
            return None
        showing_info = {}
        showing_info['movie'] = movie_title.string.encode('utf-8').strip()
        showing_info['theater'] = self.extract_theater()
        showing_info['times'] = AMCShowingInfo.extract_showtimes(showtimes_section)
        showing_info['date'] = self.extract_date()
        return showing_info
