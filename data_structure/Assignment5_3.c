#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 1000000001

// create and initialize an adjacency matrix
int **createMatrix(int **adjMatrix, int vertexNum);

// shortest path algorithm
int *Dijkstra(int **adjMatrix, int vertexNum, int root);

// get the unprocessed vertex in gragh, which will be used by Dijkstra algorithm
int getMin(int *distanceArr, int vertexNum, bool *isfound);

// calculate the total distance from root to all vertices
int getTotalDistance(int *distanceArr, int nameNum);

int main() {
    int **adjMatrix;
    char names[2048][21];
    int nameNum, edgeNum;
    int vertex1, vertex2, distance;
    int totalDistance;
    int minDistance = -1;
    int minIdx = -1;
    int cnt = 1;

    scanf("%d %d", &nameNum, &edgeNum);
    while(nameNum != 0 && edgeNum != 0) {
        adjMatrix = createMatrix(adjMatrix, nameNum);
        for(int i = 0; i < nameNum; i++)
            scanf("%s", names[i]);
        for(int i = 0; i < edgeNum; i++) {
            scanf("%d %d %d", &vertex1, &vertex2, &distance);
            adjMatrix[vertex1][vertex2] = distance;
            adjMatrix[vertex2][vertex1] = distance;
        }

        int *distanceArr = (int *)malloc(sizeof(int) * nameNum);
        minDistance = -1;
        for(int i = 0; i < nameNum; i++) {
            distanceArr = Dijkstra(adjMatrix, nameNum, i);
            totalDistance = getTotalDistance(distanceArr, nameNum);
            if(minDistance == -1 || totalDistance < minDistance) {
                minIdx = i;
                minDistance = totalDistance;
            }
        }
        
        printf("Case #%d %s\n", cnt, names[minIdx]);
        cnt++;

        scanf("%d %d", &nameNum, &edgeNum);
    }
    // todo free memory

    return 0;
}

int **createMatrix(int **adjMatrix, int vertexNum)
{
    adjMatrix = (int **)malloc(sizeof(int *) * vertexNum);
    for(int i = 0; i < vertexNum; i++)
        adjMatrix[i] = (int *)malloc(sizeof(int) * vertexNum);

    for(int i = 0; i < vertexNum; i++)
        for(int j = 0; j < vertexNum; j++) {
            if(i == j)  
                adjMatrix[i][j] = 0;
            else
                adjMatrix[i][j] = MAX;
        }
    return adjMatrix;
}

int *Dijkstra(int **adjMatrix, int vertexNum, int root)
{   
    int *distanceArr;
    bool *isfound;
    int curPoint;

    distanceArr = (int *)malloc(sizeof(int) * vertexNum);
    isfound = (bool *)malloc(sizeof(bool) * vertexNum);
    for(int i = 0; i < vertexNum; i++) {
        distanceArr[i] = adjMatrix[root][i];
        isfound[i] = false;
    }
    
    isfound[root] = true;
    distanceArr[root] = 0;
    for(int i = 0; i < vertexNum - 2; i++) {
        curPoint = getMin(distanceArr, vertexNum, isfound);
        for(int j = 0; j < vertexNum; j++)
            if(!isfound[j])
                if(distanceArr[curPoint] + adjMatrix[curPoint][j] < distanceArr[j])
                    distanceArr[j] = distanceArr[curPoint] + adjMatrix[curPoint][j];
    }

    return distanceArr;
}

int getMin(int *distanceArr, int vertexNum, bool *isfound)
{
    int minPos = -1;
    int min = MAX;

    for(int i = 0; i < vertexNum; i++) {
        if(distanceArr[i] < min && !isfound[i]) {
            min = distanceArr[i];
            minPos = i;
        }
    }

    return minPos;
}

int getTotalDistance(int *distanceArr, int nameNum)
{   
    int totalDistance = 0;

    for(int i = 0; i < nameNum; i++)
        totalDistance += distanceArr[i];
    return totalDistance;
}