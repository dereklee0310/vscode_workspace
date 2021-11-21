#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAZQUEUESIZE 123 // ! need to calculate

// structure of nodes in the BST tree
struct node {
    int data;
    struct node *left;
    struct node *right;
};

struct node *queue[MAXQUEUESIZE];
int front = -1;
int rear = -1;

// insert a new data into the tree
struct node *insert(struct node *tree, int data);

// delete a data in the tree
struct node *delete(struct node *tree, int data);

// print the sequence of data in infix order
void printInfixOrder(struct node *tree);

// print the sequence of data in level order
void printLevelOrder(struct node *tree);

// check if the queue is empty
bool isEmpty(void)

// push a node into the queue
void push(struct node *treeNode);

// pop out a node from the queue
struct node *pop(void);

int main() {
    struct node *tree = NULL;
    int numOfData;
    int data;

    scanf("%d", &numOfData);
    for(int i = 0; i < numOfData; i++)
        tree = insert(tree, data);

    scanf("%d", numOfData);
    for(int i = 0; i < numOfData; i++)
    tree = delete(tree, data);
    

    puts("Output:");
    print("Infixorder:");
    printInfixOrder(tree);
    putchar('\n');
    puts("Levelorder:");
    printLevelOrder(tree);
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
    return tree;D
}

struct node *delete(struct node *tree, int data)
{   
    if(!tree)
        return tree;

    if(data == tree->data) {
        if(!tree->left && !tree->right) {
            free(tree);
            tree = NULL;
        } else if(tree->left && !tree->right) {
            // todo
        }
    } else if(data < tree->data) {
        delete(tree->left, data);
    } else {
        delete(tree->right, data);
    }
    return tree;
}

void printInfixOrder(struct node *tree
{   
    printInfixOrder(tree->left);
    print(" %d", tree->data);
    printInfixOrder(tree->right);
}

void printLevelOrder(struct node *tree)
{   
    struct node *currentNode = NULL:

    push(tree);
    
    while(!isEmpty) {
        currentNode = pop();
        printf(" %d", currentNode->data);
        if(currentNode->left)
            push(currentNode->left);
        if(currentNode->right)
            push(currentNode->right);
    }
}

bool isEmpty(void)
{
    return front == queue ? true : false; 
}

void push(struct node *treeNode);
{
    queue[++rear] = treeNode;
}

struct node *pop(void)
{   
    return queue[++front];
}
