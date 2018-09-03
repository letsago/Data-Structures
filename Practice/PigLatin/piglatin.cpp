#include "headers/piglatin.h"

bool isAlphabet(const char entry)
{
    if ((entry >= 'a' && entry <= 'z') || (entry >= 'A' && entry <= 'Z') || entry == '\'' || entry == '-')
        return true;
    else
        return false;
}

bool isVowel(const char entry)
{
    const char validchars[] = "aeiouAEIOU-";
    for (int i = 0; i < sizeof(validchars) - 1; ++i)
    {
        if (entry == validchars[i])
            return true;
    }

    return false;
}

bool isPunctuation(const char entry)
{
    const char validchars[] = ".?!,";
    for (int i = 0; i < sizeof(validchars) - 1; ++i)
    {
        if (entry == validchars[i])
            return true;
    }

    return false;
}

bool doInvalidCharsExist(const MyVector<char>& input)
{
    for (int i = 0; i < input.Length(); ++i)
    {
        if (!((input.At(i) >= 'a' && input.At(i) <= 'z') || 
            (input.At(i) >= 'A' && input.At(i) <= 'Z') ||
            (input.At(i) == '-') || (input.At(i) == '\'') ||
            (input.At(i) == '.') || (input.At(i) == '?') ||
            (input.At(i) == '!') || (input.At(i) == ',') ||
            (input.At(i) == '\0') || input.At(i) == ' '))
                return true;
    }

    return false;
}

// bool appropriatelySpace(const MyVector<char>& input, MyVector<char>& output)
// {
//     output = input;

//     // adding space after last punctuation
//     for (int i = 0; i < (input.Length() - 1); ++i)
//     {
//         if ((input.At(i) == '.' || input.At(i) == '?' || input.At(i) == '!' || input.At(i) == ',') &&
//             ((input.At(i + 1) >= 'a' && input.At(i + 1) <= 'z') || 
//             (input.At(i + 1) >= 'A' && input.At(i + 1) <= 'Z')))
//             {
//                 output.Insert(i + 1, ' ');
//             }      
//     }
    
//     // removing multiple spaces
//     for (int i = 0; i < (input.Length() - 1); ++i)
//     {
//         if ((input.At(i) == ' ' && input.At(i + 1) == ' '))
//             output.Remove(i + 1);
//     }

//     // if input starts or ends with space, removes that space
//     if (input.Front() == ' ')
//         output.Remove_front();

//     // if input ends with space, removes that space
//     if ((input.Back() - 1) == ' ')
//         output.Remove(output.Back() - 1);
    
//     return true;
// }

