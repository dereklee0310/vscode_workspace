#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXSTACKSIZE  size * size / 2 + 1

enum dir {
    Down,
    Right,
    Up,
    Left
};

struct node {
    short int row;
    short int col;
    short int dir;
};

struct st {
    struct node *stackArr;
    int top;
};

// create a new maze in a size of n x n and store the data
int **createMaze(int size);

// return the answer(2d array)
struct st findPath(int **maze, int size);

// move the mouse to the next position 
int moveforward();

// print the route of mouse
void printPath(struct st stack);

// check if the stack is empty
bool isEmpty(int top);

// check if the stack is full
bool isFull(int top, int size);

void push(struct st stack, struct node currentPos);

struct node pop(struct st stack);

int **createMap(size);


int main() {
    int numOfMaze = 0;
    int size = 0;
    int **maze = NULL;
    struct st stack;
    
    scanf("%d", &numOfMaze);

    for(int i = 0; i < numOfMaze; i++) {
        scanf("%d, &size");
        // create the maze and read the data
        maze = createMaze(size);

        // find a path
        stack = findPath(maze, size);

        printPath(stack);


        // remember to free the memory
    }

    return 0;
}

int **createMaze(int size)
{
    int **maze = NULL;
    int c = 0;

    maze = (int **)malloc(sizeof(int *) * size);
    for(int i = 0; i < size; i++)
        maze[i] = (int *)malloc(sizeof(int) * size);

    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            maze[i][j] = getchar();
        }
        getchar(); // remove the newline
    }

    return maze;
}

struct st findPath(int **maze, int size)
{
    struct st stack;

    stack.stackArr = (struct node *)malloc(sizeof(struct node) * MAXSTACKSIZE);

    // initialize the start position
    struct node currentPos = {
            .row = 0, .col = 0, .dir = 0
        };
    struct node nextPos = {
            .row = 0, .col = 0, .dir = 0
        };
    int **routeMap;
    bool isPathfound = false;
    int top = -1; // the top of stack array
    int row = 0;
    int col = 0;
    int dir = 0;

    routeMap = createMap(size);
    routeMap[0][0] = 1; // start position

    while(!isEmpty(stack.top) && !isPathfound) {
        currentPos = pop(stack);

        while(dir < 4 && !isPathfound) {
            nextPos.row = currentPos.row;
            nextPos.col = currentPos.col;

            switch(dir) {
                case 0:
                    nextPos.row += 1;
                    break;
                case 1:
                    nextPos.col += 1;
                    break;
                case 2:
                    nextPos.row -= 1;
                    break;
                case 3:
                    nextPos.col -= 1;
                    break;
            }

            if(nextPos.row == size - 1 && nextPos.col == size - 1) {
                isPathfound = true;
            } else if(maze[nextPos.row][nextPos.col] && routeMap[nextPos.row][nextPos.col]) {
                routeMap[nextPos.row][nextPos.col] = 1;
                push(stack, currentPos);
                currentPos.row = nextPos.row;
                currentPos.col = nextPos.col;
                dir = 0;
            } else {
                dir++;
            }
        }
    }

}

int moveforward();


int **createMap(size)
{
    int **routeMap = NULL;

    routeMap = (int **)malloc(sizeof(int *) * size);
    for(int i = 0; i < size; i++)
        routeMap[i] = (int *)malloc(sizeof(int) * size);

    // initialize the map of route
    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            routeMap[i][j] = 0;

    return routeMap;
}


// check if the stack is empty
bool isEmpty(int top)
{
    if(top < 0)
        return true;
    return false;
}

// check if the stack is full
bool isFull(int top, int size)
{
    if(top == MAXSTACKSIZE - 1)
        return true;
    return false;
}

void push(struct st stack, struct node currentPos)
{   
    stack.stackArr[++stack.top] = currentPos;
    return;
}

struct node pop(struct st stack)
{      
    return stack.stackArr[stack.top--];
}
