#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SWAP(num1, num2) {int tmp; tmp = num1; num1 = num2; num2 = tmp;}

void selectionsort(int *arr, int size);

bool isFirst = true;

int main() {
    int size = 0;
    char buf[4096];
    int arr[4096];

    fgets(buf, sizeof(buf), stdin);

    char *token = strtok(buf, ",");
    while(token != NULL) {
        arr[size] = atoi(token);
        size++;
        token = strtok(NULL, ",");
    }

    selectionsort(arr, size);

    return 0;
}

void selectionsort(int *arr, int size)
{   
    int minIdx;

    for(int i = 0; i < size - 1; i++)
    {   
        minIdx = i;
        for(int j = i; j < size; j++)
        {   
            //若找到新的最小值 記錄其值和位置
            if(arr[j] < arr[minIdx])
                minIdx = j;
        }
        //如果最小值改變 將第一個值和新的最小值位置互換
        if(arr[minIdx] != arr[i])
            SWAP(arr[minIdx], arr[i]);

        if(isFirst)
            isFirst = false;
        else
            printf("\n");
        for(int k = 0; k < size; k++) {
            printf("%d", arr[k]);
            if(k != size - 1)
                printf(", ");
        }
    }
}