#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAXBUFSIZE 4096

int main() {
    FILE* filePtr1;
    FILE* filePtr2;

    // correct output
    if(NULL == (filePtr1 = fopen("filename.c", "r"))) {
        fprintf(stderr, "the file doesn't exit!\n");
        exit(1);
    }

    //my output
    if(NULL == (filePtr2 = fopen("filename.c", "r"))) {
        fprintf(stderr, "the file doesn't exit!\n");
        exit(1);
    }
    
    while(true) {
        
    }

    fclose(filePtr);
    return 0;
}