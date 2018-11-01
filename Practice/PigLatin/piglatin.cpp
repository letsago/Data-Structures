#include "piglatin.h"

using namespace pyu;

bool isAlphabet(const char entry)
{
    // - and ' are treated as valid characters using same rules as Lingojam's piglatin translator found online
    if((entry >= 'a' && entry <= 'z') || (entry >= 'A' && entry <= 'Z') || entry == '\'' || entry == '-')
        return true;
    else
        return false;
}

bool isVowel(const char entry)
{
    char lower_entry = tolower(entry);

    // - is treated as a vowel using same rules as Lingojam's piglatin translator found online
    if(lower_entry == 'a' || lower_entry == 'e' || lower_entry == 'i' || lower_entry == 'o' || lower_entry == 'u' ||
       lower_entry == '-')
        return true;

    return false;
}

bool isPunctuation(const char entry)
{
    if(entry == '.' || entry == '?' || entry == '!' || entry == ',')
        return true;

    return false;
}

bool doInvalidCharsExist(const Vector<char>& input)
{
    for(uint32_t i = 0; i < input.length(); ++i)
    {
        if(!((input.at(i) >= 'a' && input.at(i) <= 'z') || (input.at(i) >= 'A' && input.at(i) <= 'Z') ||
             (input.at(i) == '-') || (input.at(i) == '\'') || (input.at(i) == '.') || (input.at(i) == '?') ||
             (input.at(i) == '!') || (input.at(i) == ',') || (input.at(i) == '\0') || input.at(i) == ' '))
            return true;
    }

    return false;
}

bool pigLatinTranslate(const Vector<char>& input, Vector<char>& output)
{
    if(doInvalidCharsExist(input))
        return false;

    // handles null case
    if(input.length() == 0)
        return false;

    int input_position = 0;
    bool isFirstLetterVowel = isVowel(input.at(0));
    bool isFirstLetterCapital = isupper(input.at(0));

    // loops until end of input string
    while(input.at(input_position) != '\0')
    {
        // three distinct cases: first letter of word is vowel, first letter of word is not vowel and not capital,
        // first letter of word is not vowel yet capital
        if(isFirstLetterVowel)
        {
            while(isAlphabet(input.at(input_position)))
            {
                output.insert_back((input.at(input_position)));
                ++input_position;
            }

            output.insert_back('y');
            output.insert_back('a');
            output.insert_back('y');

            // this loop adds all punctuation at end of word until the next space
            while(isPunctuation(input.at(input_position)))
            {
                output.insert_back(input.at(input_position));
                ++input_position;
            }
        }
        else if(!isFirstLetterVowel && isFirstLetterCapital)
        {
            int counter = 0; // this counter iterates over each character in string until next space
            bool doVowelsExist = false;
            // must check if vowels exist in word for cases where words don't have vowels
            while(isAlphabet(input.at(input_position + counter)))
            {
                if(isVowel(input.at(input_position + counter)))
                {
                    doVowelsExist = true;
                    break;
                }
                ++counter;
            }

            output.insert_back(tolower(input.at(input_position))); // lowercases the original capital letter
            ++input_position;

            counter = 1; // counter is reset to now keep track of how many characters exist before first vowel of word

            if(doVowelsExist)
            {
                while(isAlphabet(input.at(input_position)) && !isVowel(input.at(input_position)))
                {
                    output.insert_back(input.at(input_position));
                    ++input_position;
                    ++counter;
                }

                if(isAlphabet(input.at(input_position)))
                {
                    // capitalizes the first letter to be moved in front of word to preserve capitalization order
                    output.insert(output.length() - counter, toupper(input.at(input_position)));
                    ++input_position;
                }

                while(isAlphabet(input.at(input_position)))
                {
                    output.insert(output.length() - counter, input.at(input_position));
                    ++input_position;
                }

                output.insert_back('a');
                output.insert_back('y');
            }
            else
            {
                if(isAlphabet(input.at(input_position)))
                {
                    output.insert(output.length() - counter, toupper(input.at(input_position)));
                    ++input_position;
                    ++counter;
                }

                while(isAlphabet(input.at(input_position)))
                {
                    output.insert(output.length() - counter, input.at(input_position));
                    ++input_position;
                    ++counter;
                }

                output.insert_back('a');
                output.insert_back('y');
            }

            while(isPunctuation(input.at(input_position)))
            {
                output.insert_back(input.at(input_position));
                ++input_position;
            }
        }
        else
        {
            bool doVowelsExist = false;
            int counter = 0;

            while(isAlphabet(input.at(input_position + counter)))
            {
                if(isVowel(input.at(input_position + counter)))
                {
                    doVowelsExist = true;
                    break;
                }
                ++counter;
            }

            counter = 0;

            if(doVowelsExist)
            {
                while(isAlphabet(input.at(input_position)) && !isVowel(input.at(input_position)))
                {
                    output.insert_back(input.at(input_position));
                    ++input_position;
                    ++counter;
                }

                while(isAlphabet(input.at(input_position)))
                {
                    output.insert(output.length() - counter, input.at(input_position));
                    ++input_position;
                }

                output.insert_back('a');
                output.insert_back('y');
            }
            else
            {
                while(isAlphabet(input.at(input_position)))
                {
                    output.insert(output.length() - counter, input.at(input_position));
                    ++input_position;
                    ++counter;
                }

                output.insert_back('a');
                output.insert_back('y');
            }

            while(isPunctuation(input.at(input_position)))
            {
                output.insert_back(input.at(input_position));
                ++input_position;
            }
        }

        // deals with multiple spaces issue
        while(input.at(input_position) == ' ' && input.at(input_position + 1) == ' ')
        {
            ++input_position;
        }

        // resets isFirstLetterVowel boolean
        if(input.at(input_position) == ' ' && isVowel(input.at(input_position + 1)))
            isFirstLetterVowel = true;
        else
            isFirstLetterVowel = false;

        // resets isFirstLetterCapital boolean
        if(input.at(input_position) == ' ' && isupper(input.at(input_position + 1)))
            isFirstLetterCapital = true;
        else
            isFirstLetterCapital = false;

        // moves input position past space values
        if(input.at(input_position) == ' ')
        {
            output.insert_back(input.at(input_position));
            ++input_position;
        }
    }

    output.insert_back('\0');

    return true;
}