from common import get_response
import unicodedata

class RTMovie:
    # to reduce memory overhead, I choose not to store my movie attribures, instead opting for a get info when needed method
    # instead of crashing the program when not finding a tag, the class will now return None or [] if attr is not found
    # that way, the rest of the movie info can still be displayed if found
    def __init__(self, url):
        self.__url = url
        self.__response = get_response(self.__url)

    def get_cast(self):
        cast_info = self.__response.find('div', 'castSection')
        if cast_info == None:
            return []
        all_cast = cast_info.find_all('div', 'cast-item media inlineBlock')
        if all_cast == []:
            return []
        # all special characters within names will be converted to utf-8 equivalent
        cast_formatted = []
        for cast in all_cast:
            if cast.find('span') == None:
                raise LookupError('%s cast member not found' % self.__url)
            cast_formatted.append(unicodedata.normalize('NFD', cast.find('span').string).encode('ascii', 'ignore').strip())
        return cast_formatted

    def get_general_info(self):
        # movie_info div contains rating, length, director, and genre info
        movie_data = {}
        movie_data['rating'] = None
        movie_data['length'] = None
        movie_data['director'] = []
        movie_data['genre'] = []

        movie_info = self.__response.find_all('li', 'meta-row clearfix')
        if movie_info == []:
            return movie_data
        for info in movie_info:
            info_attr = info.find('div', 'meta-label subtle')

            if info_attr == None:
                raise LookupError('%s info attribute not found' % self.__url)

            if info_attr.string == 'Rating: ':
                if info.find('div', 'meta-value') == None:
                    raise LookupError('%s rating not found' % self.__url)
                movie_data['rating'] = info.find('div', 'meta-value').string.split(' ')[0]
            elif info_attr.string == 'Runtime: ':
                if info.find('time') == None:
                    raise LookupError('%s length not found' % self.__url)
                movie_data['length'] = int(info.find('time').string.strip().split(' ')[0])
            elif info_attr.string == 'Directed By: ':
                directors = info.find_all('a')
                if directors == []:
                    raise LookupError('%s director not found' % self.__url)
                movie_data['director'] = [director.string for director in directors]
            elif info_attr.string == 'Genre: ':
                genres = info.find_all('a')
                if genres == []:
                    raise LookupError('%s genres not found' % self.__url)
                movie_data['genre'] = [genre.string.strip() for genre in genres]
        return movie_data

    def get_RT_score(self):
        score = self.__response.find('span', 'mop-ratings-wrap__percentage') 
        try:
            # score format is "dd%"
            return int(score.string.strip()[:-1])
        except:
            # for new movies that don't have rating input yet, return None
            return None

    def get_synopsis(self):
        synopsis = self.__response.find(id='movieSynopsis')
        if synopsis == None:
            return None
        return unicodedata.normalize('NFD', synopsis.string).encode('ascii', 'ignore').strip()

    def get_img(self):
        img_url = self.__response.find('img', 'posterImage')
        if img_url == None:
            return None
        if 'data-src' in img_url.attrs:
            return img_url['data-src']
        tag = 'src'
        try:
            return img_url[tag]
        except:
            raise KeyError('Tag %s not found in %s' % (tag, img_url))  
