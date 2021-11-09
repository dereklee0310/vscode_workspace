#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define STRSIZE 1024

// flag to determine if a newline is need to be printed
bool isStrPrinted = false;

// enumeration of instructions
enum ins{
    Insert,
    Delete,
    Swap,
    Query,
    Error
};

// structure of the nodes in linked list
struct node{
    char *name;
    int idx;
    struct node *next; 
};

// remove the unnecessary newline in given string
void removeNewline(char *buf);

// get the token of instruction
enum ins getToken(char *buf);

// insert the person after the the given position in queue
struct node *insert(struct node *queue, char *buf);

// delete the person at the given position in queue 
struct node *delete(struct node *queue, char *buf);

// swap the persons at the given positions
struct node *swap(struct node *queue, char *buf);

// print the name of the person which is at the given position
void query(struct node *queue, char *buf);

// create a new node for the insertion
struct node *createNewNode(int idx, char *name);

// change the indices due to the insertion or deletion
void changeIndex(struct node *nodePtr, int offset);

// concatenate the given nodes to swap node1 and node2
void concatenate(struct node **preNode1, struct node **preNode2, struct node **node1, struct node **node2);

int main() {
    enum ins token;
    struct node *queue;
    int numOfInstruction;
    char buf[STRSIZE];

    // create initial node
    queue = (struct node *)malloc(sizeof(struct node));
    queue->idx = 0;
    queue->next = NULL;

    scanf("%d", &numOfInstruction);
    getchar(); // flush the newline from buffer

    for(int i = 0; i < numOfInstruction; i++) {
        fgets(buf, STRSIZE + 1, stdin);
        removeNewline(buf);

        token = getToken(buf);
        switch(token) {
            case Insert:
                queue = insert(queue, buf);
                break;
            case Delete:
                queue = delete(queue, buf);
                break;
            case Swap:
                queue = swap(queue, buf);
                break;
            case Query:
                query(queue, buf);
                break;
            case Error:
                fprintf(stderr, "invalid instruction!\n");
                exit(1);
        }

        // print the newline if necessary
        if(i != numOfInstruction - 1 && isStrPrinted) {
            isStrPrinted = false;
            putchar('\n');
        }
    }

    // free memory
    struct node *nodePtr = queue;
    struct node *tmp = NULL;
    while(nodePtr) {
        tmp = nodePtr;
        free(tmp->name);
        free(tmp);
        nodePtr = nodePtr->next;
    }

    return 0;
}

void removeNewline(char *buf)
{   
    if(buf[strlen(buf) - 1] == '\n')
        buf[strlen(buf) - 1] = '\0';
}

enum ins getToken(char *buf)
{
    if(strncmp(buf, "insert", 6) == 0)
        return Insert;
    else if(strncmp(buf, "delete", 6) == 0)
        return Delete;
    else if(strncmp(buf, "swap", 4) == 0)
        return Swap;
    else if(strncmp(buf, "query", 5) == 0)
        return Query;
    return Error;
}

struct node *insert(struct node *queue, char *buf)
{   
    struct node *newNode;
    int idx;
    char instruction[STRSIZE];
    char name[STRSIZE];

    sscanf(buf, "%s %d %s", instruction, &idx, name);

    newNode = createNewNode(idx, name);

    struct node *nodePtr = queue;
    while(nodePtr && nodePtr->idx != idx)
        nodePtr = nodePtr->next;
    
    if(!nodePtr) {
        printf("no reslut");
        isStrPrinted = true;
        return queue;
    }

    newNode->next = nodePtr->next;
    nodePtr->next = newNode;

    // all the indices of nodes after the new node need to +1
    changeIndex(newNode->next, 1);

    return queue;
}

struct node *delete(struct node *queue, char *buf)
{   
    int idx;
    char instruction[STRSIZE];

    sscanf(buf, "%s %d", instruction, &idx);

    struct node *nodePtr = queue;
    struct node *lastNode = NULL;
    while(nodePtr && nodePtr->idx != idx) {
        lastNode = nodePtr;
        nodePtr = nodePtr->next;
    }

    if(!nodePtr || !lastNode) {
        printf("no reslut");
        isStrPrinted = true;
        return queue;
    }

    lastNode->next = nodePtr->next;
    free(nodePtr->name);
    free(nodePtr);

    // all the nodes afte the deleted node need to -1
    changeIndex(lastNode->next, -1);

    return queue;
} 

struct node *swap(struct node *queue, char *buf)
{   
    struct node *preNode1 = NULL, *preNode2 = NULL;
    struct node *node1 = NULL, *node2 = NULL;
    int idx1, idx2;
    char instruction[STRSIZE];

    sscanf(buf, "%s %d %d", instruction, &idx1, &idx2);

    if(idx1 == idx2)
        return queue;

    struct node *nodePtr = queue;
    while(nodePtr) {
        if(nodePtr->idx == idx1 - 1) {
            preNode1 = nodePtr;
            node1 = nodePtr->next;
        }
        if(nodePtr->idx == idx2 - 1) {
            preNode2 = nodePtr;
            node2 = nodePtr->next;
        }
        if(node1 && node2)
            break;

        nodePtr = nodePtr->next;
    }

    if(!nodePtr) { // if the given index is not in the queue, print no result
        printf("no result");
        isStrPrinted = true;
    } else {
        concatenate(&preNode1, &preNode2, &node1, &node2);
    }

    return queue;
}

void query(struct node *queue, char *buf)
{
    char instruction[STRSIZE];
    int idx;

    sscanf(buf, "%s %d", instruction, &idx);

    struct node *nodePtr = queue;
    while(nodePtr && nodePtr->idx != idx)
        nodePtr = nodePtr->next;

    if(nodePtr && nodePtr->name)
        printf("%s", nodePtr->name);
    else
        printf("no result");
    isStrPrinted = true;
}

struct node *createNewNode(int idx, char *name)
{   
    struct node *newNode;

    newNode = (struct node *)malloc(sizeof(struct node));
    newNode->name = (char *)malloc(sizeof(char) * strlen(name));
    newNode->idx = idx + 1;
    strcpy(newNode->name, name);
    return newNode;
}

void changeIndex(struct node *nodePtr, int offset)
{
    while(nodePtr) {
        nodePtr->idx += offset;
        nodePtr = nodePtr->next;
    }
}

void concatenate(struct node **preNode1, struct node **preNode2, struct node **node1, struct node **node2)
{
    (*preNode1)->next = *node2;
    (*preNode2)->next = *node1;

    int tmpIdx = (*node2)->idx;
    (*node2)->idx = (*node1)->idx;
    (*node1)->idx = tmpIdx;

    struct node *tmpPtr = (*node2)->next;
    (*node2)->next = (*node1)->next;
    (*node1)->next = tmpPtr;
}