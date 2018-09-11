// A basic arithmetic calculator that only takes in +, -, *, /, or = as an operator, float numbers as input,
// and continues to calculate until user terminates with = operator

#include <iostream>
using namespace std;

float getFloat()
{
    // loop until user enters a valid input
    while (true) 
    {
        std::cout << "Enter a number: ";
        double x;
        std::cin >> x;

        // check for failed extraction
        if (std::cin.fail()) // has a previous extraction failed?
        {
            std::cin.clear(); // put us back in 'normal' operation mode
            std::cin.ignore(32767,'\n'); // ignores the invalid cleared input
            std::cout << "Oops, that input is invalid.  Please try again.\n";
        }
        else
        {
            std::cin.ignore(32767,'\n'); // ignores all following bad input if first part of input is valid
            return x;
        }
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

float calculate(float x, float y, char op)
{
    switch(op)
    {
        case '+':
            return x + y;

        case '-':
            return x - y;

        case '*':
            return x * y;

        case '/':
            return x / y;
    }
}

int main() {
    char op;
    float num1, num2, result;
    
    num1 = getFloat();

    do 
    {
        op = getOperator();

        // main.cpp returns and outputs last result if user inputs = as op
        if (op == '=')
            {
            cout << num1 << endl;
            return 0;
            }
            
        num2 = getFloat();

        result = calculate(num1, num2, op);
        cout << result << endl; // result continues to update per operation
        
        num1 = result; // results becomes new num1 for later calculations
    }
    while (op != '='); // loops until user inputs = as op

    return 0;
}
