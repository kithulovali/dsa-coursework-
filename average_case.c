#include <stdio.h>

int main()
{
    int arr[] = {3, 5, 7, 9, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    int totalComparisons = 0;

    // Calculate comparisons for each element
    for (int i = 0; i < n; i++)
    {
        // In linear search, if the element is at position i, it takes (i+1) comparisons
        totalComparisons += (i + 1);
    }

    // Average comparisons
    float average = (float)totalComparisons / n;

    printf("Array elements: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\nAverage number of comparisons in linear search: %.2f\n", average);

    return 0;
}
