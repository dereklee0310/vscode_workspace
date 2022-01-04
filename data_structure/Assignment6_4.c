#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SWAP(num1, num2) {int tmp; tmp = num1; num1 = num2; num2 = tmp;}

// transform the input into an array of integers
void getNumbers(char *buf, int *arr);

// the function that invoke every past of merge sort
void mergesort(int *arr, int dataNum);

// do a single past of merge sort
void mergeSinglePast(int *arr, int *sortedArr, int dataNum, int len);

// merge two subarrays into one sorted array
void merge(int *arr, int *sortedArr, int left, int middle, int right);

// print out the current array of integers
void printStep(int *arr);

// return the minimum gap between two numbers in the given array
int getMinGap(int *arr);

int dataNum = 1;
bool isFirst = true;

int main() {
    char buf[4096];
    int arr[4096];

    fgets(buf, sizeof(buf), stdin);

    getNumbers(buf, arr);

    mergesort(arr, dataNum - 1);

    int minGap = getMinGap(arr);
    printf("Minimum gap: %d", minGap);

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

void mergesort(int *arr, int dataNum)
{
    int len = 1;
    int sortedArr[4096];

    while(len < dataNum) {
        mergeSinglePast(arr, sortedArr, dataNum, len);
        len *= 2;
        mergeSinglePast(sortedArr, arr, dataNum, len);
        len *= 2;
    }
    putchar('\n'); // add a newline after the previous steps
    for(int k = 1; k < dataNum; k++) {
        printf("%d, ", arr[k]);
    }
    printf("%d\n", arr[dataNum]); // print out the final line
}

void mergeSinglePast(int *arr, int *sortedArr, int dataNum, int len)
{
    int i;

    for(i = 1; i <= dataNum - 2 * len + 1; i += 2 * len)
        merge(arr, sortedArr, i, i + len - 1, i + 2 * len - 1);

    if(i + len - 1 < dataNum)
        merge(arr, sortedArr, i, i + len - 1, dataNum);
    else
        for(int j = i; j <= dataNum; j++)
            sortedArr[j] = arr[j];

    if(len == 1)
        return;
    
    printStep(arr);
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
        for(int k = i; k <= dataNum; k++)
            sortedArr[j + k - i] = arr[k];
    else
        for(int k = left; k <= middle; k++)
            sortedArr[j + k - left] = arr[k];

}

void printStep(int *arr)
{   
    // print newline after each line except for the last line
    if(isFirst)
        isFirst = false;
    else
        putchar('\n');
    for(int i = 1; i < dataNum; i++) {
        printf("%d", arr[i]);
        if(i != dataNum - 1)
            printf(", ");
    }
}

int getMinGap(int *arr)
{
    int minGap = abs(arr[2] - arr[1]);
    for(int i = 3; i < dataNum; i++) {
        int tmp = abs(arr[i] - arr[i - 1]);
        if(tmp < minGap)
            minGap = tmp;
    }
    return minGap;
}