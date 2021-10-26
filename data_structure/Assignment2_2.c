#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define STRINGSIZE 1024

// precedence of operators and parentheses
enum pre {
    LeftParen,
    RightParen, 
    Plus,
    Minus,
    Times,
    Divide
};

// a stack store the operators in the transformation of infix to postfix
struct st {
    enum pre stackArr[STRINGSIZE];
    int top;
};

// a stack store the digits in the evaluation of postfix
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
    int numOfCase = 0;
    char buf[STRINGSIZE];
    char *postfix = malloc(sizeof(char) * STRINGSIZE);

    scanf("%d", &numOfCase);
    getchar(); // remove the newline which was left in the buffer by using scanf

    for(int i = 0; i < numOfCase; i++) {
        fgets(buf, STRINGSIZE + 1, stdin);
        removeNewline(buf);
        
        if(isValid(buf)) {
            postfix = toPostfix(buf);
            if(isValidPos(postfix))
                printf("1 %s", postfix);
            else
                putchar('0');
        }
        else
            putchar('0');
        if(i != numOfCase - 1)
            putchar('\n');
    }
    // free memory
    free(postfix);
    return 0;
}

bool isValid(char *buf)
{   
    enum pre token;
    enum pre isp[] = {0, 19, 12, 12, 13, 13}; // in-stack precedence
    enum pre icp[] = {20, 19, 12, 12, 13, 13}; // incoming precedence
    char *bufPtr = buf;
    char symbolArr[] = "()+-*/";
    char parenArr[] = "()";
    char operatorArr[] = "+-*/";
    struct st stack;
    stack.top = -1;

    if(strlen(buf) == 1 && isdigit(*buf))
        return false;

    // check if there is invalid character
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
            if(token == RightParen) {
                if(isEmpty(stack.top))
                    return false;
                while(stack.stackArr[stack.top] != LeftParen) {
                    pop(&stack);
                    if(isEmpty(stack.top))
                        return false;
                }
                pop(&stack);
            } else {
                while(!isEmpty(stack.top) && isp[stack.stackArr[stack.top]] >= icp[token])
                    pop(&stack);
                push(&stack, token);
            }
        }
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
            if(token == RightParen) {
                while(stack.stackArr[stack.top] != LeftParen)
                    *postfixPtr++ = getSymbol(pop(&stack));
                pop(&stack);
            } else {
                while(!isEmpty(stack.top) && isp[stack.stackArr[stack.top]] >= icp[token])
                    *postfixPtr++ = getSymbol(pop(&stack));
                push(&stack, token);
            }
        }
        bufPtr++;
    }

    while(!isEmpty(stack.top))
        *postfixPtr++ = getSymbol(pop(&stack));
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
            token = LeftParen;
            break;
        case ')':
            token = RightParen;
            break;
        case '+':
            token = Plus;
            break;
        case '-':
            token = Minus;
            break;
        case '*':
            token = Times;
            break;
        case '/':
            token = Divide;
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
}

enum pre pop(struct st *stack)
{   
    return stack->stackArr[(stack->top)--];
}

char getSymbol(enum pre token)
{   
    char symbol;
    switch(token) {
        case LeftParen:
            symbol = '(';
            break;
        case RightParen:
            symbol = ')';
            break;
        case Plus:
            symbol = '+';
            break;
        case Minus:
            symbol = '-';
            break;
        case Times:
            symbol = '*';
            break;
        case Divide:
            symbol = '/';
            break;
    }

    return symbol;
}

void postPush(struct postSt *stack, int element)
{
    stack->stackArr[++(stack->top)] = element;
}

enum pre postPop(struct postSt *stack)
{   
    return stack->stackArr[(stack->top)--];
}
