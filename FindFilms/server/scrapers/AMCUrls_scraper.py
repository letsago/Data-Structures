from common import get_response

# AMCUrls class scrapes through AMC website to find all existing AMC theater urls in US 
class AMCUrls:
    def __init__(self):
        self.__base_url = 'https://www.amctheatres.com'
        self.__location_urls = self.get_location_urls()
    
    def get_location_urls(self):
        response = get_response(self.__base_url + '/movie-theatres')
        location_section = response.find('div', 'u-margin-top-30 container-fluid')
        if location_section == None:
            raise LookupError('AMC theater location section not found')
        locations = location_section.find_all('a', 'Link Link--arrow Link--reversed Link--arrow--txt--tiny txt--tiny')
        if locations == []:
            raise LookupError('AMC Locations not found')
        # supposed to return a list of all location urls but will only grab seattle area location url for now
        location_urls = []
        tag = 'href'
        for location in locations:
            try:
                if location[tag] == '/movie-theatres/seattle-tacoma':
                    location_urls.append(self.__base_url + location[tag].encode('utf-8'))
            except:
                raise KeyError('Tag %s not found in %s' % (tag, location))
        return location_urls
    
    def get_theater_urls(self):
        theater_urls = set()
        tag = 'href'
        for location_url in self.__location_urls:
            response = get_response(location_url)
            all_theaters_info = response.find_all('div', 'TheatreInfo')
            if all_theaters_info == []:
                raise LookupError('AMC theater info not found')
            for theater_info in all_theaters_info:
                theater_url_section = theater_info.find('a', 'Link')
                if theater_url_section == None:
                    raise LookupError('AMC theater url section not found')
                try:
                    theater_urls.add(self.__base_url + theater_url_section[tag].encode('utf-8'))
                except:
                    raise KeyError('Tag %s not found in %s' % (tag, theater_url_section))  
        return theater_urls



