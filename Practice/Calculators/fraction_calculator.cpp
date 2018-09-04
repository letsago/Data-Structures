// A fraction calculator that allows user to create fractions 
// by entering numerators and denominators as integers,
// and then performing basic arithmetic operations on those fractions.
// Dividing by 0 will raise a floating point exception.

#include <iostream>
#include <cmath>
using namespace std;

struct Fraction
{
    int numerator;
    int denominator;
};

// All subsequent Fraction struct function parameters are passed using const 
// references in order to avoid making unnecessary expensive copies of variables
Fraction add(const Fraction &f1, const Fraction &f2)
{
    Fraction f3;
    f3.numerator = ((f1.numerator * f2.denominator) + (f2.numerator * f1.denominator));
    f3.denominator = (f1.denominator * f2.denominator);
    return f3; 
}

Fraction subtract(const Fraction &f1, const Fraction &f2)
{
    Fraction f3;
    f3.numerator = ((f1.numerator * f2.denominator) - (f2.numerator * f1.denominator));
    f3.denominator = (f1.denominator * f2.denominator);
    return f3; 
}

Fraction multiply(const Fraction &f1, const Fraction &f2)
{
    Fraction f3;
    f3.numerator = (f1.numerator * f2.numerator);
    f3.denominator = (f1.denominator * f2.denominator);
    return f3; 
}

Fraction divide(const Fraction &f1, const Fraction &f2)
{
    Fraction f3;
    f3.numerator = (f1.numerator * f2.denominator);
    f3.denominator = (f1.denominator * f2.numerator);
    return f3; 
}

Fraction calculate(const Fraction &f1, const Fraction &f2, char op)
{
    switch(op)
    {
        case '+':
            add(f1, f2);
            break;

        case '-':
            subtract(f1, f2);
            break;

        case '*':
            multiply(f1, f2);
            break;

        case '/':
            divide(f1, f2);
            break;
    }
}

char getOperator()
{
    // loop until user enters a valid input
    while (true) 
    {
        std::cout << "Enter one of the following: +, -, *, /, or =: ";
        char op;
        std::cin >> op;
 
        std::cin.ignore(32767,'\n');    // ignores the invalid cleared input, 
                                        // 32767 is used because it is the largest number to 
                                        // safely be represented in a 2-byte integer on all platforms 
 
        // check whether the user entered meaningful input
        if (op == '+' || op == '-' || op == '*' || op == '/' || op == '=')    
            return op; 
        else 
            std::cout << "Oops, that input is invalid.  Please try again.\n";
        } 
}

int getInt()
{
    // loop until user enters a valid input
    while (true) 
    {
        std::cout << "Enter an integer: ";
        int x;
        std::cin >> x;

        // check for failed extraction
        if (std::cin.fail())
        {
            std::cin.clear(); // put us back in 'normal' operation mode
            std::cin.ignore(32767,'\n');    // ignores the invalid cleared input up to 32767 characters, 
                                            // 32767 is used because it is the largest number to 
                                            // safely be represented in a 2-byte integer on all platforms 
            std::cout << "Oops, that input is invalid.  Please try again.\n";
        }
        else
        {
            std::cin.ignore(32767,'\n');    // ignores invalid input up to 32767 characters
                                            // see above for why 32767 is used
            return x;
        }
    }
}

// uses getInt() to extract numerator and denominators of Fraction struct 
Fraction getFraction()
{
    Fraction frac;
    frac.numerator = getInt();
    frac.denominator = getInt();
    return frac;
}

// uses Euclid's algorithm to calculate the greatest common denominator between numerator and denominator 
// and returns simplified fraction
Fraction simplifyFraction(const Fraction &frac)
{
    int numerator = abs(frac.numerator); 
    int denominator = abs(frac.denominator);
    int remainder = numerator % denominator;    // since numerator and denominator are non-negative, 
                                                // remainder will also be non-negative
                                                // which allows Euclid's algorithm to correctly operate
    int gcd = 1; // greatest common denominator
    Fraction simplified_frac;

    if (remainder == 0)
    {
        gcd = denominator;
        simplified_frac.numerator = frac.numerator / gcd;
        simplified_frac.denominator = frac.denominator / gcd;
        return simplified_frac;
    }

    if (remainder == 1)
        return frac;

    numerator = abs(frac.denominator);          // must be non-negative
    denominator = remainder;
    remainder = numerator % denominator;

    while (remainder >= 2)
    {
        numerator = denominator;
        denominator = remainder;
        remainder = numerator % denominator;
    }

    if (remainder == 0)
    {
        gcd = denominator;
        simplified_frac.numerator = frac.numerator / gcd;
        simplified_frac.denominator = frac.denominator / gcd;
        return simplified_frac;
    }

    if (remainder == 1)
        return frac;
}

// pointer input that is deferenced and prints out fraction in numerator/denominator format
void printFraction(const Fraction* frac)
{
    Fraction f;
    f = *frac;
    if (abs(f.denominator) == 1) 
    {
        if (f.denominator > 0)              // if denominator equals 1, will only print numerator
            cout << f.numerator << "\n"; 
        else                                // if denominator equals -1, will only print -(numerator)
            cout << -(f.numerator) << "\n";
    }
    else
    {
        if (f.denominator < 0)              // if denominator is negative and not equal to -1, 
                                            // will print fraction with negative numerator instead
            cout << -(f.numerator) << "/" << -(f.denominator) << "\n";
        else                                // if denominator is positive and not equal to 1,
                                            // will print fraction normally
            cout << f.numerator << "/" << f.denominator << "\n";
    }
}

int main()
{
    Fraction f1, f2, result;
    f1 = getFraction();
    f1 = simplifyFraction(f1);
    Fraction *ptr1 = &f1;
    Fraction *ptr_result = &result; //retrieve pointers to later printFraction
    char op;
    
    do 
    {
        op = getOperator();

        // main() returns and outputs last result if user inputs = as op
        if (op == '=')
            {
            printFraction(ptr1);
            return 0;
            }
            
        f2 = getFraction();

        result = calculate(f1, f2, op);
        result = simplifyFraction(result);
        printFraction(ptr_result); // result continues to update per operation
        
        f1 = result; // results becomes new fraction 1 for later calculations
    }
    while (op != '='); // loops until user inputs = as op

    return 0;
}