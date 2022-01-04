#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SWAP(num1, num2) {int tmp; tmp = num1; num1 = num2; num2 = tmp;}

// transform the input into an array of integers
void getNumbers(char *buf, int *arr);

// implementation of selection sort
void selectionsort(int *arr);

// print out the current array of integers
void printStep(int *arr);

int dataNum = 0;
bool isFirst = true;

int main() {
    char buf[4096];
    int arr[4096];

    fgets(buf, sizeof(buf), stdin);

    getNumbers(buf, arr);

    selectionsort(arr);

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

void selectionsort(int *arr)
{   
    int minIdx;

    for(int i = 0; i < dataNum - 1; i++) {   
        minIdx = i;
        for(int j = i; j < dataNum; j++)
            if(arr[j] < arr[minIdx])
                minIdx = j;
        if(arr[minIdx] != arr[i])
            SWAP(arr[minIdx], arr[i]);

        printStep(arr);
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