#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXSTACKSIZE  size * size / 2 + 1
#define MAXDIR  4

// direction of each positon in the maze
enum dir {
    Down,
    Right,
    Up,
    Left
};

// the info of a single position in the maze
struct node {
    short int row;
    short int col;
    short int dir;
};

// a stack record all the path that mouse has reached 
struct st {
    struct node *stackArr;
    int top;
};

// create a new maze and store the input in n x n maze
void createMaze(int ***maze, int size);

// return the stack of path except for the position of exit
struct st findPath(int **maze, int size);

// create and initialize a route map to record the position we have reached
void createRouteMap(int ***routeMap, int size);

// create a new stack and push the info of start position into it
void createStack(struct st *stack, int size);

// check if the stack is empty
bool isEmpty(int top);

// check if the stack is full
bool isFull(int top, int size);

// push the info of current position into the stack
void push(struct st *stack, struct node currentPos);

// pop out a position info from the top of stack
struct node pop(struct st *stack);

// check if the next position is out of the boundary of the maze
bool isOutOfBoundary(struct node nextPos, int size);

// check if the next positon has been reached 
bool isValidPos(int **maze, int **routeMap, struct node nextPos);

// calculate the next position by checking different direction and store it in next position
void setNextPos(struct node *currentPos, struct node *nextPos);

// create the map of the correct path
void createPathMap(int ***pathMap, struct st stack, int size);

// print out the path map
void printPath(int **pathMap, int size);

int main() {
    struct st stack;
    int numOfMaze = 0;
    int size = 0;
    int **maze = NULL;
    int **pathMap = NULL;
    
    scanf("%d", &numOfMaze);

    for(int i = 0; i < numOfMaze; i++) {
        scanf("%d", &size);
        getchar(); // remove the newline in the buffer

        createMaze(&maze, size);
        stack = findPath(maze, size);

        createPathMap(&pathMap, stack, size);

        printPath(pathMap, size);
        if(i != numOfMaze - 1)
            putchar('\n'); // add a new line after the last matrix

        // free memory
        free(stack.stackArr);
        for(int i = 0; i < size; i++) {
            free(maze[i]);
            free(pathMap[i]);
        }
        free(maze);
        free(pathMap);
    }

    return 0;
}

void createMaze(int ***maze, int size)
{
    *maze = (int **)malloc(sizeof(int *) * size);
    for(int i = 0; i < size; i++)
        (*maze)[i] = (int *)malloc(sizeof(int) * size);

    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            (*maze)[i][j] = getchar() - '0';
        }
        getchar(); // remove the newline
    }
}

struct st findPath(int **maze, int size)
{   
    bool isPathfound = false;
    struct node currentPos = {
        .row = 0, .col = 0, .dir = 0
    };
    struct node nextPos = {
        .row = 0, .col = 0, .dir = 0
    };
    struct st stack;    
    int exitCoord = size - 1;
    int **routeMap;

    createStack(&stack, size);
    createRouteMap(&routeMap, size);
    
    while(!isEmpty(stack.top) && !isPathfound) {
        currentPos = pop(&stack);
        while(currentPos.dir < MAXDIR && !isPathfound) {
            setNextPos(&currentPos, &nextPos);
            if(nextPos.row == exitCoord && nextPos.col == exitCoord) {
                isPathfound = true;
            } else if(isOutOfBoundary(nextPos, size) || !isValidPos(maze, routeMap, nextPos)) {
                currentPos.dir++;
            } else if(isValidPos(maze, routeMap, nextPos)){
                routeMap[nextPos.row][nextPos.col] = 1;
                if(isFull(stack.top, size))
                    exit(1);
                else
                    push(&stack, currentPos);
                currentPos = nextPos;
                currentPos.dir = 0;
            }
        }
    }
    push(&stack, currentPos);

    for(int i = 0; i < size; i++)
        free(routeMap[i]);
    free(routeMap);

    return stack;
}

void createRouteMap(int ***routeMap, int size)
{   
    int startCoord = 0;
    *routeMap = (int **)malloc(sizeof(int *) * size);
    for(int i = 0; i < size; i++)
        (*routeMap)[i] = (int *)malloc(sizeof(int) * size);

    // initialize
    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            (*routeMap)[i][j] = 0;
    (*routeMap)[startCoord][startCoord] = 1;
}

void createStack(struct st *stack, int size)
{
    stack->stackArr = (struct node *)malloc(sizeof(struct node) * MAXSTACKSIZE);

    stack->top = 0;
    stack->stackArr[0].row = 0;
    stack->stackArr[0].col = 0;
    stack->stackArr[0].dir = 0;
}

bool isEmpty(int top)
{
    if(top < 0)
        return true;
    return false;
}

bool isFull(int top, int size)
{
    if(top == MAXSTACKSIZE - 1)
        return true;
    return false;
}

void push(struct st *stack, struct node currentPos)
{   
    stack->stackArr[++(stack->top)] = currentPos;
}

struct node pop(struct st *stack)
{      
    return stack->stackArr[(stack->top)--];
}

bool isOutOfBoundary(struct node nextPos, int size)
{
    if(nextPos.row == -1 || nextPos.row == size || nextPos.col == -1 || nextPos.col == size)
        return true;
    return false;
}

bool isValidPos(int **maze, int **routeMap, struct node nextPos)
{   
    if(maze[nextPos.row][nextPos.col] == 1 && routeMap[nextPos.row][nextPos.col] == 0)
        return true;
    return false;
}

void setNextPos(struct node *currentPos, struct node *nextPos)
{   
    *nextPos = *currentPos;
    
    switch(currentPos->dir) {
        case Down:
            nextPos->row += 1;
            break;
        case Right:
            nextPos->col += 1;
            break;
        case Up:
            nextPos->row -= 1;
            break;
        case Left:
            nextPos->col -= 1;
            break;
    }
}

void createPathMap(int ***pathMap, struct st stack, int size)
{   
    int exitCoord = size - 1;

    *pathMap = (int **)malloc(sizeof(int *) * size);
    for(int i = 0; i < size; i++)
        (*pathMap)[i] = (int *)malloc(sizeof(int) * size);
    
    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            (*pathMap)[i][j] = 0;

    for(int i = 0; i <= stack.top; i++)
        (*pathMap)[stack.stackArr[i].row][stack.stackArr[i].col] = 1;
    (*pathMap)[exitCoord][exitCoord] = 1;
}

void printPath(int **pathMap, int size)
{   
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++)
            printf("%d", pathMap[i][j]);
        if(i != size - 1)
            putchar(' ');

        if(i != size - 1)
            putchar('\n'); // add a new line after each row
    }
}