#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

// a node in the linked list 
struct lt {
    int vertex;
    struct lt *next;
};

struct lt **list;
int *dfn;
int *low;
int *articulation;
int startPoint;
int artIndex = 0;
int initialIdx = 0;
int childCnt = 0;

// add a relation between vertices i and j to the adjacency list
void addVertex(int i, int j);

// find the low, dfn, and articulation points of the graph
void getArticulation(int curVertex, int preVertex);

// compare function for qsort, sort the articulation points to remove redundant points
int cmp(const void *num1, const void *num2);

// print the array according to the required format
void printArr(int *arr, int size);

// free the memory of the adjacency list
void freeList(struct lt ***list, int vertexNum);

int main() {
    int vertexNum, tmp;

    scanf("%d", &startPoint);
    startPoint--; // starpoint - 1 because of the difference beteen vertex number and array indices
    scanf("%d", &vertexNum);
    
    list = (struct lt **)malloc(sizeof(struct lt *) * vertexNum);
    dfn = (int *)malloc(sizeof(int) * vertexNum);
    low = (int *)malloc(sizeof(int) * vertexNum);
    articulation = (int *)malloc(sizeof(int) * vertexNum);

    for(int i = 0; i < vertexNum; i++) {
        list[i] = NULL;
        dfn[i] = -1;
    }

    // build an adjacency list for the graph
    for(int i = 0; i < vertexNum; i++) {
        for(int j = 0; j < vertexNum; j++) {
            scanf("%d", &tmp);
            if(tmp == 1)
                addVertex(i, j);
        }
    }

    getArticulation(startPoint, -1); // the parent of the root is set to -1
    if(childCnt > 1)
        articulation[artIndex++] = startPoint; // check if the root is an articulation point

    printArr(dfn, vertexNum);
    printArr(low, vertexNum);

    qsort(articulation, artIndex, sizeof(int), cmp);
    for(int i = 0; i < artIndex; i++)
        articulation[i]++;

    printf("%d", articulation[0]);
    for(int i = 1; i < artIndex; i++)
        if(articulation[i - 1] != articulation[i])
            printf(" %d", articulation[i]);
    putchar('\n');

    freeList(&list, vertexNum);
    free(dfn);
    free(low);
    free(articulation);

    return 0;
}

void addVertex(int i, int j)
{
    struct lt *newNode;

    newNode = (struct lt *)malloc(sizeof(struct lt));
    newNode->vertex = j;
    newNode->next = NULL;

    if(!list[i]) {
        list[i] = newNode;
    } else {
        struct lt *listPtr = list[i];
        while(listPtr->next)
            listPtr = listPtr->next;
        listPtr->next = newNode;
    }
}

void getArticulation(int curVertex, int preVertex)
{
    int vertex;
    struct lt *listPtr = list[curVertex];

    dfn[curVertex] = initialIdx;
    low[curVertex] = initialIdx;
    initialIdx++;

    while(listPtr) {
        vertex = listPtr->vertex;

        if(dfn[vertex] < 0) {
            if(curVertex == startPoint)
                childCnt++;
            getArticulation(vertex, curVertex);
            low[curVertex] = MIN(low[curVertex], low[vertex]);
 
            if(low[vertex] >= dfn[curVertex] && curVertex != startPoint)
                articulation[artIndex++] = curVertex;
        } else if(vertex != preVertex) {
            low[curVertex] = MIN(low[curVertex], dfn[vertex]);
        }
        listPtr = listPtr->next;
    }
}

int cmp(const void *num1, const void *num2)
{
    return *(int *)num1 - *(int *)num2;
}

void printArr(int *arr, int size)
{
    for(int i = 0; i < size - 1; i++)
        printf("%d ", arr[i]);
    printf("%d\n", arr[size - 1]);
}

void freeList(struct lt ***list, int vertexNum)
{   
    struct lt *listPtr = NULL;
    struct lt *tmp = NULL;

    for(int i = 0; i < vertexNum; i++) {
        listPtr = (*list)[i];
        while(listPtr) {
            tmp = listPtr;
            listPtr = listPtr->next;
            free(tmp);
        }
    }
    free(*list);
}