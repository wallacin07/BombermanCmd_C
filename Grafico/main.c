#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h> // Para captura de tecla no Windows
#include <windows.h> // Para Sleep e threads no Windows

#define L 9
#define C 15
#define ENEMY_SYMBOL 'E'
#define CHAR_SYMBOL 'P'
#define BOMB_SYMBOL 'O'
#define NUM_ENEMIES 5
#define BOMB_RANGE 2
#define INITIAL_LIVES 3

struct Character {
    int x;
    int y;
    int lives;
};

struct Enemy {
    int xEnemy;
    int yEnemy;
    int direction;
    int alive; // Indicador se o inimigo está vivo (1) ou não (0)
};

// Variáveis globais para controle do jogo
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

struct Character character;
struct Enemy enemies[NUM_ENEMIES];

// Mutex para sincronização de acesso à matriz
HANDLE hMutex;

// Função para limpar a console
void clearConsole() {
    system("cls");
}

// Função para converter a matriz de inteiros para uma matriz de caracteres para exibição
void convertToCharMatriz(char charMatriz[L][C]) {
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < C; j++) {
            if (matriz[i][j] == 0) {
                charMatriz[i][j] = ' ';
            } else if (matriz[i][j] == 1) {
                charMatriz[i][j] = '#';
            } else if (matriz[i][j] == ENEMY_SYMBOL) {
                charMatriz[i][j] = 'E';
            } else if (matriz[i][j] == CHAR_SYMBOL) {
                charMatriz[i][j] = 'P';
            } else if (matriz[i][j] == BOMB_SYMBOL) {
                charMatriz[i][j] = 'O';
            }
        }
    }
}

// Função para exibir a matriz com caracteres
void displayMatriz() {
    clearConsole();
    char charMatriz[L][C];
    convertToCharMatriz(charMatriz);
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < C; j++) {
            printf("%c ", charMatriz[i][j]);
        }
        printf("\n");
    }
    printf("Lives: %d\n", character.lives);
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
    // Procura um espaço vazio ao lado do personagem para colocar a bomba
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

// Função para verificar se um inimigo está no alcance da explosão da bomba
int isInBombRange(int x, int y, int bombX, int bombY) {
    return (abs(x - bombX) <= BOMB_RANGE && abs(y - bombY) <= BOMB_RANGE);
}

// Função para explodir a bomba
void explodeBomb(int bombX, int bombY) {
    WaitForSingleObject(hMutex, INFINITE); // Bloqueia o acesso à matriz durante a explosão

    for (int i = 0; i < NUM_ENEMIES; i++) {
        if (enemies[i].alive && isInBombRange(enemies[i].xEnemy, enemies[i].yEnemy, bombX, bombY)) {
            enemies[i].alive = 0;
            matriz[enemies[i].xEnemy][enemies[i].yEnemy] = 0;
        }
    }
    matriz[bombX][bombY] = 0; // Remove a bomba do mapa

    ReleaseMutex(hMutex); // Libera o acesso à matriz
}

// Função para verificar se todos os inimigos foram eliminados
int checkVictory() {
    for (int i = 0; i < NUM_ENEMIES; i++) {
        if (enemies[i].alive) {
            Sleep(2000);
            return 0;
        }
    }
    Sleep(2000);
    return 1;
}

// Função para mover os inimigos
DWORD WINAPI moveEnemies(LPVOID lpParam) {
    while (1) {
        for (int i = 0; i < NUM_ENEMIES; i++) {
            if (!enemies[i].alive) continue;

            int x = enemies[i].xEnemy;
            int y = enemies[i].yEnemy;

            WaitForSingleObject(hMutex, INFINITE); // Bloqueia o acesso à matriz durante o movimento

            matriz[x][y] = 0;

            enemies[i].direction = rand() % 4;

            switch (enemies[i].direction) {
                case 0: // Movimento para cima
                    if (x > 0 && (matriz[x - 1][y] == 0 || matriz[x - 1][y] == CHAR_SYMBOL)) {
                        enemies[i].xEnemy--;
                    }
                    break;
                case 1: // Movimento para baixo
                    if (x < L - 1 && (matriz[x + 1][y] == 0 || matriz[x + 1][y] == CHAR_SYMBOL)) {
                        enemies[i].xEnemy++;
                    }
                    break;
                case 2: // Movimento para a esquerda
                    if (y > 0 && (matriz[x][y - 1] == 0 || matriz[x][y - 1] == CHAR_SYMBOL)) {
                        enemies[i].yEnemy--;
                    }
                    break;
                case 3: // Movimento para a direita
                    if (y < C - 1 && (matriz[x][y + 1] == 0 || matriz[x][y + 1] == CHAR_SYMBOL)) {
                        enemies[i].yEnemy++;
                    }
                    break;
            }

            if (enemies[i].alive) {
                matriz[enemies[i].xEnemy][enemies[i].yEnemy] = ENEMY_SYMBOL;
            }

            ReleaseMutex(hMutex); // Libera o acesso à matriz
            Sleep(200); // Intervalo entre movimentos dos inimigos
        }

        if (checkVictory()) {
            printf("You Win!\n");
            Sleep(2000);
            exit(0);
        }
    }
    return 0;
}

