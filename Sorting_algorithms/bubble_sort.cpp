// Bubble sort

#include <iostream>
using namespace std;

int main()
{
    const int length(9);
    int array[length] = { 6, 3, 2, 9, 7, 1, 5, 4, 8 };
    bool swapped;
    int max_index = length;
    int iteration = 0;
    do
    {
        swapped = false;
        for (int index = 0; index < max_index - 1; index++)
        {
            if (array[index] > array[index + 1])
            {
                swap(array[index], array[index + 1]);
                swapped = true;
            }
        }
        --max_index;
        ++iteration;
    } while (swapped);

    cout << "Early termination on iteration " << iteration << endl;
    for (int index = 0; index < length; index++)
        cout << array[index] << " ";
    
    cout << "\n";

    return 0;
}
