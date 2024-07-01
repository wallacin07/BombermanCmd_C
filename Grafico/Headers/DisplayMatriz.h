#include <stdio.h>
#include <stdlib.h>
#include "Personagens.h"


#ifndef DISPLAY_H
#define DISPLAY_H

void clearConsole() {
    system("cls");
}




void displayMatriz(char **fixedCharMatriz, int **matriz, Character character) {
    clearConsole();
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < C; j++) {
            if (matriz[i][j] == ENEMY_SYMBOL) {
                printf("E ");
            } else if (matriz[i][j] == CHAR_SYMBOL) {
                printf("P ");
            } else if (matriz[i][j] == BOMB_SYMBOL) {
                printf("O ");
            } else {
                printf("%c ", fixedCharMatriz[i][j]);
            }
        }
        printf("\n");
    }
    printf("Lives: %d\n", character.lives);
}


#endif // !Inicio