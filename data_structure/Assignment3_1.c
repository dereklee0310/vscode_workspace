#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define STRSIZE 1024

enum ins{
    Insert,
    Delete,
    Swap,
    Query
};

//insert delete swap query

struct node{
    char *name;
    int idx;
    struct node *next; 
};

void removeNewline(char *buf);

enum ins getToken(char *buf);

struct node insert(struct node *queue, char *buf);

struct node delete(struct node *queue, char *buf);

struct node swap(struct node *queue, char *buf);

void query(struct node *queue, char *buf);

int getIdx(char *buf);

int getName(char *buf);

int main() {
    enum ins token;
    struct node *queue;
    int numOfInstruction;
    int token;
    char buf[STRSIZE];

    queue = (struct node *)malloc(sizeof(struct node));
    queue->idx = 0;
    queue->next = NULL;

    scanf("%d", &numOfInstruction);

    buf = malloc(sizeof(char) * ma)
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
            default:
                fprintf(stderr, "invalid instruction!\n");
                exit(1);
        }   
    }

    return 0;
}

void removeNewline(char *buf)
{   
    if(buf[strlen(buf) - 1 == '\n'])
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
}

struct node insert(struct node *queue, char *buf)
{   
    char *bufPtr = buf + 7; // move to the position of index in buf
    struct node *newNode = (struct node *)malloc(sizeof(struct node));

    newNode->idx = getIdx(bufPtr); //! +1 because it need to be appended after the position of idx (use anotehr idx to record it)
    newNode->name = getName(bufPtr);

    if(!queue) {
        newNode->next = NULL;
        return newNode;
    }
        struct node *queuePtr = queue;
        while(queuePtr && queuePtr->idx != newNode->idx)
            queuePtr = queuePtr->next;
        
        if(!queuePtr) {
            printf("no reslut\n");
            return queue;
        }
    
        newNode->next = queuePtr->next;
        queuePtr->next = newNode;
        return queue;
}

struct node delete(struct node *queue, char *buf)
{   
    char *bufPtr = buf + 7;
    int idx;
    char *name;
    struct node *lastPtr = NULL;

    idx = getIdx(bufPtr);
    name = getName(bufPtr);

    struct node *queuePtr = queue;
    while(queuePtr && queuePtr->idx != idx) {
        lastPtr = queuePtr;
        queuePtr = queuePtr->next;
    }
    if(!queuePtr) {
        printf("no reslut\n");
        return queue;
    }

    lastPtr->next = queuePtr->next;
    free(queuePtr);
    return queue;

}

struct node swap(struct node *queue, char *buf)
{   
    char *bufPtr = buf + 4;
    int idx1 = getIdx(bufPtr);
    int idx2 = getIdx(bufPtr); // !wrong
    struct node *lastPtr = NULL;
    struct node *lastPtr1 = NULL;
    struct node *lastPtr2 = NULL;
    struct node *node1;
    struct node *node2;

    struct node queuePtr = queue;
    while(queuePtr) {
        lastPtr = queuePtr;
        if(queuePtr->idx == idx1) {
            lastPtr1 = lastPtr;
            node1 = queuePtr;
        }
        if(queuePtr->idx == idx2) {
            lastPtr2 = lastPtr;
            node2 = queuePtr;
        }

        if(node1 && node2)
            break;

        queuePtr = queuePtr->next;
    }

    if(!queuePtr) {
        printf("no reslut\n");
        return queue;
    }

    // swap
    node2->next = lastPtr1->next;
    lastPtr1->next = node2;

    node1->next = lastPtr2->next;
    lastPtr2->next = node1;

    return queue;
}

void query(struct node *queue, char *buf)
{
    struct node *queuePtr = queue;
    char *bufPtr = buf + 5;

    int idx = getIdx(bufPtr);

    while(queuePtr && queuePtr->idx) {
        if(queuePtr->idx == idx)
            break;
        queuePtr = queuePtr->next;
    }

    if(queuePtr) {
        printf("%s\n", queuePtr->name);
    }
}

int getIdx(char *buf)
{
    return atoi(buf); //! use strtol?
}

int getName(char *buf)
{
    char *bufPtr = buf;

    while(*bufPtr && isdigit(*bufPtr))
        bufPtr++;
    return bufPtr;
}