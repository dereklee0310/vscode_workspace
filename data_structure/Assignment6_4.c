#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SWAP(num1, num2) {int tmp; tmp = num1; num1 = num2; num2 = tmp;}


void mergesort(int *arr, int size);

void mergeSinglePast(int *arr, int *sortedArr, int size, int len);

void merge(int *arr, int *sortedArr, int left, int middle, int right);

bool isFirst = true;

int size = 1;

int main() {
    char buf[4096];
    int arr[4096];

    fgets(buf, sizeof(buf), stdin);

    char *token = strtok(buf, ",");
    while(token != NULL) {
        arr[size] = atoi(token);
        size++;
        token = strtok(NULL, ",");
    }

    mergesort(arr, size - 1);

    int minGap = abs(arr[2] - arr[1]);
    for(int i = 3; i < size; i++) {
        int tmp = abs(arr[i] - arr[i - 1]);
        if(tmp < minGap)
            minGap = tmp;
    }
    printf("Minimum gap: %d", minGap);

    return 0;
}

void mergesort(int *arr, int size)
{
    int len = 1;
    int sortedArr[4096];

    while(len < size) {
        mergeSinglePast(arr, sortedArr, size, len);
        len *= 2;
        mergeSinglePast(sortedArr, arr, size, len);
        len *= 2;
    }
    putchar('\n');
    for(int k = 1; k <= size; k++) {
        printf("%d", arr[k]);
        if(k != size)
            printf(", ");
    }
    putchar('\n');
}

void mergeSinglePast(int *arr, int *sortedArr, int size, int len)
{
    int i;

    for(i = 1; i <= size - 2 * len + 1; i += 2 * len)
        merge(arr, sortedArr, i, i + len - 1, i + 2 * len - 1);

    if(i + len - 1 < size)
        merge(arr, sortedArr, i, i + len - 1, size);
    else
        for(int j = i; j <= size; j++)
            sortedArr[j] = arr[j];

    if(len == 1)
        return;
    
    if(isFirst)
        isFirst = false;
    else
        printf("\n");
    for(int k = 1; k <= size; k++) {
        printf("%d", arr[k]);
        if(k != size)
            printf(", ");
    }
}

void merge(int *arr, int *sortedArr, int left, int middle, int right)
{   
    int i = middle + 1;
    int j = left;


    while(left <= middle && i <= right)
        if(arr[left] <= arr[i])
            sortedArr[j++] = arr[left++];
        else
            sortedArr[j++] = arr[i++];
    
    if(left > middle)
        for(int k = i; k <= size; k++)
            sortedArr[j + k - i] = arr[k];
    else
        for(int k = left; k <= middle; k++)
            sortedArr[j + k - left] = arr[k];

}