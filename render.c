#include "imports.h"
#include "functions.c"

void DrawMap(const LList * Map, HWND hwnd)
{
    HDC hdc = GetDC(hwnd);
    LLNode * N = Map->Head;
    for(int i = 0; i < Map->Size; ++i)
    {
        block * B = (block *) N->Value;
        DrawImg(hdc, B->x*32, 649 - (B->y*32), 32, 32, B->img);
        N = N->Next;
    }
    ReleaseDC(hwnd, hdc);
}