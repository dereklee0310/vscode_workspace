#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define STRINGSIZE 1024

enum pre {
    leftParen,
    rightParen, 
    plus,
    minus,
    times,
    divide
};

struct st {
    enum pre stackArr[STRINGSIZE];
    int top;
};

struct postSt {
    int stackArr[STRINGSIZE];
    int top;
};

bool isValid(char *buf);

bool isValidPos(char *postfix);

char *toPostfix(char *buf);

void removeNewline(char *buf);

enum pre getToken(char symbol);

bool isEmpty(int top);

void push(struct st *stack, enum pre token);

enum pre pop(struct st *stack);

char getSymbol(enum pre token);

void postPush(struct postSt *stack, int element);

enum pre postPop(struct postSt *stack);

int main() {
    bool isFisrt = true;
    int numOfCase = 0;
    char buf[STRINGSIZE];
    char *postfix = malloc(sizeof(char) * STRINGSIZE);

    scanf("%d", &numOfCase);
    getchar();

    for(int i = 0; i < numOfCase; i++) {
        fgets(buf, 1025, stdin);
        if(isFisrt)
            isFisrt = false;
        else
            puts("");
        if(isValid(buf)) {
            postfix = toPostfix(buf);
            if(isValidPos(postfix)) {
                printf("1 %s", postfix);
                continue;
            }
        }

        printf("0");
    }
    // free memory
    free(postfix);
    return 0;
}

bool isValid(char *buf)
{   
    bool digitFlag = false;
    bool operatorFlag = false;
    char *bufPtr = buf;
    enum pre token;
    enum pre isp[] = {0, 19, 12, 12, 13, 13}; // in-stack precedence
    enum pre icp[] = {20, 19, 12, 12, 13, 13}; // incoming precedence
    char symbolArr[] = "()+-*/";
    char parenArr[] = "()";
    char operatorArr[] = "+-*/";
    struct st stack;
    stack.top = -1;

    removeNewline(buf);

    //new test of invalid example
    if(strcmp(buf, "()") == 0)
        return false;
    else if(strlen(buf) == 1 && isdigit(*buf))
        return false;


    // check if there is invalid character
    // puts("valid?");
    while(*bufPtr) {
        if(!isdigit(*bufPtr) && !strchr(symbolArr, *bufPtr))
            return false;
        bufPtr++;
    }
    // check if there is any invalid parentheses
    bufPtr = buf;
    while(*bufPtr) {
        if(!isdigit(*bufPtr)) {
            token = getToken(*bufPtr);
            if(token == rightParen) {
                if(isEmpty(stack.top))
                    return false;
                    // int count = 0; //test
                while(stack.stackArr[stack.top] != leftParen) {
                    // count++;
                    pop(&stack);
                    if(isEmpty(stack.top))
                        return false;
                }
                // if(count == 0)
                //     return false;
                pop(&stack);
            } else {
                while(!isEmpty(stack.top) && isp[stack.stackArr[stack.top]] >= icp[token])
                    pop(&stack);
                push(&stack, token);
            }
        }
        bufPtr++;
    }

    // check if there is an operator after the leftParen or before the rightParen
    bufPtr = buf;
    while(*bufPtr) {
        if(*bufPtr == '(')
            if(strchr(operatorArr, *(bufPtr + 1)))
                return false;
        else if(*bufPtr == ')')
            if(strchr(operatorArr, *(bufPtr - 1)))
                return false;
        bufPtr++;
    }

    while(!isEmpty(stack.top)) {
        token = pop(&stack);
        if(strchr(parenArr, token))
            return false;
    }
    
    // check if there is any set of consecutive operators or digits
    bufPtr = buf;
    while(*bufPtr) {
        if(isdigit(*bufPtr)) {
            if(digitFlag)
                return false;

            digitFlag = true;
            operatorFlag = false; 
        } else if(strchr(operatorArr, *bufPtr)) {
            if(operatorFlag)
                return false;

            digitFlag = false;
            operatorFlag = true;

        }
        bufPtr++;
    }
    // puts("test_first_valid");
    return true;
}

