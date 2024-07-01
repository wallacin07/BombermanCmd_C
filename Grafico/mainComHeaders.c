#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "Headers/DisplayMatriz.h"
#include "Headers/Bomb.h"
#include "Headers/interface.h"
#include "Headers/MovesCharacter.h"
#include "Headers/MovesEnemys.h"

int main() {
    int matriz[L][C] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    char fixedCharMatriz[L][C] = {
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
};


    Character character;
    Enemy enemies[NUM_ENEMIES];
    HANDLE hMutex;
    srand(time(NULL));
    character.x = 0;
    character.y = 0;
    character.lives = INITIAL_LIVES;
    matriz[character.x][character.y] = CHAR_SYMBOL;

    for (int i = 0; i < NUM_ENEMIES; i++) {
        enemies[i].alive = 1;
        do {
            enemies[i].xEnemy = rand() % L;
            enemies[i].yEnemy = rand() % C;
        } while (matriz[enemies[i].xEnemy][enemies[i].yEnemy] != 0);
        matriz[enemies[i].xEnemy][enemies[i].yEnemy] = ENEMY_SYMBOL;
    }

    hMutex = CreateMutex(NULL, FALSE, NULL);

    // Inicialize os parâmetros da thread de inimigos
    ThreadParams enemyParams;
    memcpy(enemyParams.matriz, matriz, sizeof(matriz));
    enemyParams.enemies = enemies;
    enemyParams.character = character;
    enemyParams.hMutex = hMutex;

    // Crie a thread passando os parâmetros
    HANDLE hThreadEnemies = CreateThread(NULL, 0, moveEnemies, &enemyParams, 0, NULL);

    // Inicialize os parâmetros da thread de bombas
    BombParams bombParams;
    memcpy(bombParams.matriz, matriz, sizeof(matriz));
    bombParams.character = character;
    bombParams.enemies = enemies;
    bombParams.hMutex = hMutex;

    // Crie a thread passando os parâmetros
    HANDLE hThreadBombs = CreateThread(NULL, 0, checkBombs, &bombParams, 0, NULL);

    // Inicialize os parâmetros da thread do personagem
    CharacterParams characterParams;
    memcpy(characterParams.matriz, matriz, sizeof(matriz));
    characterParams.character = character;
    characterParams.hMutex = hMutex;

    // Crie a thread passando os parâmetros
    HANDLE hThreadCharacter = CreateThread(NULL, 0, moveCharacter, &characterParams, 0, NULL);

    // Código adicional, como movimentação do personagem, bombas, etc.
        while (1) {
        displayMatriz(fixedCharMatriz,matriz,character);
        Sleep(100);
    }

    // Espere as threads terminarem (se necessário)
    WaitForSingleObject(hThreadEnemies, INFINITE);
    WaitForSingleObject(hThreadBombs, INFINITE);
    WaitForSingleObject(hThreadCharacter, INFINITE);

    // Libere o mutex
    CloseHandle(hMutex);

    return 0;
}
