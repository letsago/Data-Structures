from server.views import movieSearch
import pytest

def createForm(data = {}):
    form = {'genre': '', 'rating': '', 'imdb': '', 'rottenTomatoes': '', 'length': '', 'cast': '', 'director': ''}
    for key in data:
        if key in form.keys():
            form[key] = data[key] 
    return form

@pytest.mark.parametrize('searchData, movieIds', [
    # invalid input
    ({'length': 'invalid'}, []), 
    ({'imdb': 'invalid'}, []), 
    ({'rottenTomatoes': 'invalid'}, []),
    
    # no input
    ({}, [1, 2, 3, 4, 5, 6, 7]),
    
    # single good input
    ({'imdb': 8.5}, [1, 3, 6]),
    ({'genre': 'Comedy'}, [2, 4, 5]),
    ({'director': 'Marc Webb'}, [2]),
    ({'cast': 'Miyu Irino'}, [3]),
    ({'rottenTomatoes': 90}, [1, 3, 4, 6]),
    ({'length': 120}, [2, 4, 5, 6, 7]),
    ({'rating': 'PG-13'}, [1, 2, 7]),

    # single bad input
    ({'imdb': 0.13}, [1, 2, 3, 4, 5, 6, 7]),
    ({'genre': 'coMEdy'}, [2, 4, 5]),
    ({'director': 'maRC WEbb'}, [2]),
    ({'cast': 'cHrIstIan bALe'}, [1, 5]),
    ({'rottenTomatoes': 201.45}, []),
    ({'length': -100.5}, []),
    ({'rating': 'pG-13'}, [1, 2, 7]),

    # multiple input
    ({'genre': 'Action & Adventure', 'rating': 'PG-13', 'imdb': -201.67, 'rottenTomatoes': 0, 'length': 180, 'cast': 'christian bale', 'director': 'christopher nolan'}, [1])
])

def test_search(searchData, movieIds):
    assert [movie['id'] for movie in movieSearch(createForm(searchData))] == movieIds


