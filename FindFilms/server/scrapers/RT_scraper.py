from common import get_response
import unicodedata

class RTMovie:
    def __init__(self, title):
        self.__title = title
        self.__url = self.get_url()
        self.__response = get_response(self.__url)

    def get_url(self):
        identifier = self.__title.lower().replace(' ', '_')
        url = 'https://www.rottentomatoes.com/m/%s' % (identifier)
        return url

    def get_cast(self):
        cast_info = self.__response.find('div', 'castSection')
        if cast_info == None:
            raise LookupError('Cast section not found')
        all_cast = cast_info.find_all('div', 'cast-item media inlineBlock')
        if all_cast == []:
            raise LookupError('Cast profiles not found')
        # all special characters within names will be converted to utf-8 equivalent
        cast_formatted = []
        for cast in all_cast:
            if cast.find('span') == None:
                raise LookupError('Cast member not found')
            cast_formatted.append(unicodedata.normalize('NFD', cast.find('span').string).encode('ascii', 'ignore').strip())
        return cast_formatted

    def get_general_info(self):
        # movie_info div contains rating, length, director, and genre info
        movie_info = self.__response.find_all('li', 'meta-row clearfix')
        if movie_info == []:
            raise LookupError('General movie info section not found') 
        movie_data = {}
        for info in movie_info:
            info_attr = info.find('div', 'meta-label subtle')

            if info_attr == None:
                raise LookupError('Info attribute not found')

            if info_attr.string == 'Rating: ':
                if info.find('div', 'meta-value') == None:
                    raise LookupError('Rating not found')
                movie_data['rating'] = info.find('div', 'meta-value').string.encode('utf-8').split(' ')[0]
            
            if info_attr.string == 'Runtime: ':
                if info.find('time') == None:
                    raise LookupError('Length not found')
                movie_data['length'] = int(info.find('time').string.strip().split(' ')[0])
            
            if info_attr.string == 'Directed By: ':
                directors = info.find_all('a')
                if directors == []:
                    raise LookupError('Director not found')
                movie_data['director'] = [director.string.encode('utf-8') for director in directors]
            
            if info_attr.string == 'Genre: ':
                genres = info.find_all('a')
                if genres == []:
                    raise LookupError('Genres not found')
                movie_data['genre'] = [genre.string.encode('utf-8').strip() for genre in genres]
        return movie_data

    def get_RT_score(self):
        score_section = self.__response.find('span', 'meter-value superPageFontColor') 
        if score_section == None:
            raise LookupError('Score section not found')
        score = score_section.find('span')
        if score == None:
            raise LookupError('Score not found')
        return int(score.string)

    def get_synopsis(self):
        synopsis = self.__response.find(id='movieSynopsis')
        if synopsis == None:
            raise LookupError('Synopsis not found')
        return synopsis.string.encode('utf-8').strip()

    def get_img(self):
        img_url = self.__response.find('img', 'posterImage')
        if img_url == None:
            raise LookupError('Img url not found')
        if 'data-src' in img_url.attrs:
            return img_url['data-src'].encode('utf-8')
        tag = 'src'
        try:
            return img_url[tag].encode('utf-8')
        except:
            raise KeyError('Tag %s not found in %s' % (tag, img_url))  
