#include <stdio.h>
#include <stdlib.h>

int main() {
    int height;
    int currentLen = 0;
    int numOfStar = 0;
    int totalCnt = 0;

    scanf("%d", &height);

    for(int i = 1; i <= height; i++)
        totalCnt += 2 * i - 1;

    int cnt = 0;
    for(int i = 1; i <= height; i++) {
        // i is the current level
        for(int j = 0; j < height - i; j++)
            printf("  "); // 2 space
        cnt += height - i;
        for(int j = 0; j < 2 * i - 1; j++)
            printf(" x");
        cnt += 2 * i - 1;
        // print out the pyramids after the first one of each line
        currentLen = 2 * (height - i);
        for(int j = 1; j < i; j++) {
            for(int k = 0; k < currentLen; k++)
                printf("  "); // 2 space
            cnt += currentLen;
            numOfStar = 2 * (i - j) - 1;
            for(int k = 0; k < numOfStar; k++)
                printf(" x");
            cnt += numOfStar;
        }
        for(int i = 0; i < totalCnt - cnt; i++)
            printf("  ");
        cnt = 0;
        if(i != height)
            printf("\n");
    }
    printf("\n");

    return 0;
}