from sqlalchemy import create_engine
from sqlalchemy.orm import scoped_session, sessionmaker
from sqlalchemy.ext.declarative import declarative_base
from server import app

# test database contains AMC showing info that needs to be updated every Wednesday - the day AMC updates their showings
engine = create_engine(app.config['DATABASE_URI'], convert_unicode=True)
db_session = scoped_session(sessionmaker(autocommit=False,
                                         autoflush=False,
                                         bind=engine))
Base = declarative_base()
Base.query = db_session.query_property()
Base.metadata.create_all(bind=engine)
                
def init_test_db():
    from server.database import db_session
    from server.models import Movie, Theater, Showing, User, Genre, Cast, Director

    Movie.query.delete()
    Theater.query.delete()
    Showing.query.delete()
    User.query.delete()
    Genre.query.delete()
    Cast.query.delete()
    Director.query.delete()

    movie_one = Movie(  
                        'https://www.rottentomatoes.com/m/the_dark_knight',
                        'https://www.imdb.com/title/tt0468569/', 
                        'The Dark Knight', 
                        'PG-13', 
                        152, 
                        'https://upload.wikimedia.org/wikipedia/en/8/8a/Dark_Knight.jpg',
                        9.0, 
                        94,
                        "Christopher Nolan steps back into the director's chair for this sequel to Batman Begins, which finds the titular superhero coming face to face with his greatest nemesis -- the dreaded Joker. Christian Bale returns to the role of Batman, Maggie Gyllenhaal takes over the role of Rachel Dawes (played by Katie Holmes in Batman Begins), and Brokeback Mountain star Heath Ledger dons the ghoulishly gleeful Joker makeup previously worn by Jack Nicholson and Cesar Romero. Just as it begins to appear as if Batman, Lt. James Gordon (Gary Oldman), and District Attorney Harvey Dent (Aaron Eckhart) are making headway in their tireless battle against the criminal element, a maniacal, wisecracking fiend plunges the streets of Gotham City into complete chaos. ~ Jason Buchanan, Rovi"
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
                        "Joseph Gordon-Levitt and Zooey Deschanel star in director Marc Webb's wry, nonlinear romantic comedy about a man who falls head over heels for a woman who doesn't believe in love. Tom (Gordon-Levitt) is an aspiring architect who currently earns his living as a greeting card writer. Upon encountering his boss' beautiful new secretary, Summer (Deschanel), Tom discovers that the pair have plenty in common despite the fact that she's seemingly out of his league; for starters, they both love the Smiths, and they're both fans of surrealist artist Magritte. Before long Tom is smitten. All he can think about is Summer. Tom believes deeply in the concept of soul mates, and he's finally found his. Unfortunately for Tom, Summer sees true love as the stuff of fairy tales, and isn't looking for romance. Undaunted and undeterred by his breezy lover's casual stance on relationships, Tom summons all of his might and courage to pursue Summer and convince her that their love is real. ~ Jason Buchanan, Rovi"
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
                        "Master animation director Hayao Miyazaki follows up on his record-breaking 1997 opus Princess Mononoke with this surreal Alice in Wonderland-like tale about a lost little girl. The film opens with ten-year-old Chihiro riding along during a family outing as her father races through remote country roads. When they come upon a blocked tunnel, her parents decide to have a look around -- even though Chihiro finds the place very creepy. When they pass through the tunnel, they discover an abandoned amusement park. As Chihiro's bad vibes continue, her parents discover an empty eatery that smells of fresh food. After her mother and father help themselves to some tasty purloined morsels, they turn into giant pigs. Chihiro understandably freaks out and flees. She learns that this very weird place, where all sorts of bizarre gods and monsters reside, is a holiday resort for the supernatural after their exhausting tour of duty in the human world. Soon after befriending a boy named Haku, Chihiro learns the rules of the land: one, she must work , as laziness of any kind is not tolerated; and two, she must take on the new moniker of Sen. If she forgets her real name, Haku tells her, then she will never be permitted to leave. ~ Jonathan Crow, Rovi"
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
                        "THE GRAND BUDAPEST HOTEL recounts the adventures of Gustave H, a legendary concierge at a famous European hotel between the wars, and Zero Moustafa, the lobby boy who becomes his most trusted friend. The story involves the theft and recovery of a priceless Renaissance painting and the battle for an enormous family fortune -- all against the back-drop ofa suddenly and dramatically changing Continent. (c) Fox Searchlight"
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
                        "Patrick Bateman is young, white, beautiful, ivy leagued, and indistinguishable from his Wall Street colleagues. Shielded by conformity, privilege, and wealth, Bateman is also the ultimate serial killer, roaming freely and fearlessly. His murderous impulses are fueled by zealous materialism and piercing envy when he discovers someone else has acquired more than he has. After a colleague presents a business card superior in ink and paper to his, Bateman's blood thirst sharpens, and he steps up his homicidal activities to a frenzied pitch. Hatchets fly, butcher knives chop, chainsaws rip, and surgical instruments mutilate-how far will Bateman go? How much can he get away with?"
                    )

    movie_six = Movie(  
                        'https://www.rottentomatoes.com/m/spider_man_into_the_spider_verse',
                        'https://www.imdb.com/title/tt4633694/', 
                        'Spider-Man: Into The Spider-Verse', 
                        'PG', 
                        100, 
                        'https://resizing.flixster.com/t-ysR8YcSH2cvSA6fhn2qxDY67I=/206x305/v1.bTsxMjg3MjM1MDtqOzE3OTY4OzEyMDA7NjA3Mjs5MDAw',
                        8.7, 
                        97, 
                        "Phil Lord and Christopher Miller, the creative minds behind The Lego Movie and 21 Jump Street, bring their unique talents to a fresh vision of a different Spider-Man Universe, with a groundbreaking visual style that's the first of its kind. Spider-Man: Into the Spider-Verse introduces Brooklyn teen Miles Morales, and the limitless possibilities of the Spider-Verse, where more than one can wear the mask."
                    )

    movie_seven = Movie(
                        'https://www.rottentomatoes.com/m/glass_2019',
                        'https://www.imdb.com/title/tt6823368/',  
                        'Glass', 
                        'PG-13', 
                        110,
                        'https://resizing.flixster.com/KrOv5ONpHt5bnI8UOQgEP3hjJUI=/206x305/v1.bTsxMjc4MDk3NjtqOzE3OTY3OzEyMDA7NzkwOzEyNTE', 
                        7.1, 
                        36, 
                        "From Unbreakable, Bruce Willis returns as David Dunn as does Samuel L. Jackson as Elijah Price, known also by his pseudonym Mr. Glass. Joining from Split are James McAvoy, reprising his role as Kevin Wendell Crumb and the multiple identities who reside within, and Anya Taylor-Joy as Casey Cooke, the only captive to survive an encounter with The Beast. Following the conclusion of Split, Glass finds Dunn pursuing Crumb's superhuman figure of The Beast in a series of escalating encounters, while the shadowy presence of Price emerges as an orchestrator who holds secrets critical to both men."
                    )

    theater_one = Theater('https://www.amctheatres.com/movie-theatres/seattle-tacoma/amc-pacific-place-11', 'AMC Pacific Place 11', '600 Pine Street - Ste 400', 'Seattle', 'Washington', 98101)
    theater_two = Theater('https://www.amctheatres.com/movie-theatres/seattle-tacoma/amc-oak-tree-6', 'AMC Oak Tree 6', '10006 Aurora Avenue N.', 'Seattle', 'Washington', 98133)
    theater_three = Theater('https://www.amctheatres.com/movie-theatres/seattle-tacoma/amc-seattle-10', 'AMC Seattle 10', '4500 9th Ave Ne', 'Seattle', 'Washington', 98105)
    user_one = User('admin', 'admin@admin.com', 'admin')
    db_session.add_all([movie_one, movie_two, movie_three, movie_four, movie_five, movie_six, movie_seven, theater_one, theater_two, theater_three, user_one])
    db_session.commit()
    db_session.add_all([
        Genre(movie_one.id, 'Action & Adventure'),
        Genre(movie_one.id, 'Drama'),
        Genre(movie_one.id, 'Science Fiction & Fantasy'),
        Cast(movie_one.id, 'Christian Bale'),
        Cast(movie_one.id, 'Heath Ledger'),
        Cast(movie_one.id, 'Aaron Eckhart'),
        Cast(movie_one.id, 'Maggie Gyllenhaal'),
        Cast(movie_one.id, 'Gary Oldman'),
        Cast(movie_one.id, 'Morgan Freeman'),
        Director(movie_one.id, 'Christopher Nolan'),

        Genre(movie_two.id, 'Comedy'),
        Genre(movie_two.id, 'Drama'),
        Genre(movie_two.id, 'Romance'),
        Cast(movie_two.id, 'Joseph Gordon-Levitt'),
        Cast(movie_two.id, 'Zooey Deschanel'),
        Cast(movie_two.id, 'Geoffrey Arend'),
        Cast(movie_two.id, 'Chloe Grace Moretz'),
        Cast(movie_two.id, 'Matthew Gray Gubler'),
        Cast(movie_two.id, 'Clark Gregg'),
        Director(movie_two.id, 'Marc Webb'),

        Genre(movie_three.id, 'Animation'),
        Genre(movie_three.id, 'Drama'),
        Genre(movie_three.id, 'Kids & Family'),
        Genre(movie_three.id, 'Science Fiction & Fantasy'),
        Cast(movie_three.id, 'Rumi Hiiragi'),
        Cast(movie_three.id, 'Miyu Irino'),
        Cast(movie_three.id, 'Mari Natsuki'),
        Cast(movie_three.id, 'Takashi Naito'),
        Cast(movie_three.id, 'Yasuko Sawaguchi'),
        Cast(movie_three.id, 'Tsunehiko Kamijo'),
        Director(movie_three.id, 'Hayao Miyazaki'),

        Genre(movie_four.id, 'Comedy'),
        Genre(movie_four.id, 'Drama'),
        Cast(movie_four.id, 'Ralph Fiennes'),
        Cast(movie_four.id, 'Tony Revolori'),
        Cast(movie_four.id, 'F. Murray Abraham'),
        Cast(movie_four.id, 'Edward Norton'),
        Cast(movie_four.id, 'Saoirse Ronan'),
        Cast(movie_four.id, 'Tilda Swinton'),
        Director(movie_four.id, 'Wes Anderson'),

        Genre(movie_five.id, 'Comedy'),
        Genre(movie_five.id, 'Drama'),
        Genre(movie_five.id, 'Horror'),
        Genre(movie_five.id, 'Mystery & Suspense'),
        Cast(movie_five.id, 'Christian Bale'),
        Cast(movie_five.id, 'Willem Dafoe'),
        Cast(movie_five.id, 'Jared Leto'),
        Cast(movie_five.id, 'Josh Lucas'),
        Cast(movie_five.id, 'Samantha Mathis'),
        Cast(movie_five.id, 'Chloe Sevigny'),
        Director(movie_five.id, 'Mary Harron'),

        Genre(movie_six.id, 'Action & Adventure'),
        Genre(movie_six.id, 'Animation'),
        Genre(movie_six.id, 'Kids & Family'),
        Genre(movie_six.id, 'Science Fiction & Fantasy'),
        Cast(movie_six.id, 'Shameik Moore'),
        Cast(movie_six.id, 'Jake Johnson'),
        Cast(movie_six.id, 'Hailee Steinfeld'),
        Cast(movie_six.id, 'Mahershala Ali'),
        Cast(movie_six.id, 'Brian Tyree Henry'),
        Cast(movie_six.id, 'Lily Tomlin'),
        Director(movie_six.id, 'Bob Persichetti'),
        Director(movie_six.id, 'Peter Ramsey'),
        Director(movie_six.id, 'Rodney Rothman'),

        Genre(movie_seven.id, 'Drama'),
        Genre(movie_seven.id, 'Mystery & Suspense'),
        Cast(movie_seven.id, 'Bruce Willis'),
        Cast(movie_seven.id, 'James McAvoy'),
        Cast(movie_seven.id, 'Samuel L. Jackson'),
        Cast(movie_seven.id, 'Sarah Paulson'),
        Cast(movie_seven.id, 'Anya Taylor-Joy'),
        Cast(movie_seven.id, 'Spencer Treat Clark'),
        Director(movie_seven.id, 'M. Night Shyamalan'),

        Showing(movie_six.id, theater_one.id, '2019-01-30', '10:45am'),
        Showing(movie_six.id, theater_one.id, '2019-01-30', '1:30pm'),
        Showing(movie_six.id, theater_one.id, '2019-01-30', '4:35pm'),
        Showing(movie_six.id, theater_one.id, '2019-01-30', '7:50pm'),

        Showing(movie_seven.id, theater_one.id, '2019-01-30', '10:55am'),
        Showing(movie_seven.id, theater_one.id, '2019-01-30', '1:35pm'),
        Showing(movie_seven.id, theater_one.id, '2019-01-30', '4:50pm'),
        Showing(movie_seven.id, theater_one.id, '2019-01-30', '7:30pm'),

        Showing(movie_six.id, theater_two.id, '2019-01-30', '10:45am'),
        Showing(movie_six.id, theater_two.id, '2019-01-30', '1:40pm'),
        Showing(movie_six.id, theater_two.id, '2019-01-30', '4:30pm'),
        Showing(movie_six.id, theater_two.id, '2019-01-30', '7:30pm'),

        Showing(movie_seven.id, theater_two.id, '2019-01-30', '11:10am'),
        Showing(movie_seven.id, theater_two.id, '2019-01-30', '2:45pm'),
        Showing(movie_seven.id, theater_two.id, '2019-01-30', '5:45pm'),
        Showing(movie_seven.id, theater_two.id, '2019-01-30', '8:45pm'),

        Showing(movie_six.id, theater_three.id, '2019-01-30', '1:55pm'),
        Showing(movie_six.id, theater_three.id, '2019-01-30', '4:40pm'),
        Showing(movie_six.id, theater_three.id, '2019-01-30', '5:10pm'),
        Showing(movie_six.id, theater_three.id, '2019-01-30', '8:15pm'),

        Showing(movie_seven.id, theater_three.id, '2019-01-30', '1:50pm'),
        Showing(movie_seven.id, theater_three.id, '2019-01-30', '4:50pm'),
        Showing(movie_seven.id, theater_three.id, '2019-01-30', '8:00pm')
    ])
    db_session.commit()
