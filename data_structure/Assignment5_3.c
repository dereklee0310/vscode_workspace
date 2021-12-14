#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 1000000000

int **createMatrix(int **adjMatrix, int pointNum);

void addEdge(int **adjMatrix, int name1, int name2, int distance);

int *Dijkstra(int **adjMatrix, int pointNum, int source);

int getMin(int *distanceArr, int pointNum, bool *isfound);

int getTotalDistance(int *distanceArr, int nameNum);

int main() {
    int **adjMatrix;
    char names[2048][21];
    int nameNum, edgeNum;
    int name1, name2, distance;
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
            scanf("%d %d %d", &name1, &name2, &distance);
            addEdge(adjMatrix, name1 - 1, name2 - 1, distance);
        }

        int *distanceArr = (int *)malloc(sizeof(int) * nameNum);
        minDistance = -1;
        for(int i = 0; i < nameNum; i++) {
            distanceArr = Dijkstra(adjMatrix, nameNum, i);
            totalDistance = getTotalDistance(distanceArr, nameNum);
            // printf("test_%d\n", totalDistance);
            if(minDistance == -1 || totalDistance < minDistance) {
                minIdx = i;
                minDistance = totalDistance;
            }
        }
        
        printf("Case #%d %s\n", cnt, names[minIdx]);
        cnt++;

        scanf("%d %d", &nameNum, &edgeNum);
    }

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
                adjMatrix[i][j] = 1000000000;
        }
    return adjMatrix;
}

void addEdge(int **adjMatrix, int name1, int name2, int distance)
{
    adjMatrix[name1][name2] = distance;
    adjMatrix[name2][name1] = distance;
}

int *Dijkstra(int **adjMatrix, int pointNum, int source)
{   
    int *distanceArr;
    bool *isfound;
    int curPoint;

    distanceArr = (int *)malloc(sizeof(int) * pointNum);
    isfound = (bool *)malloc(sizeof(bool) * pointNum);
    for(int i = 0; i < pointNum; i++) {
        distanceArr[i] = adjMatrix[source][i];
        isfound[i] = false;
    }
    
    isfound[source] = true;
    distanceArr[source] = 0;
    for(int i = 0; i < pointNum - 2; i++) {
        curPoint = getMin(distanceArr, pointNum, isfound);
        for(int j = 0; j < pointNum; j++)
            if(!isfound[j])
                if(distanceArr[curPoint] + adjMatrix[curPoint][j] < distanceArr[j])
                    distanceArr[j] = distanceArr[curPoint] + adjMatrix[curPoint][j];
    }

    return distanceArr;
}

int getMin(int *distanceArr, int pointNum, bool *isfound)
{
    int minPos = 0;
    int min = MAX + 1;

    for(int i = 0; i < pointNum; i++) {
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