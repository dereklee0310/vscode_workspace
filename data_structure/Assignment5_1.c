#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX  1000000001

// data of a single river
struct rv {
    char name[11];
    int nearestPoint;
    int distance;
    int rank;
    int index;
};

// create and initialize an adjacency matrix
int **createMatrix(int **adjMatrix, int vertexNum);

// shortest path algorithm
int *Dijkstra(int **adjMatrix, int vertexNum);

// get the unprocessed vertex in gragh, which will be used by Dijkstra algorithm
int getMin(int *distanceArr, int vertexNum, bool *isfound);

// rank the rivers by their lengths
void getRank(struct rv *river, int riverNum);

// compare funciton for qsort, compare two elements by their length;
int cmp(const void *riv1, const void *riv2);

// compare function for qsort, compare two elements by their original indices;
int rCmp(const void *riv1, const void *riv2);

int main() {
    struct rv *river;
    int riverNum, vertexNum, relationNum;
    int vertex1, vertex2, distance;

    scanf("%d %d", &riverNum, &vertexNum);
    vertexNum++; // number of vertex + 1 because of conflence 0
    
    river = (struct rv *)malloc(sizeof(struct rv) * riverNum);
    for(int i = 0; i < riverNum; i++) {
        scanf("%s", river[i].name);
        scanf("%d", &river[i].nearestPoint);
        scanf("%d", &river[i].distance);
        river[i].index = i;
    }

    // build an adjacency matrix for the graph
    int **adjMatrix = createMatrix(adjMatrix, vertexNum);
    scanf("%d", &relationNum);
    for(int i = 0; i < relationNum; i++) {
        scanf("%d", &vertex1);
        scanf("%d", &vertex2);
        scanf("%d", &distance);
        adjMatrix[vertex1][vertex2] = distance;
    }

    // find legths of rivers and rank them
    int *distanceArr = Dijkstra(adjMatrix, vertexNum);
    for(int i = 0; i < riverNum; i++)
        river[i].distance += distanceArr[river[i].nearestPoint];
    getRank(river, riverNum);
    for(int i = 0; i < riverNum; i++)
        printf("%s %d\n", river[i].name, river[i].rank);

    free(river);
    for(int i = 0; i < vertexNum; i++)
        free(adjMatrix[i]);
    free(adjMatrix);
    free(distanceArr);

    return 0;
}

int **createMatrix(int **adjMatrix, int vertexNum)
{
    adjMatrix = (int **)malloc(sizeof(int *) * vertexNum);
    for(int i = 0; i < vertexNum; i++)
        adjMatrix[i] = (int *)malloc(sizeof(int) * vertexNum);

    for(int i = 0; i < vertexNum; i++)
        for(int j = 0; j < vertexNum; j++)
            adjMatrix[i][j] = i == j ? 0 : MAX;

    return adjMatrix;
}

int *Dijkstra(int **adjMatrix, int vertexNum)
{   
    int *distanceArr;
    bool *isfound;
    int curPoint;

    distanceArr = (int *)malloc(sizeof(int) * vertexNum);
    isfound = (bool *)malloc(sizeof(bool) * vertexNum);
    for(int i = 0; i < vertexNum; i++) {
        distanceArr[i] = adjMatrix[0][i];
        isfound[i] = false;
    }
    
    isfound[0] = true;
    distanceArr[0] = 0;
    for(int i = 0; i < vertexNum - 2; i++) {
        curPoint = getMin(distanceArr, vertexNum, isfound);
        isfound[curPoint] = true;
        for(int j = 0; j < vertexNum; j++)
            if(!isfound[j])
                if(distanceArr[curPoint] + adjMatrix[curPoint][j] < distanceArr[j])
                    distanceArr[j] = distanceArr[curPoint] + adjMatrix[curPoint][j];
    }

    free(isfound);

    return distanceArr;
}

int getMin(int *distanceArr, int vertexNum, bool *isfound)
{
    int minPos = -1;
    int min = INT_MAX;

    for(int i = 0; i < vertexNum; i++) {
        if(distanceArr[i] < min && !isfound[i]) {
            min = distanceArr[i];
            minPos = i;
        }
    }

    return minPos;
}

void getRank(struct rv *river, int riverNum)
{   
    int rank = 1;

    qsort(river, riverNum, sizeof(struct rv), cmp); // sort the rivers by length
    river[0].rank = rank;
    for(int i = 1; i < riverNum; i++)
        river[i].rank = river[i - 1].distance == river[i].distance ? rank : ++rank;
    qsort(river, riverNum, sizeof(struct rv), rCmp); // restore to the original order
}

int cmp(const void *riv1, const void *riv2)
{
    int firstDis = ((struct rv *)riv1)->distance;
    int secondDis = ((struct rv *)riv2)->distance;
    
    return (firstDis < secondDis) - (firstDis > secondDis);
}

int rCmp(const void *riv1, const void *riv2)
{
    int firstDis = ((struct rv *)riv1)->index;
    int secondDis = ((struct rv *)riv2)->index;
    
    return (firstDis > secondDis) - (firstDis < secondDis);
}