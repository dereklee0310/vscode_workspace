#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAXNUM  500000

struct rv {
    char name[11];
    int nearestPoint;
    int distance;
};

int main() {
    struct rv river[MAXNUM];
    int riverNum, pointNum;
    int *relationArr;
    int relationNum = 0;

    scanf("%d %d", &riverNum, &pointNum);
    
    for(int i = 0; i < riverNum; i++) {
        scanf("%s", river[i].name);
        scanf("%d", &river[i].nearestPoint);
        scanf("%d", &river[i].distance);
    }

    scanf("%d", &relationNum);

    relationArr = (int *)malloc(sizeof(int) * relationNum); // !free
    for(int i = 0; i < relationNum; i++) {
        if(i == 0) {
            relationNum[i]
        }
    }

    return 0;
}