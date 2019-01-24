from bs4 import BeautifulSoup
import requests

def get_response(url):
    response = requests.get(url)
    if response.status_code != 200:
        raise ConnectionError('%s not found' % (url))
    return BeautifulSoup(response.content, 'html.parser')
