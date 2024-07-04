#include <stdio.h>
#include <stdlib.h>
#define MAX_LENGTH 256



void savescore(int pontuation)
{
    char nickName[20];
    printf("\n\nENTER YOUR NICK NAME: ");
    scanf("%s", nickName);
    FILE *f;
    char url[] = "Score.txt";
    f = fopen(url, "a");
    fprintf(f,"\n%s : %i", nickName, pontuation);
    fclose(f);
}

void ver_score()
{
    
    FILE *f;
    char url[] = "Score.txt";
    f = fopen(url, "r");
    char buffer[MAX_LENGTH];

    while (fgets(buffer, MAX_LENGTH, f))
        printf("%s", buffer);

    fclose(f);
}