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
    int life;
    HBITMAP img;
} character;

/*
Estrutura do zumbi.
*/

typedef struct enemy
{
    int xPos, yPos;
    int xSubPos, ySubPos;
    HBITMAP img;
} laele;

#endif