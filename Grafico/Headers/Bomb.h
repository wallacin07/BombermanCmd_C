#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include "Personagens.h"
#include "FuncoesAdd.h"
#ifndef BOMB_H
#define BOMB_H
#define BOMB_RANGE 2


HANDLE hMutex;

int isValidBombPosition(int x, int y, int **matriz) {
    if (x < 0 || x >= L || y < 0 || y >= C) {
        return 0;
    }
    return (matriz[x][y] == 0);
}

void placeBomb(Character character, int **matriz) {
    if (isValidBombPosition(character.x, character.y + 1,matriz)) {
        matriz[character.x][character.y + 1] = BOMB_SYMBOL;
    } else if (isValidBombPosition(character.x, character.y - 1,matriz)) {
        matriz[character.x][character.y - 1] = BOMB_SYMBOL;
    } else if (isValidBombPosition(character.x + 1, character.y,matriz)) {
        matriz[character.x + 1][character.y] = BOMB_SYMBOL;
    } else if (isValidBombPosition(character.x - 1, character.y,matriz)) {
        matriz[character.x - 1][character.y] = BOMB_SYMBOL;
    }
}

void explodeBomb(int bombX, int bombY, Character character, int **matriz, Enemy *enemies) {
    WaitForSingleObject(hMutex, INFINITE);

    matriz[bombX][bombY] = 0;

    for (int i = -BOMB_RANGE; i <= BOMB_RANGE; i++) {
        for (int j = -BOMB_RANGE; j <= BOMB_RANGE; j++) {
            int x = bombX + i;
            int y = bombY + j;

            if (x >= 0 && x < L && y >= 0 && y < C) {
                // Verifica se há uma parede entre a bomba e o alvo
                if (abs(i) + abs(j) > BOMB_RANGE || temParedeEntre(bombX, bombY, x, y, matriz)) {
                    continue; // Pula para o próximo alvo se houver parede
                }

                if (matriz[x][y] == ENEMY_SYMBOL) {
                    // Mata o inimigo
                    for (int k = 0; k < NUM_ENEMIES; k++) {
                        if (enemies[k].xEnemy == x && enemies[k].yEnemy == y && enemies[k].alive) {
                            enemies[k].alive = 0;
                            matriz[x][y] = 0; // Limpa a posição do inimigo morto
                            break; // Sai do loop após matar o inimigo
                        }
                    }
                } else if (matriz[x][y] == CHAR_SYMBOL) {
                    // Diminui a vida do personagem
                    character.lives--;
                    if (character.lives == 0) {
                        printf("Game Over\n");
                        exit(0);
                    }

                    // Move o personagem para a posição inicial
                    matriz[character.x][character.y] = 0;
                    character.x = 0;
                    character.y = 0;
                    matriz[character.x][character.y] = CHAR_SYMBOL;
                } 
            }
        }
    }

    ReleaseMutex(hMutex);
}

DWORD WINAPI checkBombs(LPVOID lpParam, int **matriz, Character character, Enemy *enemies) {
    while (1) {
        for (int i = 0; i < L; i++) {
            for (int j = 0; j < C; j++) {
                if (matriz[i][j] == BOMB_SYMBOL) {
                    Sleep(2000); // Tempo para explosão da bomba
                    explodeBomb(i, j, character,matriz,enemies);
                }
            }
        }
        Sleep(100); 
    }
    return 0;
}

#endif // !Inicio