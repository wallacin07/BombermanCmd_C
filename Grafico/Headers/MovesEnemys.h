#ifndef MOVESENEMYS_H
#define MOVESENEMYS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "Personagens.h"
#include "FuncoesAdd.h"

#define L 9
#define C 15
#define ENEMY_SYMBOL 'E'
#define CHAR_SYMBOL 'P'
#define NUM_ENEMIES 5
#define ENEMY_SPEED 800 // Velocidade dos inimigos em milissegundos

typedef struct {
    int matriz[L][C];
    Enemy *enemies;
    Character character;
    HANDLE hMutex;
} ThreadParams;

DWORD WINAPI moveEnemies(LPVOID lpParam) {
    ThreadParams *params = (ThreadParams *)lpParam;
    int (*matriz)[C] = params->matriz;
    Enemy *enemies = params->enemies;
    Character character = params->character;
    HANDLE hMutex = params->hMutex;

    while (1) {
        for (int i = 0; i < NUM_ENEMIES; i++) {
            if (!enemies[i].alive) continue;

            int x = enemies[i].xEnemy;
            int y = enemies[i].yEnemy;
            int newX = x;
            int newY = y;

            WaitForSingleObject(hMutex, INFINITE);

            // Código para perseguir o personagem
            int dx = character.x - x;
            int dy = character.y - y;

            // Verifica se o inimigo está na mesma linha ou coluna
            // e a uma distância máxima de 2 casas vazias
            if ((dx == 0 && abs(dy) <= 3 && !temParedeEntre(x, y, character.x, character.y, &matriz)) ||
                (dy == 0 && abs(dx) <= 3 && !temParedeEntre(x, y, character.x, character.y, &matriz))) {
                // Move o inimigo em direção ao jogador
                if (dx > 0) newX++;
                if (dx < 0) newX--;
                if (dy > 0) newY++;
                if (dy < 0) newY--;
            } else {
                // Movimento aleatório caso não esteja perto do personagem
                matriz[x][y] = 0; // Limpa a posição atual do inimigo
                enemies[i].direction = rand() % 4;

                switch (enemies[i].direction) {
                    case 0: // Movimento para cima
                        if (x > 0 && matriz[x - 1][y] == 0) {
                            newX--;
                        }
                        break;
                    case 1: // Movimento para baixo
                        if (x < L - 1 && matriz[x + 1][y] == 0) {
                            newX++;
                        }
                        break;
                    case 2: // Movimento para a esquerda
                        if (y > 0 && matriz[x][y - 1] == 0) {
                            newY--;
                        }
                        break;
                    case 3: // Movimento para a direita
                        if (y < C - 1 && matriz[x][y + 1] == 0) {
                            newY++;
                        }
                        break;
                }
            }

            // Verifica se a nova posição já está ocupada por outro inimigo
            int posicaoLivre = 1;
            for (int j = 0; j < NUM_ENEMIES; j++) {
                if (j != i && enemies[j].xEnemy == newX && enemies[j].yEnemy == newY && enemies[j].alive) {
                    posicaoLivre = 0;
                    break;
                }
            }

            // Move o inimigo se a nova posição estiver livre
            if (posicaoLivre) {
                matriz[x][y] = 0;
                enemies[i].xEnemy = newX;
                enemies[i].yEnemy = newY;
                matriz[newX][newY] = ENEMY_SYMBOL;
            }

            // Verifica se o inimigo encontrou o personagem
            if (enemies[i].xEnemy == character.x && enemies[i].yEnemy == character.y) {
                character.lives--;
                if (character.lives == 0) {
                    printf("Game Over\n");
                    exit(0);
                } else {
                    // Reinicia o personagem na posição inicial
                    matriz[character.x][character.y] = 0;
                    character.x = 0;
                    character.y = 0;
                    matriz[character.x][character.y] = CHAR_SYMBOL;
                }
            }

            ReleaseMutex(hMutex);
        }

        Sleep(ENEMY_SPEED);

        if (checkVictory(enemies)) {
            printf("You Win!\n");
            Sleep(2000);
            exit(0);
        }
    }
    return 0;
}

#endif
