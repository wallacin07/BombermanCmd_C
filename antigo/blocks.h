#ifndef BLOCKS
#define BLOCKS
#include <stdio.h>
#include "imports.h"


// Estrutura dos blocos, especificando com posição e tipo.
typedef struct block
{
    int x;
    int y;
    int type;
    wchar_t * img;
} block;

// Função de definição da textura dos blocos
void blockDefine(block * B)
{
    switch (B->type)
    {
    case 1:
        B->img = L"imagens/grama.bmp";
        break;
    
    default:
        break;
    }
}
/* 
Função de leitura do arquivo de mapa, fazemos a construção do mapa do Ternaria por meio da leitura desse arquivo.
*/ 
void readArchive(LList *lista)
{
    int count = 0;
    FILE * File = fopen("Map.txt", "r");

    while(!feof(File))
    {
        ++count;
        block *bloco = malloc(sizeof(block));
        fscanf(File, "%i,%i,%i", &bloco->x, &bloco->y, &bloco->type);
        blockDefine(bloco);
        LListAdd(lista, bloco);
    }
}
#endif 
