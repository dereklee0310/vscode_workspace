#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SWAP(num1, num2) {int tmp; tmp = num1; num1 = num2; num2 = tmp;}

void quicksort(int *arr, int left, int right);

int dataNum = 0;
bool isFirst = true;

int main() {
    char *buf = NULL;
    int *arr = NULL;

    buf = (char *)malloc(sizeof(char) * 4096);
    arr = (int *)malloc(sizeof(int) * 4096);

    fgets(buf, 4097, stdin);

    char *token = strtok(buf, ",");
    while(token != NULL) {
        arr[dataNum] = atoi(token);
        dataNum++;
        token = strtok(NULL, ",");
    }

    // while(scanf("%d", &arr[dataNum]) != EOF)
    //     dataNum++;

    quicksort(arr, 0, dataNum - 1);

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

        if(isFirst)
            isFirst = false;
        else
            printf(" \n");
        for(int k = 0; k < dataNum; k++) {
            printf("%d", arr[k]);
            if(k != dataNum - 1)
                printf(", ");
        }

        // printf("%d__%d\n", left, right);
        // puts("-----------------");

        quicksort(arr,left, j - 1);
        quicksort(arr, j+1, right);
    }
    
}