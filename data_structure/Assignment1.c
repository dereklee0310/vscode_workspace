#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ELEMENTNUM  5  

// each length of array + 1 for the space of '\0'.
struct info {
    char id[11];
    char name[26];
    char vaccineBrand[31];
    int age;
    char city[21];
};

void getData(struct info *vaccineInfo, int i);
void printInfo(struct info *vaccineInfo, int i);

int main() {
    bool isFirst = true;
    int dataNum;
    char brandName[31];
    struct info *vaccineInfo = NULL;

    scanf("%d", &dataNum);
    vaccineInfo = (struct info*)malloc(sizeof(struct info) * dataNum);
    
    for(int i = 0; i < dataNum; i++)
        getData(vaccineInfo, i);
        
    scanf("%s", brandName);

    for(int i = 0; i < dataNum; i++) {
        if(strcmp(brandName, vaccineInfo[i].vaccineBrand) == 0) {
            if(!isFirst)
                puts("");
            else
                isFirst = false;
            printInfo(vaccineInfo, i);
        }
    }

    return 0;
}

void getData(struct info *vaccineInfo, int i)
{
    scanf("%s", vaccineInfo[i].id);
    scanf("%s", vaccineInfo[i].name);
    scanf("%s", vaccineInfo[i].vaccineBrand);
    scanf("%d", &vaccineInfo[i].age);
    scanf("%s", vaccineInfo[i].city);

    return;
}

void printInfo(struct info *vaccineInfo, int i)
{   
    printf("%s ", vaccineInfo[i].id);
    printf("%s ", vaccineInfo[i].name);
    printf("%s ", vaccineInfo[i].vaccineBrand);
    printf("%d ", vaccineInfo[i].age);
    printf("%s", vaccineInfo[i].city);

    return;
}