// Função para mover o personagem
DWORD WINAPI moveCharacter(LPVOID lpParam) {
    while (1) {
        if (_kbhit()) {
            char key = _getch();
            int newX = character.x, newY = character.y;

            switch (key) {
                case 'w': // Movimento para cima
                    if (character.x > 0 && matriz[character.x - 1][character.y] == 0) {
                        newX--;
                    }
                    break;
                case 's': // Movimento para baixo
                    if (character.x < L - 1 && matriz[character.x + 1][character.y] == 0) {
                        newX++;
                    }
                    break;
                case 'a': // Movimento para a esquerda
                    if (character.y > 0 && matriz[character.x][character.y - 1] == 0) {
                        newY--;
                    }
                    break;
                case 'd': // Movimento para a direita
                    if (character.y < C - 1 && matriz[character.x][character.y + 1] == 0) {
                        newY++;
                    }
                    break;
                case ' ': // Colocar bomba
                    placeBomb();
                    break;
            }

            WaitForSingleObject(hMutex, INFINITE); // Bloqueia o acesso à matriz durante o movimento do personagem

            matriz[character.x][character.y] = 0;
            character.x = newX;
            character.y = newY;
            matriz[character.x][character.y] = CHAR_SYMBOL;

            ReleaseMutex(hMutex); // Libera o acesso à matriz

            displayMatriz(); // Atualiza a matriz após o movimento
        }

        Sleep(150); // Intervalo de verificação de tecla pressionada
    }

    return 0;
}

// Função para verificar e explodir bombas no mapa
DWORD WINAPI checkBombs(LPVOID lpParam) {
    while (1) {
        for (int i = 0; i < L; i++) {
            for (int j = 0; j < C; j++) {
                if (matriz[i][j] == BOMB_SYMBOL) {
                    Sleep(2000); // Tempo para explosão da bomba
                    explodeBomb(i, j);
                }
            }
        }
        Sleep(100); // Intervalo de verificação de bombas
    }
    return 0;
}

int main() {
    srand((unsigned int)time(NULL));

    hMutex = CreateMutex(NULL, FALSE, NULL); // Cria o mutex para sincronização de acesso à matriz

    // Inicializa os inimigos em posições aleatórias válidas
    for (int i = 0; i < NUM_ENEMIES; i++) {
        do {
            enemies[i].xEnemy = rand() % L;
            enemies[i].yEnemy = rand() % C;
        } while (matriz[enemies[i].xEnemy][enemies[i].yEnemy] != 0);

        enemies[i].alive = 1; // Define que o inimigo está vivo
        matriz[enemies[i].xEnemy][enemies[i].yEnemy] = ENEMY_SYMBOL;
    }

    // Inicializa o personagem
    character.lives = INITIAL_LIVES;
    do {
        character.x = rand() % L;
        character.y = rand() % C;
    } while (matriz[character.x][character.y] != 0);

    matriz[character.x][character.y] = CHAR_SYMBOL;

    // Cria threads para mover o personagem, os inimigos, verificar/explodir bombas e exibir a matriz
    HANDLE hThreadChar = CreateThread(NULL, 0, moveCharacter, NULL, 0, NULL);
    HANDLE hThreadEnemies = CreateThread(NULL, 0, moveEnemies, NULL, 0, NULL);
    HANDLE hThreadBombs = CreateThread(NULL, 0, checkBombs, NULL, 0, NULL);

    // Loop principal para exibir a matriz continuamente
    while (1) {
        displayMatriz();
        Sleep(500); // Intervalo entre atualizações da tela
    }

    CloseHandle(hThreadChar);
    CloseHandle(hThreadEnemies);
    CloseHandle(hThreadBombs);

    CloseHandle(hMutex); // Libera o mutex

    return 0;
}
