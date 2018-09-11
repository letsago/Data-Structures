#include <iostream>
#include <cassert>
#include "headers/Vector.h"

int main() 
{
    MyArray <int> A;        // default constructor: size = 0, data -> nullptr
    assert(A.Insert(-1, 10) == false); // should print an error and return false for failed insertion
    A.Insert_front(1);      
    A.Insert_front(2);
    assert(A.Front() == 2);
    assert(A.Back() == 1);
    A.Insert(5, 8);
    assert(A.At(2) == 0);
    assert(A.At(5) == 8);
    assert(A.actual_size == 6);
    assert(A.Remove(6) == false);
    assert(A.memory_size == 10);
    A.Remove(4);
    A.Remove_back();
    assert(A.Back() == 0);
    assert(A.At(1) == 1);
    A.Clear();
    assert(A.actual_size == 0);
    assert(A.memory_size == 0);
    assert(A.Empty() == true);

    MyArray <int> B(2, 7);      // size = 2, data -> [7,7]
    B.Print();                  // prints 7 7 as array
    B.Insert_back(9);           // inserts 9 at back of array
    B.Print();                  // prints 7 7 9 as array
    cout << B.Front() << endl;  // prints first element of array which is 7
    cout << B.Back() << endl;   // prints last element of array which is 9
    cout << B.At(1) << endl;    // prints index 0 element of array which is 7
    B.At(1) = 12;
    cout << B.At(1) << endl;
    cout << B.Data() << endl;   // prints memory address of array
    B.Clear();                  // array reset
    B.Print();                  // can't print null pointer
    if (B.Empty())              // prints "I'm empty" because array B is now of size 0
    {
        cout << "I'm empty!" << endl;
    }
    B.Remove_back();            // prints error and returns false for failed remove
    B.Insert_front(8);          // inserts 8 at front of array
    B.Print();                  // prints 8 as array

    return 0;
}
