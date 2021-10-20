#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct TURTLE{
    int pos[2]; //y, x
    int heading; //0, 1, 2, 3 : 東,南,西,北
}turtle;

bool isPenDown = false;
int maxRowSize = 0;
int maxColumnSize = 0;
void changeDir(int change);
void moveForward(int arr[50][50], int steps);
void printArr(int arr[50][50]);

int main() {
    int arr[50][50];
    char steps[2];
    char command = 0;

    turtle.pos[0] = 0;
    turtle.pos[1] = 0;
    turtle.heading = 0;
    for(int i = 0; i < 50; i++)
        for(int j = 0; j < 50; j++)
            arr[i][j] = 0;

    while(scanf("%c", &command) != EOF) {
        switch(command) {
            case '1':
                isPenDown = false;
                break;
            case '2':
                isPenDown = true;
                if(arr[turtle.pos[0]][turtle.pos[1]] == 0) {
                    arr[turtle.pos[0]][turtle.pos[1]] = 1;
                    maxRowSize += 1;
                    maxColumnSize += 1;
                }
                break;
            case '3':
                changeDir(1);
                break;
            case '4':
                changeDir(-1);
                break;
            case '5':
                scanf(",%s", steps);
                moveForward(arr, atoi(steps));
                break;
            case '6':
                printArr(arr);
                break;
            case '9':
                return 0;
                break;
        }
    }
    return 0;
}

void changeDir(int change)
{
    turtle.heading += change;
    if(turtle.heading == 4)
        turtle.heading = 0;
    else if(turtle.heading == -1)
        turtle.heading = 3;
    return;
}

void moveForward(int arr[50][50], int steps)
{   
    switch(turtle.heading) {
        case 0:
            if(isPenDown)
                for(int i = 0; i <= steps; i++)
                    arr[turtle.pos[0]][turtle.pos[1] + i] = 1;
            turtle.pos[1] += steps;
            if(turtle.pos[1] + 1> maxRowSize)
                maxRowSize = turtle.pos[1] + 1;
            break;
        case 1:
            if(isPenDown)
                for(int i = 0; i <= steps; i++)
                    arr[turtle.pos[0] + i][turtle.pos[1]] = 1;
            turtle.pos[0] += steps;
            if(turtle.pos[0] + 1> maxColumnSize)
                maxColumnSize = turtle.pos[0] + 1;
            break;
        case 2:
            if(isPenDown)
                for(int i = 0; i <= steps; i++)
                    arr[turtle.pos[0]][turtle.pos[1] - i] = 1; 
            turtle.pos[1] -= steps;
            break;
        case 3:
            if(isPenDown)
                for(int i = 0; i <= steps; i++)
                    arr[turtle.pos[0] - i][turtle.pos[1]] = 1;
            turtle.pos[0] -= steps;
            break;
    }
    return;
}

void printArr(int arr[50][50]) {
    // printf("%d__%d\n", maxColumnSize, maxRowSize);
    for(int i = 0; i < maxColumnSize; i++) {
        for(int j = 0; j < maxRowSize; j++) {
            if(arr[i][j] != 0)
                putchar('*');
            else
                putchar(' ');
        }
        puts("");
    }
    return;
}