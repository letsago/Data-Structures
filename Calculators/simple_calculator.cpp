#include <iostream>

float add(float x, float y)
{
  return x + y;
}

float multiply(float x, float y)
{
  return x * y;
}

float subtract(float x, float y)
{
  return x - y;
}

float divide(float x, float y)
{
  return x / y;
}

int main()
{
    char op;
    float num1, num2;

    std::cout << "Enter a basic arithmetic operator: ";
    std::cin >> op;

    std::cout << "Enter two numbers: ";
    std::cin >> num1 >> num2;

    switch(op)
    {
        case '+':
            std::cout << add(num1, num2) << std::endl;
            break;

        case '-':
            std::cout << subtract(num1, num2) << std::endl;
            break;

        case '*':
            std::cout << multiply(num1, num2) << std::endl;
            break;

        case '/':
            std::cout << divide(num1, num2) << std::endl;
            break;

        default:
            std::cout << "Error!/n";
            break;
    }

    return 0;
}