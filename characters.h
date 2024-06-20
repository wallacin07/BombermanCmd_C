#ifndef CHARACTERS
#define CHARACTERS

/* 
Estrutura dos personagens, especificando posição e subposição.
A subposição serve para calcular colisões entre personagem e bloco.
*/

typedef struct character
{
    int xPos, yPos;
    int xSubPos, ySubPos;
    int inventory[32];
    int life;
    int damage;
    char * img;
} character;

/*
Estrutura do zumbi.
*/

typedef struct zombie
{
    int life;
    int damage;
    int xPos, yPos;
    int xSubPos, ySubPos;
    char * img;
} zombie;

#endif