#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXSIZE   256

char source[MAXSIZE];
char target[MAXSIZE];
unsigned char stack[MAXSIZE];
char record[MAXSIZE * 2];
int len = 0;

// if there is a newline before null character, remove it
void removeNewline(char *string);

// search all the possible set of order with push and pop
void searchSequence(int cnt, int pushCnt, int popCnt);

// print out the sequence of i(push) and o(pop)
void printSequence(int cnt);

int main() {
    int numOfCase = 0;
    stack[0] = 1; // stack[0] store the information of the top of stack

    scanf("%d", &numOfCase);
    getchar();

    for(int i = 0; i < numOfCase; i++) {
        fgets(source, MAXSIZE + 1, stdin);
        removeNewline(source);
        fgets(target, MAXSIZE + 1, stdin);
        removeNewline(target);

        len = strlen(source);
        printf("[\n");
        if(len == strlen(target))
            searchSequence(0, 0, 0);
        printf("]");
        if(i != numOfCase - 1)
            putchar('\n');
    }
    return 0;     
}

void searchSequence(int cnt, int pushCnt, int popCnt)
{   
    // terminating condition
    if(pushCnt == len && popCnt == len) {
        printSequence(cnt);
        return;
    }
    
    if(pushCnt < len && stack[0] < MAXSIZE) {
        record[cnt] = 'i';
        stack[stack[0]] = source[pushCnt];
        stack[0]++;
        searchSequence(cnt + 1, pushCnt + 1, popCnt);
        stack[0]--;
    }
    
    if(stack[0] > 0 && target[popCnt] == stack[stack[0] - 1]) {
        record[cnt] = 'o';
        int tmp = stack[stack[0] - 1];
        stack[0]--;
        searchSequence(cnt + 1, pushCnt, popCnt + 1);
        stack[stack[0]] = tmp;
        stack[0]++;
    }
    return;
}

void printSequence(int cnt)
{   
    for(int i = 0; i < cnt; i++) {
        printf("%c", record[i]);
        if(i != cnt - 1)
            printf(" ");
    }
    putchar('\n');
}

void removeNewline(char *string)
{   
    int lastPos = strlen(string);
    if(string[lastPos- 1] == '\n')
        string[lastPos - 1] = '\0';
}