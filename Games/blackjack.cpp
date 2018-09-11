#include <iostream>
#include <array>
using namespace std;

enum Rank
{
    RANK_2,
    RANK_3,
    RANK_4,
    RANK_5,
    RANK_6,
    RANK_7,
    RANK_8,
    RANK_9,
    RANK_10,
    RANK_JACK,
    RANK_QUEEN,
    RANK_KING,
    RANK_ACE,
    MAX_RANKS
};

enum Suit
{
    SUIT_CLUBS,
    SUIT_DIAMONDS,
    SUIT_HEARTS,
    SUIT_SPADES,
    MAX_SUITS
};

struct Card
{
    Rank rank;
    Suit suit;
};

void printCard(const Card &card)
{
    switch (card.rank)
	{
		case RANK_2:		cout << '2'; break;
		case RANK_3:		cout << '3'; break;
		case RANK_4:		cout << '4'; break;
		case RANK_5:		cout << '5'; break;
		case RANK_6:		cout << '6'; break;
		case RANK_7:		cout << '7'; break;
		case RANK_8:		cout << '8'; break;
		case RANK_9:		cout << '9'; break;
		case RANK_10:		cout << 'T'; break;
		case RANK_JACK:		cout << 'J'; break;
		case RANK_QUEEN:	cout << 'Q'; break;
		case RANK_KING:		cout << 'K'; break;
		case RANK_ACE:		cout << 'A'; break;
	}
 
	switch (card.suit)
	{
		case SUIT_CLUBS:	cout << 'C'; break;
		case SUIT_DIAMONDS:	cout << 'D'; break;
		case SUIT_HEARTS:	cout << 'H'; break;
		case SUIT_SPADES:	cout << 'S'; break;
	}
}

void printDeck(const array<Card, 52> &deck)
{
    for (auto &card : deck)
    {
        printCard(card);
        cout << " ";
    }

    cout << endl;
}

int main()
{
    array<Card, 52> deck;

    int card = 0;

    for (int rank = 0; rank < MAX_RANKS; rank++)
    for (int suit = 0; suit < MAX_SUITS; suit++)
    {
        deck[card].rank = static_cast<Rank>(rank);
        deck[card].suit = static_cast<Suit>(suit);
        card++;
    }

    printDeck(deck);

    return 0;
}