#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXQUEUESIZE 300 // ! need to calculate

// structure of nodes in the BST tree
struct node {
    int data;
    struct node *left;
    struct node *right;
};

struct que {
    int front;
    int rear;
    int queueArr[MAXQUEUESIZE];
};

// insert a new data into the tree
struct node *insert(struct node *tree, int data);

// // check if the queue is empty
// bool isEmpty(void);

// push a node into the queue
void push(struct que *queue, int data);

// pop out a node from the queue
int pop(struct que *queue);

void initQueue(struct que *keyQueue, struct que *treasureQueue, struct que *pathQueue);

struct que getQueue(struct node *tree, struct que *queue, int data);

struct que getPath(struct que *pathQueue, struct que keyQueue, struct que treasureQueue);

int main() {
    struct node *tree = NULL;
    struct que keyQueue, treasureQueue, pathQueue;
    int numOfData;
    int data, key, treasure;

    scanf("%d", &numOfData);
    for(int i = 0; i < numOfData; i++) {
        scanf("%d", &data);
        tree = insert(tree, data);
    }

    scanf("%d", &key);
    scanf("%d", &treasure);
    
    initQueue(&keyQueue, &treasureQueue, &pathQueue);
    keyQueue = getQueue(tree, &keyQueue, key);
    treasureQueue = getQueue(tree, &treasureQueue, treasure);

    // while(keyQueue.front != keyQueue.rear - 1)
    //     printf("%d->", pop(&keyQueue));
    // printf("%d", pop(&keyQueue));
    // puts("\n-------------");
    // while(treasureQueue.front != treasureQueue.rear - 1)
    //     printf("%d->", pop(&treasureQueue));
    // printf("%d", pop(&treasureQueue));

    pathQueue = getPath(&pathQueue, keyQueue, treasureQueue);
    while(pathQueue.front != pathQueue.rear - 1)
        printf("%d->", pop(&pathQueue));
    printf("%d", pop(&pathQueue));

    return 0;
}

struct node *insert(struct node *tree, int data)
{
    struct node *newNode;

    newNode = (struct node *)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    if(!tree)
        return newNode;
    
    if(newNode->data < tree->data)
        tree->left = insert(tree->left, data);
    else
        tree->right = insert(tree->right, data);
    return tree;
}

// bool isEmpty(void)
// {
//     return front == rear ? true : false; 
// }

void push(struct que *queue, int data)
{
    queue->queueArr[++(queue->rear)] = data;
}

int pop(struct que *queue)
{   
    return queue->queueArr[++(queue->front)];
}

void initQueue(struct que *keyQueue, struct que *treasureQueue, struct que *pathQueue)
{
    keyQueue->front = -1;
    keyQueue->rear = -1;
    treasureQueue->front = -1;
    treasureQueue->rear = -1;
    pathQueue->front = -1;
    pathQueue->rear = -1;
}

struct que getQueue(struct node *tree, struct que *queue, int data)
{   
    if(!tree)
        return *queue;
    
    if(data == tree->data) {
        push(queue, tree->data);
        return *queue;
    } else if(data < tree->data) {
        push(queue, tree->data);
        getQueue(tree->left, queue, data);
    } else if(data > tree->data) {
        push(queue, tree->data);
        getQueue(tree->right, queue, data);
    }
    return *queue;
}

struct que getPath(struct que *pathQueue, struct que keyQueue, struct que treasureQueue)
{   
    for(int i = keyQueue.front + 1; i < keyQueue.rear; i++)
        push(pathQueue, keyQueue.queueArr[i]);

    while(keyQueue.queueArr[keyQueue.front + 1] == treasureQueue.queueArr[(treasureQueue.front + 1)]) {
        if(keyQueue.queueArr[(keyQueue.front + 2)] == treasureQueue.queueArr[(treasureQueue.front + 2)]) {
            pop(&keyQueue);
            pop(&treasureQueue);
        } else {
            pop(&keyQueue); // remove redundant parent node
            break;
        }
    }
    // pop out the elements in keyQueue reversely
    for(int i = keyQueue.rear; i >= keyQueue.front + 1; i--)
        push(pathQueue, keyQueue.queueArr[i]);
    while(treasureQueue.front != treasureQueue.rear)
        push(pathQueue, pop(&treasureQueue));

    return *pathQueue;
}