bool pigLatinTranslate(const MyVector<char>& input, MyVector<char>& output)
{
    if (doInvalidCharsExist(input))
        return false;

    // handles null case
    if (input.Length() == 0)
        return false;
    
    int input_position = 0;
    bool isFirstLetterVowel = isVowel(input.At(0));
    bool isFirstLetterCapital = isupper(input.At(0));

    // loops until end of input string
    while (input.At(input_position) != '\0')
    {
        // three distinct cases: first letter of word is vowel, first letter of word is not vowel and not capital,
        // first letter of word is not vowel yet capital
        if (isFirstLetterVowel)
        {
            while (isAlphabet(input.At(input_position)))
            {
                output.Insert_back((input.At(input_position)));
                ++input_position;
            }
            
            output.Insert_back('y');
            output.Insert_back('a');
            output.Insert_back('y');

            // this loop adds all punctuation at end of word until the next space
            while (isPunctuation(input.At(input_position)))
            {
                output.Insert_back(input.At(input_position));
                ++input_position;
            }
        }
        else if (!isFirstLetterVowel && isFirstLetterCapital)  
        {
            int counter = 0;    // this counter iterates over each character in string until next space
            bool doVowelsExist = false;
            // must check if vowels exist in word for cases where words don't have vowels
            while (isAlphabet(input.At(input_position + counter)))
            {
                if (isVowel(input.At(input_position + counter)))
                {
                    doVowelsExist = true;
                    break;
                }
                ++counter;
            }

            output.Insert_back(tolower(input.At(input_position)));  // lowercases the original capital letter
            ++input_position;

            counter = 1;    // counter is reset to now keep track of how many characters exist before first vowel of word

            if (doVowelsExist)
            {
                while (isAlphabet(input.At(input_position)) && !isVowel(input.At(input_position)))
                {
                    output.Insert_back(input.At(input_position));
                    ++input_position;
                    ++counter;
                }

                if (isAlphabet(input.At(input_position)))
                {
                    // capitalizes the first letter to be moved in front of word to preserve capitalization order
                    output.Insert(output.Length() - counter, toupper(input.At(input_position)));
                    ++input_position;
                }

                while (isAlphabet(input.At(input_position)))
                {
                    output.Insert(output.Length() - counter, input.At(input_position));
                    ++input_position;
                }

                output.Insert_back('a');
                output.Insert_back('y');
            }
            else
            {
                if (isAlphabet(input.At(input_position)))
                {
                    output.Insert(output.Length() - counter, toupper(input.At(input_position)));
                    ++input_position;
                    ++counter;
                }

                while (isAlphabet(input.At(input_position)))
                {
                    output.Insert(output.Length() - counter, input.At(input_position));
                    ++input_position;
                    ++counter;
                }

                output.Insert_back('a');
                output.Insert_back('y');
            }

            while (isPunctuation(input.At(input_position)))
            {
                output.Insert_back(input.At(input_position));
                ++input_position;
            }
        }
        else 
        {
            bool doVowelsExist = false;
            int counter = 0;

            while (isAlphabet(input.At(input_position + counter)))
            {
                if (isVowel(input.At(input_position + counter)))
                    doVowelsExist = true;

                ++counter;
            }

            counter = 0;

            if (doVowelsExist)
            {
                while (isAlphabet(input.At(input_position)) && !isVowel(input.At(input_position)))
                {
                    output.Insert_back(input.At(input_position));
                    ++input_position;
                    ++counter;
                }

                while (isAlphabet(input.At(input_position)))
                {
                    output.Insert(output.Length() - counter, input.At(input_position));
                    ++input_position;
                }

                output.Insert_back('a');
                output.Insert_back('y');
            }
            else
            {
                while (isAlphabet(input.At(input_position)))
                {
                    output.Insert(output.Length() - counter, input.At(input_position));
                    ++input_position;
                    ++counter;
                }

                output.Insert_back('a');
                output.Insert_back('y');
            }

            while (isPunctuation(input.At(input_position)))
            {
                output.Insert_back(input.At(input_position));
                ++input_position;
            }
        }

        // deals with multiple spaces issue
        while (input.At(input_position) == ' ' && input.At(input_position + 1) == ' ')
        {
            ++input_position;
        }

        // resets isFirstLetterVowel boolean
        if (input.At(input_position) == ' ' && isVowel(input.At(input_position + 1)))
            isFirstLetterVowel = true;
        else
            isFirstLetterVowel = false;
        
        // resets isFirstLetterCapital boolean
        if (input.At(input_position) == ' ' && isupper(input.At(input_position + 1)))
            isFirstLetterCapital = true;
        else
            isFirstLetterCapital = false;
        
        // moves input position past space values
        if (input.At(input_position) == ' ')
        {
            output.Insert_back(input.At(input_position));
            ++input_position;
        }

    }
    
    output.Insert_back('\0');
    return true;
}

// int main()
// {
//     const char str[] = "Oh my snot!!! How come??";

//     const MyVector<char> A(str, sizeof(str));
//     MyVector<char> B;

//     pigLatinTranslate(A, B);
    
//     cout << B.Length() << endl;
//     cout << sizeof(str) << endl;
//     B.Print();
//     // for (int i = 0; i < A.Length(); ++i)
//     // {
//     //     cout << A.At(i) << endl;
//     // }
//     // for (int i = 0; i < B.Length(); ++i)
//     // {
//     //     cout << B.At(i) << endl;
//     // }
//     return 0;
// }