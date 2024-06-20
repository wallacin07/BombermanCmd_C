#include "imports.h"

// typedef struct block
// {
//     int x;
//     int y;
//     int type;
// } block;


int main(){
    LList *lista;
    readArchive(lista);
    for(int i = 0; i < 100; i++)
    {
        printf("%d %d %d\n", ((block *)LListGet(lista, i))->x, ((block *)LListGet(lista, i))->y, ((block *)LListGet(lista, i))->type);
    }
}