from common import get_response

class AMCTheaters:
    def __init__(self, url):
        self.__url = url
    
    @staticmethod
    def extract_formatted_addr(address_section):
        # AMC address format is 'street, city, state zipCode'
        # because commas exist in streets, negative indices are used to extract city, state zipCode
        formatted_addr = {}
        address_section = address_section.split(',')
        formatted_addr['street'] = address_section[0]
        formatted_addr['city'] = address_section[-2].strip()        
        formatted_addr['zipCode'] = int(address_section[-1][-5:])
        formatted_addr['state'] = address_section[-1][:-5].strip()
        return formatted_addr

    def get_theater_info(self):
        # contains theater name, street, city, state, and zip code info
        # returns None if theater_info doesn't exist
        response = get_response(self.__url)
        theater_section = response.find('h1', itemprop='name')
        if theater_section == None:
            return None
        address_section = response.find('p', 'Headline--sub')
        if address_section == None: 
            return None
        theater_info = {}        
        theater_info['url'] = self.__url
        theater_info['name'] = theater_section.string.encode('utf-8').strip()
        formatted_addr = AMCTheaters.extract_formatted_addr(address_section.string.encode('utf-8'))
        theater_info.update(formatted_addr)
        return theater_info
    
