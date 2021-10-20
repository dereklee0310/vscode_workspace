#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAXLENGTH 2048
#define KEYLENGTH 5

void decrptText(char *ciphertext);
char *getKey(char *ciphertext);
int *getLps(char *key);
int getSumOfLps(int *lpsArr);
char *getPositions(char *article, char *key, int *lpsArr, int *position);


int main() {
    char ciphertext[MAXLENGTH];
    char article[MAXLENGTH];
    char *articlePtr = article;
    char ansDic[52][MAXLENGTH];
    char *key = NULL;
    int *lpsArr = NULL;
    int position = 0;
    int dif = 0;
    
    fgets(ciphertext, MAXLENGTH + 1, stdin);
    decrptText(ciphertext);
    printf("%s", ciphertext);

    key = getKey(ciphertext);
    printf("%s\n", key);

    lpsArr = getLps(key);
    int sum = getSumOfLps(lpsArr);
    printf("%d\n", sum);

    fgets(article, MAXLENGTH + 1, stdin);
    int posArr[MAXLENGTH];
    int i = 0;
    while(articlePtr) {
        articlePtr = getPositions(articlePtr, key, lpsArr, &position);
        if(position != -1) {
            posArr[i] = position + sum + dif;
            i++;
            dif += position + 1;
        } 
    }
    for(int j = 0; j < i; j++)
        printf("%d\n", posArr[j]);

    for(int i = 0; i < 52; i++) {
        fgets(ansDic[i], MAXLENGTH + 1, stdin);
        int len = strlen(ansDic[i]);
        ansDic[i][len - 1] = '\0';
    }
    int index = 0;
    char base;
    bool isFirst = true;
    for(int j = 0; j < i; j++) {
        if(isupper(posArr[j]))
            base = 'A';
        else
            base = 'a' - 26; // move 26 backward for the index in array.

        index = posArr[j] - base;
        if(isFirst)
            isFirst = false;
        else
            printf(" ");

        printf("%s", &ansDic[index][2]);
    }
    

    return 0;
}

void decrptText(char *ciphertext)
{   
    char *cipherPtr = ciphertext;
    char base;

    while(*cipherPtr != '\n') {
        if(isupper(*cipherPtr))
            base = 'A';
        else
            base = 'a';
        
        *cipherPtr = base + (*cipherPtr - base + 13) % 26;
        cipherPtr++;
    }
    return;
}

char *getKey(char *ciphertext)
{   
    char *key = malloc(sizeof(char) * KEYLENGTH);
    strncpy(key, ciphertext, 5);
    key[KEYLENGTH] = '\0'; 
    return key;
}

int *getLps(char *key)
{   
    int *lpsArr = malloc(sizeof(int) * KEYLENGTH);
    int i = 1, j = 0;
    
    lpsArr[j] = 0;
    while(i < KEYLENGTH) {
        if(key[i] == key[j]) {
            i++;
            j++;
            lpsArr[i - 1] = j;
        } else if(j == 0) {
            i++;
            lpsArr[i - 1] = j;
        } else {
            j = lpsArr[j - 1];
        }
    }
    return lpsArr;
}

int getSumOfLps(int *lpsArr)
{   
    int sum = 0;

    for(int i = 0; i < KEYLENGTH; i++)
        sum += lpsArr[i];
    return sum;
}

char *getPositions(char *article, char *key, int *lpsArr, int *position)
{   
    int i = 0, j = 0;
    int articleLen = strlen(article);

    while(i < articleLen && j < KEYLENGTH) {
        if(article[i] == key[j]) {
            i++;
            j++;
        } else if(j == 0){
            i++;
        } else {
            j = lpsArr[j - 1];
        }
    }

    if(j >= KEYLENGTH) {
        *position = i - KEYLENGTH;
        return &article[*position + 1]; // +1 for the start point of next pointer of the article.
    } else {
        *position = -1;
        return NULL;
    }
}