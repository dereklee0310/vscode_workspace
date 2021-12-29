#include <stdio.h>
#include <stdlib.h>

#define SWAP(num1, num2) {int tmp; tmp = num1; num1 = num2; num2 = tmp;}

void quicksort(int *arr, int left, int right);

int i = 0;

int main() {
    int *arr = NULL;

    arr = (int *)malloc(sizeof(int) * 4096);

    while(scanf("%d", &arr[i]) != EOF)
        i++;

    quicksort(arr, 0, i - 1);

    for(int j = 0; j < i; j++)
        printf("%d\n", arr[j]);

    return 0;
}

void quicksort(int *arr, int left, int right)
{
    int pivot;
    int i = left;
    int j = right + 1;

    if(left < right) {
        pivot = arr[left];
        do {
            do {
                i++;
            } while (arr[i] < pivot);
            do {
                j--;
            } while (arr[j] > pivot);
            if(i < j)
                SWAP(arr[i], arr[j]);
        } while (i < j);
        SWAP(arr[left], arr[j]);
        quicksort(arr,left, j - 1);
        quicksort(arr, j+1, right);
    }

    for(int k = 0; k < i; k++)
        printf("%d\n", arr[k]);
    
}