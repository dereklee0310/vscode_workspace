#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

#define MAXLEN  1000000001

struct rv {
    char name[11];
    int nearestPoint;
    unsigned long long distance;
    int rank;
    int index;
};

int **createMatrix(int **adjMatrix, int pointNum);

void addEdge(int **adjMatrix, int vertice1, int vertice2, int distance);

unsigned long long *Dijkstra(int **adjMatrix, int pointNum);

void getDistance(struct rv *river, int riverNum, unsigned long long *distanceArr);

void getRank(struct rv *river, int riverNum);

unsigned long long getMin(unsigned long long *distanceArr, int pointNum, bool *isfound);

int cmp(const void *riv1, const void *riv2);

int rCmp(const void *riv1, const void *riv2);

int main() {
    struct rv *river;
    int riverNum, pointNum;
    int vertice1, vertice2, distance;
    int **adjMatrix;
    unsigned long long relationNum;
    unsigned long long *distanceArr;

    scanf("%d %d", &riverNum, &pointNum);
    pointNum++;
    
    river = (struct rv *)malloc(sizeof(struct rv) * riverNum);
    for(int i = 0; i < riverNum; i++) {
        scanf("%s", river[i].name);
        scanf("%d", &river[i].nearestPoint);
        scanf("%llu", &river[i].distance);
        river[i].index = i;
    }

    adjMatrix = createMatrix(adjMatrix, pointNum);

    scanf("%llu", &relationNum);
    for(unsigned long long i = 0; i < relationNum; i++) {
        scanf("%d", &vertice1);
        scanf("%d", &vertice2);
        scanf("%d", &distance);
        addEdge(adjMatrix, vertice1, vertice2, distance);
    }

    distanceArr = Dijkstra(adjMatrix, pointNum);

    // // test
    // puts("test");
    // for(int i = 0; i < pointNum; i++)
    //     printf("test_%d\n", distanceArr[i]);
    // for(int i = 0; i < riverNum; i++)
    //     printf("%s %d\n", river[i].name, river[i].distance);

    getDistance(river, riverNum, distanceArr);
    // test
    for(int i = 0; i < riverNum; i++)
        printf("%s %d\n", river[i].name, river[i].distance);

    getRank(river, riverNum);
    for(int i = 0; i < riverNum; i++)
        printf("%s %d\n", river[i].name, river[i].rank);

    return 0;
}

int **createMatrix(int **adjMatrix, int pointNum)
{
    adjMatrix = (int **)malloc(sizeof(int *) * pointNum);
    for(int i = 0; i < pointNum; i++)
        adjMatrix[i] = (int *)malloc(sizeof(int) * pointNum);

    for(int i = 0; i < pointNum; i++)
        for(int j = 0; j < pointNum; j++) {
            if(i == j)
                adjMatrix[i][j] = 0;
            else
                adjMatrix[i][j] = MAXLEN;
        }
    return adjMatrix;
}

void addEdge(int **adjMatrix, int vertice1, int vertice2, int distance)
{
    adjMatrix[vertice1][vertice2] = distance;
}

unsigned long long *Dijkstra(int **adjMatrix, int pointNum)
{   
    unsigned long long *distanceArr;
    bool *isfound;
    unsigned long long curPoint;

    distanceArr = (unsigned long long *)malloc(sizeof(unsigned long long) * pointNum);
    isfound = (bool *)malloc(sizeof(bool) * pointNum);
    for(int i = 0; i < pointNum; i++) {
        distanceArr[i] = adjMatrix[0][i];
        isfound[i] = false;
    }

    // for(int i = 0; i < pointNum; i++)
    //         printf("dijktest_%d\n", distanceArr[i]);
    //     puts("-first-");
    
    isfound[0] = true;
    distanceArr[0] = 0;
    for(int i = 0; i < pointNum - 2; i++) {
        curPoint = getMin(distanceArr, pointNum, isfound);
        isfound[curPoint] = true;
        for(int j = 0; j < pointNum; j++)
            if(!isfound[j])
                if(distanceArr[curPoint] + (unsigned long long)adjMatrix[curPoint][j] < distanceArr[j])
                    distanceArr[j] = distanceArr[curPoint] + (unsigned long long)adjMatrix[curPoint][j];
        
        // // test
        // for(int i = 0; i < pointNum; i++)
        //     printf("dijktest_%d\n", distanceArr[i]);
        // puts("--------------------");
    }

    return distanceArr;
}

void getDistance(struct rv *river, int riverNum, unsigned long long *distanceArr)
{
    for(int i = 0; i < riverNum; i++)
        river[i].distance += distanceArr[river[i].nearestPoint];
}

void getRank(struct rv *river, int riverNum)
{   
    int rank = 1;

    qsort(river, riverNum, sizeof(struct rv), cmp); // reverse
    for(int i = 0; i < riverNum; i++) {
        if(i == 0) {
            river[i].rank = rank;
        } else {
            if(river[i - 1].distance == river[i].distance)
                river[i].rank = rank;
            else
                river[i].rank = ++rank;
        }
    }

    // for(int i = 0; i < riverNum; i++)
    //     printf("%s %d\n", river[i].name, river[i].distance);

    qsort(river, riverNum, sizeof(struct rv), rCmp); // restore to origin array
}

unsigned long long getMin(unsigned long long *distanceArr, int pointNum, bool *isfound)
{
    int minPos = 0;
    unsigned long long min = ULONG_MAX;

    for(int i = 0; i < pointNum; i++) {
        if(distanceArr[i] < min && !isfound[i]) {
            min = distanceArr[i];
            minPos = i;
        }
    }

    return minPos;
}

int cmp(const void *riv1, const void *riv2)
{
    unsigned long long firstDis = ((struct rv *)riv1)->distance;
    unsigned long long secondDis = ((struct rv *)riv2)->distance;
    
    return (firstDis < secondDis) - (firstDis > secondDis);
}

int rCmp(const void *riv1, const void *riv2)
{
    int firstDis = ((struct rv *)riv1)->index;
    int secondDis = ((struct rv *)riv2)->index;
    
    return (firstDis > secondDis) - (firstDis < secondDis);
}