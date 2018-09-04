#include <iostream>

using namespace std;

void printArray(const int *array, const int size)
{
    // if user passed in a null pointer for array, bail out early!
    if (!array)
        return;

    for (int index = 0; index < size; index++)
        cout << array[index] << " ";
    cout << endl;
}

void addElementAtIndex(int **array, int *size, int element, int index)
{
    if (index < 0)
    {
        cout << "Error! Please enter a valid array index to add element" << endl;
        return;
    }

    int new_size;
    bool isIndexBiggerthanSize = false;

    if (index >= *size)
    {
        new_size = index + 1;
        isIndexBiggerthanSize = true;
    }
    else
        new_size = *size + 1;

    int *new_array = new int[new_size];

    if (isIndexBiggerthanSize)
    {
        for (int i = 0; i < new_size - 1; i++)
        {
            if (i < *size)
                new_array[i] = (*array)[i];
            else
                new_array[i] = 0;
        }

        new_array[new_size - 1] = element;
    }
    else
    {
        for (int i = 0; i < index; i++)
            new_array[i] = (*array)[i];

        new_array[index] = element;

        for (int i = index + 1; i < new_size; i++)
            new_array[i] = (*array)[i - 1];
    }

    *size = new_size;
    *array = new_array;
} 

void removeElementAtIndex(int **array, int *size, int index)
{
    if (index >= *size)
    {
        cout << "Error! Cannot remove indexed element due to out of range index" << endl;
        return;   
    }

    if (index < 0)  
    {
        cout << "Error! Please enter a valid array index to remove element" << endl;
        return;
    }

    int new_size = *size - 1;
    int *new_array = new int[new_size];

    for (int i = 0; i < index; i++)
        new_array[i] = (*array)[i];
    
    for (int i = index; i < new_size; i++)
        new_array[i] = (*array)[i + 1];
    
    *(size) = new_size;

    *array = new_array;
}

void addElementToFront(int **array, int *size, int element)
{
    if (*size < 0)
    {
        cout << "Error! Cannot add element to invalid sized array" << endl;
        return;   
    }

    addElementAtIndex(array, size, element, 0);
    /*int new_size = size + 1;
    int new_array[new_size];
    new_array[0] = element;

    for (int index = 1; index <= size; index++)
        new_array[index] = array[index - 1];
    */
}

void addElementToBack(int **array, int *size, int element)
{
    if (*size < 0)
    {
        cout << "Error! Cannot add element to invalid sized array" << endl;
        return;   
    }

    addElementAtIndex(array, size, element, *size);

    /*int new_size = size + 1;
    int new_array[new_size];

    for (int index = 0; index < size; index++)
        new_array[index] = array[index];

    new_array[new_size - 1] = element;
    */
}

void removeElementFromFront(int **array, int *size)
{
    if (*size <= 0)
    {
        cout << "Error! Cannot remove element from invalid sized array" << endl;
        return;   
    }

    removeElementAtIndex(array, size, 0);

    /*
    int new_size = size - 1;
    int new_array[size - 1];

    for (int index = 1; index < size; index++)
        new_array[index - 1] = array[index];
    */
}

void removeElementFromBack(int **array, int *size)
{
    if (*size <= 0)
    {
        cout << "Error! Cannot remove element from invalid sized array" << endl;
        return;   
    }

    removeElementAtIndex(array, size, *size - 1);
    
    /*
    int new_size = size - 1;
    int new_array[size - 1];

    for (int index = 0; index < new_size; index++)
        new_array[index] = array[index];
    */
}

int main()
{
 /*   cout << "Enter a positive integer: ";
    int input;
    cin >> input;
*/

    int* my_array = nullptr;
    int my_size = 0;

    printArray(my_array, my_size);

    removeElementAtIndex(&my_array, &my_size, 3);
    printArray(my_array, my_size);

    removeElementFromBack(&my_array, &my_size);
    printArray(my_array, my_size);

    addElementAtIndex(&my_array, &my_size, 1, 0);
    printArray(my_array, my_size);

    addElementToFront(&my_array, &my_size, 4);
    printArray(my_array, my_size);

    addElementToBack(&my_array, &my_size, 6);
    printArray(my_array, my_size);

    removeElementFromFront(&my_array, &my_size);
    printArray(my_array, my_size);

    delete[] my_array;
}