// validate the postfix expression
bool isValidPos(char *postfix)
{   
    char *postPtr = postfix;
    struct postSt stack;
    stack.top = -1;
    int operand1;
    int operand2;

    while(*postPtr) {
        if(isdigit(*postPtr))
            postPush(&stack, *postPtr - '0');
        else {
            if(stack.top < 1)
                return false;
            operand2 = postPop(&stack);
            operand1 = postPop(&stack);

            switch(*postPtr) {
                case '+':
                    postPush(&stack, operand1 + operand2);
                    break;
                case '-':
                    postPush(&stack, operand1 - operand2);
                    break;
                case '*':
                    postPush(&stack, operand1 * operand2);
                    break;
                case '/':
                    postPush(&stack, operand1 / operand2);
                    break;
            }
        }
        postPtr++;
    }
    postPop(&stack);
    if(stack.top != -1)
        return false;

    // puts("test_post_valid");
    return true;
}

char *toPostfix(char *buf)
{   
    enum pre isp[] = {0, 19, 12, 12, 13, 13}; // in-stack precedence
    enum pre icp[] = {20, 19, 12, 12, 13, 13}; // incoming precedence
    char *postfixArr = malloc(sizeof(char) * STRINGSIZE);
    char *bufPtr = buf;
    char *postfixPtr = postfixArr;
    enum pre token;
    struct st stack;
    stack.top = -1;
    
    while(*bufPtr) {
        if(isdigit(*bufPtr)) {
            *postfixPtr++ = *bufPtr;
        } else {
            token = getToken(*bufPtr);
            if(token == rightParen) {
                // puts("rightparen");
                while(stack.stackArr[stack.top] != leftParen) {
                    *postfixPtr++ = getSymbol(pop(&stack));
                    // printf("while_top_%d\n", stack.top);
                }
                pop(&stack);
            } else {
                // puts("here");
                while(!isEmpty(stack.top) && isp[stack.stackArr[stack.top]] >= icp[token]) {
                    *postfixPtr++ = getSymbol(pop(&stack));
                }
                push(&stack, token);
            }
        }
        // printf("test_whileloop_top_%d__%c\n", stack.top, getSymbol(stack.stackArr[stack.top]));
        bufPtr++;
    }
    // printf("tset_str_%s\n", buf);
    // printf("test_top_%d\n", stack.top);
    while(!isEmpty(stack.top)) {
        *postfixPtr++ = getSymbol(pop(&stack));
        // printf("test_____empty\n");
    }
    *postfixPtr = '\0';
    return postfixArr;
}

void removeNewline(char *buf)
{
    if(buf[strlen(buf) - 1] == '\n')
        buf[strlen(buf) - 1] = '\0';
    return;
}

enum pre getToken(char symbol)
{   
    enum pre token;
    switch(symbol) {
        case '(':
            token = leftParen;
            break;
        case ')':
            token = rightParen;
            break;
        case '+':
            token = plus;
            break;
        case '-':
            token = minus;
            break;
        case '*':
            token = times;
            break;
        case '/':
            token = divide;
            break;
    }

    return token;
}

bool isEmpty(int top)
{
    if(top < 0)
        return true;
    return false;
}

void push(struct st *stack, enum pre token)
{
    stack->stackArr[++(stack->top)] = token;
    // printf("push_%d\n", stack->top);
    return;
}

enum pre pop(struct st *stack)
{   
    // printf("pop%d\n", stack->top);
    return stack->stackArr[(stack->top)--];
}

char getSymbol(enum pre token)
{   
    char symbol;
    switch(token) {
        case leftParen:
            symbol = '(';
            break;
        case rightParen:
            symbol = ')';
            break;
        case plus:
            symbol = '+';
            break;
        case minus:
            symbol = '-';
            break;
        case times:
            symbol = '*';
            break;
        case divide:
            symbol = '/';
            break;
    }

    return symbol;
}

void postPush(struct postSt *stack, int element)
{
    stack->stackArr[++(stack->top)] = element;
    // printf("push_%d\n", stack->top);
    return;
}

enum pre postPop(struct postSt *stack)
{   
    // printf("pop%d\n", stack->top);
    return stack->stackArr[(stack->top)--];
}
