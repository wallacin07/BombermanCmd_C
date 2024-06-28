#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include "Personagens.h"
#ifndef FUNCOESADD_H
#define FUNCOESADD_H

int temParedeEntre(int x1, int y1, int x2, int y2, int **matriz) {
    if (x1 == x2) { // Movimento horizontal
        for (int j = (y1 < y2 ? y1 + 1 : y2 + 1); j < (y1 > y2 ? y1 : y2); j++) {
            if (matriz[x1][j] == 1) {
                return 1; // Há parede no caminho
            }
        }
    } else if (y1 == y2) { // Movimento vertical
        for (int i = (x1 < x2 ? x1 + 1 : x2 + 1); i < (x1 > x2 ? x1 : x2); i++) {
            if (matriz[i][y1] == 1) {
                return 1; // Há parede no caminho
            }
        }
    }
    return 0; // Não há parede no caminho
}

int checkVictory(Enemy *enemies) {
    for (int i = 0; i < NUM_ENEMIES; i++) {
        if (enemies[i].alive) {
            return 0; // Ainda há inimigos vivos
        }
    }
    return 1; // Todos os inimigos foram derrotados
}

#endif// !Inicio