from sqlalchemy import create_engine
from sqlalchemy.orm import scoped_session, sessionmaker
from sqlalchemy.ext.declarative import declarative_base

hostname = ''
path = 'findFilmsTest.db'
engine = create_engine('sqlite://%s/%s' % (hostname, path), convert_unicode=True)
db_session = scoped_session(sessionmaker(autocommit=False,
                                         autoflush=False,
                                         bind=engine))
Base = declarative_base()
Base.query = db_session.query_property()


def init_db():
    from server.database import db_session
    from server.models import Movie, Theater, Showing, User
    Base.metadata.create_all(bind=engine)

    Movie.query.delete()
    Theater.query.delete()
    Showing.query.delete()
    User.query.delete()

    movie_one = Movie(  
                        'https://www.rottentomatoes.com/m/the_dark_knight', 
                        'https://www.imdb.com/title/tt0468569/', 
                        'The Dark Knight', 
                        'PG-13', 
                        152, 
                        'https://upload.wikimedia.org/wikipedia/en/8/8a/Dark_Knight.jpg',
                        9.0, 
                        94, 
                        'Action & Adventure', 
                        'Christian Bale', 
                        'Christopher Nolan',
                        "Christopher Nolan steps back into the director's chair for this sequel to Batman Begins, which finds the titular superhero coming face to face with his greatest nemesis -- the dreaded Joker. Christian Bale returns to the role of Batman, Maggie Gyllenhaal takes over the role of Rachel Dawes (played by Katie Holmes in Batman Begins), and Brokeback Mountain star Heath Ledger dons the ghoulishly gleeful Joker makeup previously worn by Jack Nicholson and Cesar Romero. Just as it begins to appear as if Batman, Lt. James Gordon (Gary Oldman), and District Attorney Harvey Dent (Aaron Eckhart) are making headway in their tireless battle against the criminal element, a maniacal, wisecracking fiend plunges the streets of Gotham City into complete chaos. ~ Jason Buchanan, Rovi", 
                        'Heath Ledger', 
                        'Aaron Eckhart',
                        'Maggie Gyllenhaal',
                        'Gary Oldman',
                        'Morgan Freeman',
                        'Drama',
                        'Science Fiction & Fantasy'
                    )
    movie_two = Movie(  
                        'https://www.rottentomatoes.com/m/500_days_of_summer',
                        'https://www.imdb.com/title/tt1022603/', 
                        '500 Days of Summer', 
                        'PG-13', 
                        95,
                        'https://upload.wikimedia.org/wikipedia/en/d/d1/Five_hundred_days_of_summer.jpg', 
                        7.7, 
                        85, 
                        'Comedy', 
                        'Joseph Gordon-Levitt', 
                        'Marc Webb',
                        "Joseph Gordon-Levitt and Zooey Deschanel star in director Marc Webb's wry, nonlinear romantic comedy about a man who falls head over heels for a woman who doesn't believe in love. Tom (Gordon-Levitt) is an aspiring architect who currently earns his living as a greeting card writer. Upon encountering his boss' beautiful new secretary, Summer (Deschanel), Tom discovers that the pair have plenty in common despite the fact that she's seemingly out of his league; for starters, they both love the Smiths, and they're both fans of surrealist artist Magritte. Before long Tom is smitten. All he can think about is Summer. Tom believes deeply in the concept of soul mates, and he's finally found his. Unfortunately for Tom, Summer sees true love as the stuff of fairy tales, and isn't looking for romance. Undaunted and undeterred by his breezy lover's casual stance on relationships, Tom summons all of his might and courage to pursue Summer and convince her that their love is real. ~ Jason Buchanan, Rovi", 
                        'Zooey Deschanel',
                        'Geoffrey Arend',
                        'Chloe Grace Moretz',
                        'Matthew Gray Gubler',
                        'Clark Gregg',
                        'Drama',
                        'Romance'
                    )
    movie_three = Movie(    
                        'https://www.rottentomatoes.com/m/spirited_away',
                        'https://www.imdb.com/title/tt0245429/', 
                        'Spirited Away', 
                        'PG', 
                        124,
                        'https://upload.wikimedia.org/wikipedia/en/d/db/Spirited_Away_Japanese_poster.png', 
                        8.6, 
                        97, 
                        'Animation', 
                        'Rumi Hiiragi', 
                        'Hayao Miyazaki',
                        "Master animation director Hayao Miyazaki follows up on his record-breaking 1997 opus Princess Mononoke with this surreal Alice in Wonderland-like tale about a lost little girl. The film opens with ten-year-old Chihiro riding along during a family outing as her father races through remote country roads. When they come upon a blocked tunnel, her parents decide to have a look around -- even though Chihiro finds the place very creepy. When they pass through the tunnel, they discover an abandoned amusement park. As Chihiro's bad vibes continue, her parents discover an empty eatery that smells of fresh food. After her mother and father help themselves to some tasty purloined morsels, they turn into giant pigs. Chihiro understandably freaks out and flees. She learns that this very weird place, where all sorts of bizarre gods and monsters reside, is a holiday resort for the supernatural after their exhausting tour of duty in the human world. Soon after befriending a boy named Haku, Chihiro learns the rules of the land: one, she must work , as laziness of any kind is not tolerated; and two, she must take on the new moniker of Sen. If she forgets her real name, Haku tells her, then she will never be permitted to leave. ~ Jonathan Crow, Rovi", 
                        'Miyu Irino',
                        'Mari Natsuki',
                        'Takashi Naito',
                        'Yasuko Sawaguchi',
                        'Tsunehiko Kamijo',
                        'Drama',
                        'Kids & Family',
                        'Science Fiction & Fantasy'
                    )
    movie_four = Movie(
                        'https://www.rottentomatoes.com/m/the_grand_budapest_hotel',
                        'https://www.imdb.com/title/tt2278388/', 
                        'The Grand Budapest Hotel', 
                        'R', 
                        99,
                        'https://upload.wikimedia.org/wikipedia/en/1/1c/The_Grand_Budapest_Hotel.png', 
                        8.1, 
                        91, 
                        'Comedy', 
                        'Ralph Fiennes', 
                        'Wes Anderson',
                        "THE GRAND BUDAPEST HOTEL recounts the adventures of Gustave H, a legendary concierge at a famous European hotel between the wars, and Zero Moustafa, the lobby boy who becomes his most trusted friend. The story involves the theft and recovery of a priceless Renaissance painting and the battle for an enormous family fortune -- all against the back-drop ofa suddenly and dramatically changing Continent. (c) Fox Searchlight", 
                        'Tony Revolori',
                        'F. Murray Abraham', 
                        'Edward Norton',
                        'Saoirse Ronan',
                        'Tilda Swinton',
                        'Drama'
                    )
    movie_five = Movie(
                        'https://www.rottentomatoes.com/m/american_psycho',
                        'https://www.imdb.com/title/tt0144084/', 
                        'American Psycho',
                        'R', 
                        97,
                        'https://upload.wikimedia.org/wikipedia/en/0/0c/American_Psycho.png', 
                        7.6, 
                        68, 
                        'Comedy', 
                        'Christian Bale', 
                        'Mary Harron', 
                        "Patrick Bateman is young, white, beautiful, ivy leagued, and indistinguishable from his Wall Street colleagues. Shielded by conformity, privilege, and wealth, Bateman is also the ultimate serial killer, roaming freely and fearlessly. His murderous impulses are fueled by zealous materialism and piercing envy when he discovers someone else has acquired more than he has. After a colleague presents a business card superior in ink and paper to his, Bateman's blood thirst sharpens, and he steps up his homicidal activities to a frenzied pitch. Hatchets fly, butcher knives chop, chainsaws rip, and surgical instruments mutilate-how far will Bateman go? How much can he get away with?",
                        'Willem Dafoe', 
                        'Jared Leto',
                        'Josh Lucas',
                        'Samantha Mathis',
                        'Chloe Sevigny',
                        'Drama',
                        'Horror',
                        'Mystery & Suspense'
                    )
    theater_one = Theater('AMC', '101 Main St.')
    theater_two = Theater('Regal', '1 Hallow Rd.')
    theater_three = Theater('Cinemark', '8 Haku Blvd.')
    user_one = User('admin', 'admin@admin.com', 'admin')
    db_session.add_all([movie_one, movie_two, movie_three, movie_four, movie_five, theater_one, theater_two, theater_three, user_one])
    db_session.commit()

    db_session.add_all([
        Showing(movie_one.id, theater_one.id, '2013-01-02', '7:00 pm', '$7.00', 5, '9:00 pm', '11:00 pm'),
        Showing(movie_two.id, theater_two.id, '2013-04-06', '5:00 pm', '$8.00', 2),
        Showing(movie_three.id, theater_three.id, '2013-05-09', '7:00 pm', '$6.00', 8, '8:30 pm')])
    db_session.commit()

