#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include "File.h"

#define L 9
#define C 15
#define ENEMY_SYMBOL 'E'
#define CHAR_SYMBOL 'P'
#define BOMB_SYMBOL 'O'
#define NUM_ENEMIES 5
#define BOMB_RANGE 2
#define INITIAL_LIVES 3
#define ENEMY_SPEED 800 // Velocidade dos inimigos em milissegundos

// Variáveis globais para controle do jogo
int matriz[L][C] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1}
};

char fixedCharMatriz[L][C] = {
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#'},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#'},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#'},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#'},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#'},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#'},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#'},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#'}
};

struct Character {
    int x;
    int y;
    int lives;
};

struct Enemy {
    int xEnemy;
    int yEnemy;
    int direction;
    int alive;
};

struct Player {
    char nickName[15];
    int pontuation;
};

struct Character character;
struct Enemy enemies[NUM_ENEMIES];
int pontuation = 0;
HANDLE hMutex;
char nickName[20];
int eny = 5;
int gameOver = 0; // Variável global para controlar o estado do jogo

// Função para limpar a console
void clearConsole() {
    system("cls");
}

// Função para exibir a matriz com caracteres
void displayMatriz() {
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

int checkVictory() {
    for (int i = 0; i < NUM_ENEMIES; i++) {
        if (enemies[i].alive) {
            return 0; // Ainda há inimigos vivos
        }
    }
    eny = 0;
    savescore(pontuation);
    ver_score();
    gameOver = 1; // Defina gameOver como verdadeiro
    return 1; // Todos os inimigos foram derrotados
}

// Função para verificar se uma posição é válida para colocar a bomba
int isValidBombPosition(int x, int y) {
    if (x < 0 || x >= L || y < 0 || y >= C) {
        return 0;
    }
    return (matriz[x][y] == 0);
}

// Função para colocar a bomba ao lado do personagem
void placeBomb() {
    if (isValidBombPosition(character.x, character.y + 1)) {
        matriz[character.x][character.y + 1] = BOMB_SYMBOL;
    } else if (isValidBombPosition(character.x, character.y - 1)) {
        matriz[character.x][character.y - 1] = BOMB_SYMBOL;
    } else if (isValidBombPosition(character.x + 1, character.y)) {
        matriz[character.x + 1][character.y] = BOMB_SYMBOL;
    } else if (isValidBombPosition(character.x - 1, character.y)) {
        matriz[character.x - 1][character.y] = BOMB_SYMBOL;
    }
}

int temParedeEntre(int x1, int y1, int x2, int y2) {
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

// Função para explodir a bomba, corrigida para verificar paredes
void explodeBomb(int bombX, int bombY) {
    WaitForSingleObject(hMutex, INFINITE);

    matriz[bombX][bombY] = 0;

    for (int i = -BOMB_RANGE; i <= BOMB_RANGE; i++) {
        for (int j = -BOMB_RANGE; j <= BOMB_RANGE; j++) {
            int x = bombX + i;
            int y = bombY + j;

            if (x >= 0 && x < L && y >= 0 && y < C) {
                // Verifica se há uma parede entre a bomba e o alvo
                if (abs(i) + abs(j) > BOMB_RANGE || temParedeEntre(bombX, bombY, x, y)) {
                    continue;
                }

                if (matriz[x][y] == ENEMY_SYMBOL) {
                    matriz[x][y] = 0;
                    for (int k = 0; k < NUM_ENEMIES; k++) {
                        if (enemies[k].xEnemy == x && enemies[k].yEnemy == y) {
                            enemies[k].alive = 0;
                            pontuation += 100;
                            checkVictory();
                            break;
                        }
                    }
                } else if (matriz[x][y] == CHAR_SYMBOL) {
                    character.lives--;
                    if (character.lives <= 0) {
                        gameOver = 1; // Defina gameOver como verdadeiro
                    }
                }
            }
        }
    }
    ReleaseMutex(hMutex);
}

// Função para verificar e explodir bombas
void checkBombs() {
    if (gameOver) return; // Saia da função se o jogo acabou

    for (int i = 0; i < L; i++) {
        for (int j = 0; j < C; j++) {
            if (matriz[i][j] == BOMB_SYMBOL) {
                explodeBomb(i, j);
            }
        }
    }
}

// Função para mover o personagem
void moveCharacter(char direction) {
    if (gameOver) return; // Saia da função se o jogo acabou

    int newX = character.x;
    int newY = character.y;

    switch (direction) {
        case 'w':
            newX--;
            break;
        case 's':
            newX++;
            break;
        case 'a':
            newY--;
            break;
        case 'd':
            newY++;
            break;
        case 'b':
            placeBomb();
            return; // Não mover o personagem ao colocar a bomba
        default:
            return; // Tecla inválida
    }

    if (newX >= 0 && newX < L && newY >= 0 && newY < C && matriz[newX][newY] == 0) {
        matriz[character.x][character.y] = 0;
        character.x = newX;
        character.y = newY;
        matriz[character.x][character.y] = CHAR_SYMBOL;
    }
}

// Função para mover os inimigos
void moveEnemies() {
    if (gameOver) return; // Saia da função se o jogo acabou

    WaitForSingleObject(hMutex, INFINITE);
    for (int i = 0; i < NUM_ENEMIES; i++) {
        if (enemies[i].alive) {
            matriz[enemies[i].xEnemy][enemies[i].yEnemy] = 0;
            switch (enemies[i].direction) {
                case 0:
                    if (enemies[i].xEnemy > 0 && matriz[enemies[i].xEnemy - 1][enemies[i].yEnemy] == 0) {
                        enemies[i].xEnemy--;
                    } else {
                        enemies[i].direction = 1;
                    }
                    break;
                case 1:
                    if (enemies[i].xEnemy < L - 1 && matriz[enemies[i].xEnemy + 1][enemies[i].yEnemy] == 0) {
                        enemies[i].xEnemy++;
                    } else {
                        enemies[i].direction = 0;
                    }
                    break;
            }
            matriz[enemies[i].xEnemy][enemies[i].yEnemy] = ENEMY_SYMBOL;
        }
    }
    ReleaseMutex(hMutex);
}

// Função do loop do jogo
void gameLoop() {
    char input;
    time_t start, end;

    time(&start);
    while (!gameOver) {
        if (_kbhit()) {
            input = _getch();
            moveCharacter(input);
        }
        checkBombs();
        moveEnemies();
        displayMatriz();
        Sleep(ENEMY_SPEED);
        time(&end);
        if (difftime(end, start) >= 30.0) {
            break; // Interrompa o loop após 30 segundos
        }
    }
}

// Função principal
int main() {
    hMutex = CreateMutex(NULL, FALSE, NULL);

    printf("Digite o nickname do jogador: ");
    scanf("%s", nickName);

    // Inicializa o personagem
    character.x = 0;
    character.y = 0;
    character.lives = INITIAL_LIVES;
    matriz[character.x][character.y] = CHAR_SYMBOL;

    // Inicializa os inimigos
    srand(time(NULL));
    for (int i = 0; i < NUM_ENEMIES; i++) {
        enemies[i].xEnemy = rand() % L;
        enemies[i].yEnemy = rand() % C;
        enemies[i].direction = rand() % 2;
        enemies[i].alive = 1;
        if (matriz[enemies[i].xEnemy][enemies[i].yEnemy] == 0) {
            matriz[enemies[i].xEnemy][enemies[i].yEnemy] = ENEMY_SYMBOL;
        } else {
            i--;
        }
    }

    displayMatriz();
    gameLoop();

    printf("Game Over\n");
    CloseHandle(hMutex);
    return 0;
}
