#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define STRINGSIZE  100000
#define CLOCKWISE   1

// structure of a node in a list which consists people in Josephus problem
struct node {
    char *name;
    struct node *next;
};

// remove the unecessary newline in given string
void removeNewline(char *buf);

// create a circular linked list for solving Josephus problem
struct node *createList(struct node *list, char *buf);

// insert the person into the circular linked list
struct node *insert(struct node *list, struct node **tail, char *name);

// find the person killed in each turn and the person who is survived
void findSurvivor(struct node *list, int step, int direction);

int getSizeOfList(struct node *list);

struct node *delete(struct node **list, struct node **previousNode, struct node **listPtr, int direction);

int main() {
    struct node *list = NULL;
    char buf[STRINGSIZE];
    int step = 0;
    int direction = 0;

    fgets(buf, STRINGSIZE + 1, stdin);
    removeNewline(buf);
    scanf("%d %d", &step, &direction);
    list = createList(list, buf);
    // // test
    // struct node *testPtr = list;
    // while(testPtr->next != list) {
    //     printf("test_%s\n", testPtr->name);
    //     testPtr = testPtr->next;
    // }
    // printf("test_%s\n", testPtr->name);
    findSurvivor(list, step, direction);

    return 0;
}

void removeNewline(char *buf)
{   
    if(buf[strlen(buf) - 1] == '\n')
        buf[strlen(buf) - 1] = '\0';
}

struct node *createList(struct node *list, char *buf)
{   
    struct node *tail = list;
    char *name;

    name = strtok(buf, ", ");

    while(name != NULL) {
        // printf("test_%s\n", token);
        list = insert(list, &tail, name);
        name = strtok(NULL, ", ");
    }
    return list;
}

struct node *insert(struct node *list, struct node **tail, char *name)
{
    struct node *newNode;

    newNode = (struct node *)malloc(sizeof(struct node));
    newNode->name = malloc(sizeof(char) * strlen(name));
    strcpy(newNode->name, name);
    newNode->next = NULL;

    if(!list) {
        newNode->next = newNode;
        (*tail) = newNode;
        return newNode;
    }

    newNode->next = list;
    (*tail)->next = newNode;
    (*tail) = newNode;
    return list;
}

void findSurvivor(struct node *list, int step, int direction)
{   
    struct node *listPtr = list;
    struct node *previousNode = NULL;
    int size = 0;
    int killNumber;

    while(list->next != list) {
        // // test
        // struct node *testPtr = list;
        // while(testPtr->next != list) {
        //     printf("test_find_%s\n", testPtr->name);
        //     testPtr = testPtr->next;
        // }
        // printf("test_last_%s\n", testPtr->name);
        // // test
        size = getSizeOfList(list);
        // killNumber = (direction == CLOCKWISE) ? step : size - step;
        if(direction == CLOCKWISE) {
            killNumber = step;
        } else {
            if(step == size)
                killNumber = step;
            else if(step < size)
                killNumber = size - step;
            else
                killNumber = size - (step % size);
        }
        for(int i = 0; i < killNumber; i++) {
            previousNode = listPtr;
            listPtr = listPtr->next;
        }
        printf("%s is killed.\n", listPtr->name);

        listPtr = delete(&list, &previousNode, &listPtr, direction); // return the next position of deleted node (clockwise?).
    }

    printf("%s is survived.", listPtr->name);
}

int getSizeOfList(struct node *list)
{
    struct node* listPtr = list;
    int count = 0;

    while(listPtr->next != list) {
        count++;
        listPtr = listPtr->next;
    }
    count++;
    return count;
}

struct node *delete(struct node **list, struct node **previousNode, struct node **listPtr, int direction)
{   
    if(*listPtr == *list) {
        *list = (*listPtr)->next;
    }

    // // test
    // printf("test_%s__%s\n", (*previousNode)->next->name, (*listPtr)->next->name);
    // // test
    (*previousNode)->next = (*listPtr)->next;
    free((*listPtr)->name);
    free((*listPtr));

    if(direction == CLOCKWISE)
        return (*previousNode)->next;
    else
        return (*previousNode);
}