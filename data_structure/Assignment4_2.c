#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXQUEUESIZE 300

// structure of nodes in the BST tree
struct node {
    int data;
    struct node *left;
    struct node *right;
};

// structure of queue that record its front and rear 
struct que {
    int front;
    int rear;
    int queueArr[MAXQUEUESIZE];
};

// insert a new data into the tree
struct node *insert(struct node *tree, int data);

// push a node into the queue
void push(struct que *queue, int data);

// pop out a node from the queue
int pop(struct que *queue);

// initialize the values of front and rear of different queues respectively
void initQueue(struct que *keyQueue, struct que *treasureQueue, struct que *pathQueue);

// get the queue recording the path from root to the given node
struct que getQueue(struct node *tree, struct que *queue, int data);

// get the queue recording the path from root through the key node to the treasure node
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

    pathQueue = getPath(&pathQueue, keyQueue, treasureQueue);
    while(pathQueue.front != pathQueue.rear - 1) // leave out the last element in queue to avoid printing redundant "->"
        printf("%d->", pop(&pathQueue));
    printf("%d", pop(&pathQueue)); // print the last element in queue

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
    // path from root to the key node
    for(int i = keyQueue.front + 1; i < keyQueue.rear; i++)
        push(pathQueue, keyQueue.queueArr[i]);
    
    // find the lowest common ancestor between key node and treasure node
    while(keyQueue.queueArr[keyQueue.front + 1] == treasureQueue.queueArr[(treasureQueue.front + 1)]) {
        if(keyQueue.queueArr[(keyQueue.front + 2)] == treasureQueue.queueArr[(treasureQueue.front + 2)]) {
            pop(&keyQueue);
            pop(&treasureQueue);
        } else {
            pop(&keyQueue); // remove redundant ancestor nodes
            break;
        }
    }
    // pop out the elements in keyQueue reversely to get the path from key to lowest common ancestor
    for(int i = keyQueue.rear; i >= keyQueue.front + 1; i--)
        push(pathQueue, keyQueue.queueArr[i]);

    // path from lowest common ancestor to treasure node
    while(treasureQueue.front != treasureQueue.rear)
        push(pathQueue, pop(&treasureQueue));

    return *pathQueue;
}