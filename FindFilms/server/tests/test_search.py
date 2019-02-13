from server.views import movieSearch, showingSearch
import pytest

def createForm(data = {}):
    form = {'date': '', 'city': '', 'genre': '', 'rating': '', 'imdb': '', 'rottenTomatoes': '', 'length': '', 'cast': '', 'director': ''}
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
    ({'genre': 'coMEdy '}, [2, 4, 5]),
    ({'director': '  maRC  WEbb'}, [2]),
    ({'cast': 'cHrIstIan  bALe '}, [1, 5]),
    ({'rottenTomatoes': 201.45}, []),
    ({'length': -100.5}, []),
    ({'rating': ' pG-13 '}, [1, 2, 6]),

    # multiple input
    ({'genre': 'Action & Adventure', 'rating': 'PG-13', 'imdb': -201.67, 'rottenTomatoes': 0, 'length': 180, 'cast': 'christian bale', 'director': 'christopher nolan'}, [1])
])

def test_movieSearch(movieSearchData, movieIds):
    assert [movie['id'] for movie in movieSearch(createForm(movieSearchData))] == movieIds

@pytest.mark.parametrize('goodShowingSearchInput, showingTimes', [    
    # well formatted input with standard date type format which is also date input format for Jade
    ({'date': '2019-02-13', 'city': 'Seattle'}, [['7:00pm', '9:55pm'], ['7:00pm', '9:15pm'], ['7:00pm']]),
    ({'date': '2019-02-14', 'city': 'Seattle'}, [['4:30pm', '7:20pm', '10:10pm']]),

    # bad formatted city input
    ({'date': '2019-02-14', 'city': 'SEaTtlE'}, [['4:30pm', '7:20pm', '10:10pm']]),
    ({'date': '2019-02-14', 'city': ' seattle '}, [['4:30pm', '7:20pm', '10:10pm']])
])

def test_validShowingsSearch(goodShowingSearchInput, showingTimes):
    # since test db only has showing for Alita Battle Angel movie, there should only be one targetShowing
    targetShowings = showingSearch(createForm(goodShowingSearchInput))
    assert len(targetShowings) == 1
    for i in range(len(showingTimes)):
        assert targetShowings[0]['theaterShowings'][i]['times'] == showingTimes[i]

@pytest.mark.parametrize('badShowingSearchInput', [    
    # no date input
    ({'date': '', 'city': 'Seattle'}),

    # no city input
    ({'date': '2019-02-14', 'city': ''}),

    # bad formatted date input
    ({'date': '2/13/19', 'city': 'Seattle'}),

    # valid date input with no showings
    ({'date': '2019-02-15', 'city': 'Seattle'}),

    # valid city input with no showings
    ({'date': '2019-02-14', 'city': 'Chicago'})
])

def test_noShowingsSearch(badShowingSearchInput):
    theaterShowings = showingSearch(createForm(badShowingSearchInput))
    assert theaterShowings == []




