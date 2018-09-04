#include <iostream>
#include <string>
#include <typeinfo>
#include <algorithm>  

using namespace std;

void isNegative(unsigned int a)
{
    if (a < 0)
    {
        cout << "It's negative" << endl;
    }
    else
    {
        cout << "It's non-negative" << endl;
    }
}

int main()
{
    int a[] {1,2};
    int * ptr = a;
    cout << a << endl;
    cout << sizeof(ptr) << endl;
    return 0;
}

/*

void sortandPrintarray(string *names, int length)
{
    for (int startIndex = 0; startIndex < length - 1; ++startIndex)
	{
		// smallestIndex is the index of the smallest element we’ve encountered this iteration
		// Start by assuming the smallest element is the first element of this iteration
		int smallestIndex = startIndex;
 
		// Then look for a smaller element in the rest of the array
		for (int currentIndex = startIndex + 1; currentIndex < length; ++currentIndex)
		{
			// If we've found an element that is smaller than our previously found smallest
			if (names[currentIndex] < names[smallestIndex])
				// then keep track of it
				smallestIndex = currentIndex;
		}
 
		// smallestIndex is now the smallest element in the remaining array
        // swap our start element with our smallest element (this sorts it into the correct place)
		swap(names[startIndex], names[smallestIndex]);
	}

    cout << "Here is your sorted list: " << endl;
    for (int index = 0; index < length; index++)
        cout << "Name #" << index + 1 << ": " << names[index] << endl;

}

int main()
{
    cout << "How many names would you like to enter? ";
    int length;
    cin >> length;
    string *names = new string[length];
    for (int index = 0; index < length; index++)
        {
            cout << "Enter name #" << index + 1 << ": ";
            cin >> names[index];
        }

    sortandPrintarray(names, length);

    delete[] names;
    return 0;
}

*/