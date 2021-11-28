#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int *getAns(int *poly, int power);

void copyPoly(int *ansPoly, int *tmpPoly);

#define MAXSIZE 1025 // 2^10 + 1
int main() {
    bool isFirst = true;
    int *poly = malloc(sizeof(int) * MAXSIZE);
    int power;

    for(int i = 2; i >= 0; i--)
        scanf("%d", &poly[i]);
    for(int i = 3; i < MAXSIZE; i++)
        poly[i] = 0;
    scanf("%d", &power);

    int *ansPoly = getAns(poly, power);


    int max = -1;
    bool isMaxFound = false;
    for(int i = MAXSIZE - 1; i >= 0; i--) {
        // if(ansPoly[i]) {
        //     if(isFirst)
        //         isFirst = false;
        //     else
        //         putchar(' ');
        //     printf("%d", ansPoly[i]);
        // }
        if(ansPoly[i]) {
            if(!isMaxFound) {
                max = i;
                isMaxFound = true;
            }
        }
        if(i <= max) {
            if(isFirst)
                isFirst = false;
            else
                putchar(' ');
            printf("%d", ansPoly[i]);
        }
    }
    putchar('\n');

    free(poly);
    free(ansPoly);

    return 0;
}

int *getAns(int *poly, int power)
{   
    int tmpPoly[MAXSIZE];
    int *ansPoly = malloc(sizeof(int) * MAXSIZE);
    int tmp = 0;

    copyPoly(ansPoly, poly);
    if(power == 1)
        return ansPoly;

    for(int i = 1; i < power; i++) {
        for(int j = 0; j < MAXSIZE; j++)
            tmpPoly[j] = 0;
        for(int k = 0; k < MAXSIZE; k++) {
            tmp = 0;
            if(ansPoly[k]) {
                for(int l = 0; l < MAXSIZE; l++) {
                    if(poly[l])
                        tmpPoly[k + l] += ansPoly[k] * poly[l];
                }
            }
        }
        copyPoly(ansPoly, tmpPoly);
    }

    return ansPoly;
}

void copyPoly(int *ansPoly, int *tmpPoly)
{
    for(int i = 0; i < MAXSIZE; i++)
        ansPoly[i] = tmpPoly[i];
}