#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

struct lt {
    int vertex;
    struct lt *next;
};

struct lt **list;
int *dfn;
int *low;
int *articulation;
int artIndex = 0;
int idx = 0;
int startPoint;
int childCnt = 0;

void addVertex(int i, int j);

void getArticulation(int curVertex, int preVertex);

int cmp(const void *num1, const void *num2);

int main() {
    int vertexNum, tmp;

    scanf("%d", &startPoint);
    startPoint--;
    scanf("%d", &vertexNum);

    dfn = (int *)malloc(sizeof(int) * vertexNum);
    low = (int *)malloc(sizeof(int) * vertexNum);
    articulation = (int *)malloc(sizeof(int) * vertexNum);

    list = (struct lt **)malloc(sizeof(struct lt *) * vertexNum);
    for(int i = 0; i < vertexNum; i++)
        list[i] = NULL;

    for(int i = 0; i < vertexNum; i++) {
        for(int j = 0; j < vertexNum; j++) {
            scanf("%d", &tmp);
            if(tmp == 1)
                addVertex(i, j);
        }
    }

    // for(int i = 0; i < vertexNum; i++) {
    //     struct lt *listPtr = list[i];
    //     while(listPtr) {
    //         printf("test_%d_%d\n", i, listPtr->vertex);
    //         listPtr = listPtr->next;
    //     }
    // }

    // init
    for(int i = 0; i < vertexNum; i++)
        dfn[i] = -1;

    getArticulation(startPoint, -1);

    if(childCnt > 1)
        articulation[artIndex++] = startPoint;

    for(int i = 0; i < vertexNum; i++) {
        printf("%d", dfn[i]);
        if(i != vertexNum - 1)
            putchar(' ');
        else
            putchar('\n');
    }
    for(int i = 0; i < vertexNum; i++) {
        printf("%d", low[i]);
        if(i != vertexNum - 1)
            putchar(' ');
        else
            putchar('\n');
    }

    // condition for only 1 point
    // if(vertexNum == 1) {
    //     printf("1\n");
    //     return 0;
    // }


    qsort(articulation, artIndex, sizeof(int), cmp);
    for(int i = 0; i < artIndex; i++)
        articulation[i]++;

    // test
    for(int i = 0; i < artIndex; i++)
        printf("test_%d\n", articulation[i]);

    for(int i = 0; i < artIndex; i++) {
        if(i == 0 || articulation[i - 1] != articulation[i]) {
            printf("%d", articulation[i]);
            if(i != vertexNum - 1)
                putchar(' ');
            else
                putchar('\n');
        }
    }

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

    dfn[curVertex] = idx;
    low[curVertex] = idx;
    idx++;


    while(listPtr) {
        vertex = listPtr->vertex;
        if(dfn[vertex] < 0) {
            getArticulation(vertex, curVertex);
            low[curVertex] = MIN(low[curVertex], low[vertex]);

            if(curVertex == startPoint)
                childCnt++;
 
            if(low[vertex] >= dfn[curVertex] && curVertex != startPoint) {
                // printf("low_dfn_%d_%d\n", low[vertex], dfn[curVertex]);
                // printf("lowIdx_dfnIdx_%d_%d\n", vertex, curVertex);
                articulation[artIndex++] = curVertex;
            }
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