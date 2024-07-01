#include <stdio.h>
#ifndef PERSONAGEM_H
#define PERSONAGEM_H






#define L 9
#define C 15
#define ENEMY_SYMBOL 'E'
#define CHAR_SYMBOL 'P'
#define BOMB_SYMBOL 'O'
#define NUM_ENEMIES 5
#define BOMB_RANGE 2
#define INITIAL_LIVES 3

typedef struct 
{
    int x;
    int y;
    int lives;
}Character;

typedef struct 
{
    int xEnemy;
    int yEnemy;
    int direction;
    int alive;
}Enemy;





#endif 