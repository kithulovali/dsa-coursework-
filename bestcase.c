#include <stdio.h>

int main()
{
    int arr[] = {7, 12, 5, 19, 3}; // Array
    int n = 5;                     // Size of array
    int key = 7;                   // BEST CASE: first element
    int comparisons = 0;

    // Linear Search
    for (int i = 0; i < n; i++)
    {
        comparisons++; // Count number of comparisons
        if (arr[i] == key)
        {
            printf("Element %d found at index %d\n", key, i);
            break; // Stop after finding element
        }
    }

    printf("Total comparisons (Best Case) = %d\n", comparisons);

    return 0;
}
