#include <iostream>
#include <cstdlib> // for std::rand() and std::srand()
#include <ctime> // for std::time()
using namespace std;

// program picks a random integer between 1 and 100
// user guesses number
// program tells user too high, too low, or just right
// user has at most 7 guesses
// user wins if they guess correctly by 7 guesses, loses if 7 guesses are all up
// if user loses, program outputs correct number
// program asks user to play again, user must enter 'y' or 'n', otherwise program asks again

int getRandomNumber(int min, int max)
{
    static const double fraction = 1.0 / (RAND_MAX + 1.0);  // static used for efficiency, so we only calculate this value once
    // evenly distribute the random number across our range
    return min + static_cast<int>((max - min + 1) * (std::rand() * fraction));
}

int evaluate(int guess, int actual)
{
    if (guess > actual)
        return 1;
    else if (guess < actual)
        return -1;
    else
        return 0;
}

void printEvaluation(int evaluation)
{
    if (evaluation == 1)
        cout << "Your guess is too high" << endl;
    else if (evaluation == -1)
        cout << "Your guess is too low" << endl;
    else
        cout << "Your guess is correct" << endl;
}

char getResponse()
{
    char response;
    do
    {
        cout << "Press 'y' to play again, press 'n' to exit: ";
        cin >> response;
    } while (response != 'y' && response != 'n');

    return response;
}

int main()
{
    const int num_guesses = 7;
    char response;
    do
    {
        std::srand(static_cast<unsigned int>(std::time(0))); // set initial seed value to system clock
        int actual;
        actual = getRandomNumber(1, 100);
        cout << "Try to guess what number between 1 and 100 inclusive I'm thinking of." << endl;
        cout << "You have " << num_guesses << " guesses." << endl;
        int guess_count = 1;
        int evaluation;
        while (guess_count <= num_guesses)
        {
            cout << "Enter your guess: ";
            int guess;
            cin >> guess;
            evaluation = evaluate(guess, actual);
            printEvaluation(evaluation);
            if (evaluation == 0)
                {
                    cout << "Congrats! You win!" << endl;
                    break;
                }
            ++guess_count;
        }
        if (evaluation != 0)
            cout << "Sorry, the number I was thinking of was " << actual << endl;
        if (evaluation == 0)
            cout << "You used " << guess_count << " of " << num_guesses << " total guesses." << endl;
        response = getResponse();

    } while (response != 'n');

    return 0;
}