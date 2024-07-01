#ifndef MOVESCHARACTER_H
#define MOVESCHARACTER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include "Personagens.h"
#include "Bomb.h"

#define L 9
#define C 15
#define ENEMY_SYMBOL 'E'
#define CHAR_SYMBOL 'P'
#define BOMB_SYMBOL 'O'
#define NUM_ENEMIES 5
#define BOMB_RANGE 2
#define INITIAL_LIVES 3
#define ENEMY_SPEED 800 // Velocidade dos inimigos em milissegundos

typedef struct {
    int (*matriz)[C];
    Character character;
    HANDLE hMutex;
} CharacterParams;

// Função para mover o personagem
DWORD WINAPI moveCharacter(LPVOID lpParam) {
    CharacterParams *params = (CharacterParams *)lpParam;
    int (*matriz)[C] = params->matriz;
    Character *character = &(params->character);
    HANDLE hMutex = params->hMutex;

    while (1) {
        if (_kbhit()) {
            char input = _getch();
            int newX = character->x;
            int newY = character->y;

            switch (input) {
                case 'w': // Para cima
                    newX--;
                    break;
                case 's': // Para baixo
                    newX++;
                    break;
                case 'a': // Para a esquerda
                    newY--;
                    break;
                case 'd': // Para a direita
                    newY++;
                    break;
                case ' ': // Colocar bomba
                    placeBomb(*character, matriz);
                    break;
            }

            // Verifica se a nova posição é válida
            if (newX >= 0 && newX < L && newY >= 0 && newY < C && matriz[newX][newY] == 0) {
                WaitForSingleObject(hMutex, INFINITE);
                matriz[character->x][character->y] = 0; 
                character->x = newX;
                character->y = newY;
                matriz[character->x][character->y] = CHAR_SYMBOL; 
                ReleaseMutex(hMutex); 
            }
        }
        Sleep(100); 
    }
    return 0;
}

#endif // MOVESCHARACTER_H
