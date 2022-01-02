#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SWAP(num1, num2) {int tmp; tmp = num1; num1 = num2; num2 = tmp;}

void insertionsort(int *arr, int size);

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

    insertionsort(arr, size);

    return 0;
}

void insertionsort(int *arr, int size)
{   
    for(int i = 0; i < size; i++)
    {   
        int key = arr[i]; //key為要插入的數值
        int j = i - 1; //要比較的資料數

        //將資料往後推移一個位值 直到欲插入的數值大於資料或資料結束
        while(key < arr[j] && j >= 0)
        {   
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key; //將欲插入的數值放入空出來的位置

        if(isFirst)
            isFirst = false;
        else
            printf(" \n");
        for(int k = 0; k < size; k++) {
            printf("%d", arr[k]);
            if(k != size - 1)
                printf(", ");
        }
    }
}