from app import movieSearch

def createForm(data = {}):
    form = {'genre': '', 'rating': '', 'imdb': '', 'rottenTomatoes': '', 'length': '', 'cast': '', 'director': ''}
    for key in data:
        if key in form.keys():
            form[key] = data[key] 
    return form

def test_search():
    formData1 = createForm({'imdb': 8.5})
    formData2 = createForm()
    formData3 = createForm({'genre': 'coMEdy'})
    formData4 = createForm({'director': 'maRC WEbb'})
    formData5 = createForm({'cast': 'mIYu iRiNo'})
    formData6 = createForm({'rottenTomatoes': 9})
    formData7 = createForm({'length': -100.5})
    formData8 = createForm({'rating': 'pG-13'})
    formData9 = createForm({'genre': 'thRiLLer', 'rating': 'PG-13', 'imdb': -201.67, 'rottenTomatoes': 0, 'length': 150, 'cast': 'christian bale', 'director': 'christopher nolan'})
    formData10 = createForm({'imdb': 'invalid'})
    formData11 = createForm({'rottenTomatoes': 'invalid'})
    formData12 = createForm({'length': 'invalid'})
    assert [movie['id'] for movie in movieSearch(formData1)] == [0, 2]
    assert [movie['id'] for movie in movieSearch(formData2)] == [0, 1, 2, 3]
    assert [movie['id'] for movie in movieSearch(formData3)] == [3]
    assert [movie['id'] for movie in movieSearch(formData4)] == [1]
    assert [movie['id'] for movie in movieSearch(formData5)] == [2]
    assert [movie['id'] for movie in movieSearch(formData6)] == [0, 2, 3]
    assert [movie['id'] for movie in movieSearch(formData7)] == []
    assert [movie['id'] for movie in movieSearch(formData8)] == [0, 1]
    assert [movie['id'] for movie in movieSearch(formData9)] == [0]
    assert [movie['id'] for movie in movieSearch(formData10)] == []
    assert [movie['id'] for movie in movieSearch(formData11)] == []
    assert [movie['id'] for movie in movieSearch(formData12)] == []
