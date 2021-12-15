#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX 1000000001

// create and initialize an adjacency matrix
int **createMatrix(int **adjMatrix, int vertexNum);

// shortest path algorithm
int *Dijkstra(int **adjMatrix, int vertexNum, int root);

// get the unprocessed vertex in gragh, which will be used by Dijkstra algorithm
int getMin(int *distanceArr, int vertexNum, bool *isfound);

// calculate the total distance from root to all vertices
int getTotalDistance(int *distanceArr, int vertexNum);

int main() {
    int **adjMatrix;
    char names[2048][21];
    int vertexNum, edgeNum;
    int vertex1, vertex2, distance;
    int totalDistance;
    int minDistance = -1;
    int minIdx = -1;
    int cnt = 1;

    scanf("%d %d", &vertexNum, &edgeNum);
    while(vertexNum != 0 && edgeNum != 0) {
        adjMatrix = createMatrix(adjMatrix, vertexNum);
        for(int i = 0; i < vertexNum; i++)
            scanf("%s", names[i]);
        for(int i = 0; i < edgeNum; i++) {
            scanf("%d %d %d", &vertex1, &vertex2, &distance);
            // -1 because of the difference between array indices and vertex
            vertex1--; 
            vertex2--;
            adjMatrix[vertex1][vertex2] = distance;
            adjMatrix[vertex2][vertex1] = distance;
        }

        int *distanceArr = (int *)malloc(sizeof(int) * vertexNum);
        minDistance = -1;
        for(int i = 0; i < vertexNum; i++) {
            distanceArr = Dijkstra(adjMatrix, vertexNum, i);
            totalDistance = getTotalDistance(distanceArr, vertexNum);
            if(minDistance == -1 || totalDistance < minDistance) {
                minIdx = i;
                minDistance = totalDistance;
            }
        }
        
        printf("Case #%d %s\n", cnt, names[minIdx]);
        cnt++;
        free(distanceArr);
        
        scanf("%d %d", &vertexNum, &edgeNum);
    }
    for(int i = 0; i < vertexNum; i++)
        free(adjMatrix[i]);
    free(adjMatrix);

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

int getTotalDistance(int *distanceArr, int vertexNum)
{   
    int totalDistance = 0;

    for(int i = 0; i < vertexNum; i++)
        totalDistance += distanceArr[i];
        
    return totalDistance;
}