from server.views import movieSearch, showingSearch
import pytest

def createForm(data = {}):
    form = {'date': '', 'genre': '', 'rating': '', 'imdb': '', 'rottenTomatoes': '', 'length': '', 'cast': '', 'director': ''}
    for key in data:
        if key in form.keys():
            form[key] = data[key] 
    return form

@pytest.mark.parametrize('movieSearchData, movieIds', [
    # invalid input
    ({'length': 'invalid'}, []), 
    ({'imdb': 'invalid'}, []), 
    ({'rottenTomatoes': 'invalid'}, []),
    
    # no input
    ({}, [1, 2, 3, 4, 5, 6]),
    
    # single good input
    ({'imdb': 8.5}, [1, 3]),
    ({'genre': 'Comedy'}, [2, 4, 5]),
    ({'director': 'Marc Webb'}, [2]),
    ({'cast': 'Miyu Irino'}, [3]),
    ({'rottenTomatoes': 90}, [1, 3, 4]),
    ({'length': 120}, [2, 4, 5]),
    ({'rating': 'PG-13'}, [1, 2, 6]),

    # single bad input
    ({'imdb': 0.13}, [1, 2, 3, 4, 5, 6]),
    ({'genre': 'coMEdy'}, [2, 4, 5]),
    ({'director': 'maRC WEbb'}, [2]),
    ({'cast': 'cHrIstIan bALe'}, [1, 5]),
    ({'rottenTomatoes': 201.45}, []),
    ({'length': -100.5}, []),
    ({'rating': 'pG-13'}, [1, 2, 6]),

    # multiple input
    ({'genre': 'Action & Adventure', 'rating': 'PG-13', 'imdb': -201.67, 'rottenTomatoes': 0, 'length': 180, 'cast': 'christian bale', 'director': 'christopher nolan'}, [1])
])

def test_movieSearch(movieSearchData, movieIds):
    assert [movie['id'] for movie in movieSearch(createForm(movieSearchData))] == movieIds

@pytest.mark.parametrize('date, showingTimes', [    
    # well formatted input - this format is standard date type format which is also date input format for Jade
    ('2019-02-13', [['7:00pm', '9:55pm'], ['7:00pm', '9:15pm'], ['7:00pm']]),
    ('2019-02-14', [['4:30pm', '7:20pm', '10:10pm']])
])

def test_validShowingsSearch(date, showingTimes):
    # showingSearch currently returns all showings for theaters 1-3
    # since test db only has showing for Alita Battle Angel movie, there should only be one targetShowing
    targetShowings = showingSearch(createForm({'date': date}))
    assert len(targetShowings) == 1
    for i in range(len(showingTimes)):
        assert targetShowings[0]['theaterShowings'][i]['times'] == showingTimes[i]

@pytest.mark.parametrize('date', [    
    # no date input
    (''),

    # bad formatted date input
    ('2/13/19'),

    # valid date input with no showings
    ('2019-02-15')
])

def test_noShowingsSearch(date):
    theaterShowings = showingSearch(createForm({'date': date}))
    assert theaterShowings == []




