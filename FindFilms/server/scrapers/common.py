from bs4 import BeautifulSoup
import requests

def get_response(url):
    maxAttempts = 3
    attemptNum = 0
    response = requests.get(url)
    while response.status_code != 200 and attemptNum < maxAttempts:
        response = requests.get(url)
        attemptNum += 1
    if attemptNum == maxAttempts:
        raise requests.ConnectionError('%s not found' % (url))
    return BeautifulSoup(response.content, 'html.parser')
