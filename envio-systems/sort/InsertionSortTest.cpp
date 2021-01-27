
/**
 * @file   InsertionSortTest.cpp
 *
 * @brief  Sort an array and print the sorted values.
 *
 * @author gustavo.garcia
 * @date   Jan 23, 2021
 */

/* INCLUDES ******************************************************************/
#include <iostream>

/* USINGS ********************************************************************/
using namespace std; 

/**
 * @brief Sorts an array using insertion sort.
 *
 * @param array The array to be sorted.
 * @param lenght The size of the byte array.
 */ 
void insertionSort(int* array, int lenght)  
{  
    for (int i = 1; i < lenght; i++) 
    {  
        int currentValue, j;

        currentValue = array[i];  
        j = i - 1;  

        while (j >= 0 && array[j] > currentValue) 
        {  
            array[j + 1] = array[j];  
            j = j - 1;  
        }  
        array[j + 1] = currentValue;  
    }
}  
  
/**
 * @brief Prints the contents of an integer array.
 *
 * @param array The array to be sorted.
 * @param lenght The size of the byte array.
 */ 
void printArray(int* array, int lenght)   
{  
    for (int i = 0; i < lenght; i++)  
        cout << array[i] << " ";  
    cout << endl; 
}  
  
/**
 * @brief Application entry point.
 *
 * @param argc The number of arguments.
 * @param argv The arguments collection.
 *
 * @return 0 if successful; otherwise, an error code.
 */
int main()  
{  
    int foo [30] = { 2, 2, 1, 0, 1, 0, 1, 1, 0, 2, 2, 1, 1, 1, 2, 0, 0, 1, 1, 0, \
                   1, 0, 1, 2, 0, 0, 0, 1, 1, 2 }; 
    int lenght = sizeof(foo) / sizeof(foo[0]);  
  
    insertionSort(foo, lenght);  
    printArray(foo, lenght);  
  
    return 0;  
}  
