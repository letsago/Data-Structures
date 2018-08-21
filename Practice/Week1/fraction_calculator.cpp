// a fraction calculator

#include <iostream>
using namespace std;

struct Fraction
{
    int numerator;
    int denominator;
};

Fraction add(Fraction f1, Fraction f2)
{
    Fraction f3;
    f3.numerator = ((f1.numerator * f2.denominator) + (f2.numerator * f1.denominator));
    f3.denominator = (f1.denominator * f2.denominator);
    return f3; 
}

Fraction subtract(Fraction f1, Fraction f2)
{
    Fraction f3;
    f3.numerator = ((f1.numerator * f2.denominator) - (f2.numerator * f1.denominator));
    f3.denominator = (f1.denominator * f2.denominator);
    return f3; 
}

Fraction multiply(Fraction f1, Fraction f2)
{
    Fraction f3;
    f3.numerator = (f1.numerator * f2.numerator);
    f3.denominator = (f1.denominator * f2.denominator);
    return f3; 
}

Fraction divide(Fraction f1, Fraction f2)
{
    Fraction f3;
    f3.numerator = (f1.numerator * f2.denominator);
    f3.denominator = (f1.denominator * f2.numerator);
    return f3; 
}

Fraction calculate(Fraction frac1, Fraction frac2, char op)
{
    switch(op)
    {
        case '+':
            add(frac1, frac2);
            break;

        case '-':
            subtract(frac1, frac2);
            break;

        case '*':
            multiply(frac1, frac2);
            break;

        case '/':
            divide(frac1, frac2);
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
 
        std::cin.ignore(32767,'\n'); // ignores all following bad input if first part of input is valid
 
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
        if (std::cin.fail()) // has a previous extraction failed?
        {
            std::cin.clear(); // put us back in 'normal' operation mode
            std::cin.ignore(32767,'\n');    // ignores the invalid cleared input, 
                                            // 32767 is the largest number to safely be represented 
                                            // in a 2-byte integer on all platforms 
            std::cout << "Oops, that input is invalid.  Please try again.\n";
        }
        else
        {
            std::cin.ignore(32767,'\n'); // ignores following bad input if first part of input is valid
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

// pointer input that is deferenced and prints out fraction in numerator/denominator format
void printFraction(const Fraction* frac)
{
    Fraction f;
    f = *frac;
    cout << f.numerator << "/" << f.denominator << "\n";
}

int main()
{
    char op;
    Fraction f1, f2, result;
    f1 = getFraction();
    Fraction *ptr1 = &f1;
    Fraction *ptr_result = &result; //retrieve pointers to later printFraction
    
    do 
    {
        op = getOperator();

        // main.cpp returns and outputs last result if user inputs = as op
        if (op == '=')
            {
            printFraction(ptr1);
            return 0;
            }
            
        f2 = getFraction();

        result = calculate(f1, f2, op);
        printFraction(ptr_result); // result continues to update per operation
        
        f1 = result; // results becomes new fraction 1 for later calculations
    }
    while (op != '='); // loops until user inputs = as op

    return 0;
}