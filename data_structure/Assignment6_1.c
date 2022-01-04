#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SWAP(num1, num2) {int tmp; tmp = num1; num1 = num2; num2 = tmp;}

// transform the input into an array of integers
void getNumbers(char *buf, int *arr);

// implementation of quick sort
void quicksort(int *arr, int left, int right);

// print out the current array of integers
void printStep(int *arr);

int dataNum = 0;
bool isFirst = true;

int main() {
    char buf[4096];
    int arr[4096];

    fgets(buf, 4097, stdin);
    getNumbers(buf, arr);

    quicksort(arr, 0, dataNum - 1);

    return 0;
}

void getNumbers(char *buf, int *arr)
{
    char *token = strtok(buf, ",");
    while(token != NULL) {
        arr[dataNum] = atoi(token);
        dataNum++;
        token = strtok(NULL, ",");
    }
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

        printStep(arr);

        quicksort(arr,left, j - 1);
        quicksort(arr, j+1, right);
    }
}

void printStep(int *arr)
{   
    // print newline after each line except for the last line
    if(isFirst)
        isFirst = false;
    else
        putchar('\n');
    for(int i = 0; i < dataNum; i++) {
        printf("%d", arr[i]);
        if(i != dataNum - 1)
            printf(", ");
    }
}