/* Compile:
gcc main.c -o main.exe -l gdi32 -l msimg32
*/

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>
#include "imports.h"
#include "render.c"


typedef struct {
    int xPos;
    int yPos;
    int xSubPos;
    int ySubPos;
    HBITMAP img;
} enemy;

DWORD ThreadID;
HANDLE Thread;

struct ImportantStuff
{
    LList Map;
} GameData;

character player;
enemy inimigo;

// Função da thread principal
DWORD WINAPI MainThread(LPVOID lpParam)
{
    HWND hwnd = *((HWND *)lpParam);

    int gameover = 0;
    player.xPos = 10;
    player.yPos = 10;
    player.xSubPos = 0;
    player.ySubPos = 0;
    player.img = LoadImage(NULL, L"imagens/man.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    if (player.img == NULL) {
        MessageBox(NULL, L"Failed to load player image!", L"Error", MB_OK | MB_ICONERROR);
    }

    inimigo.xPos = 500;
    inimigo.yPos = 430;
    inimigo.xSubPos = 0;
    inimigo.ySubPos = 0;
    inimigo.img = LoadImage(NULL, L"imagens/enemy.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    if (inimigo.img == NULL) {
        MessageBox(NULL, L"Failed to load enemy image!", L"Error", MB_OK | MB_ICONERROR);
    }

    LListCreate(&GameData.Map);

    // Simulação do loop principal do jogo
    while (!gameover)
    {
        // Atualizações do jogo aqui

        // Redesenhar a janela
        InvalidateRect(hwnd, NULL, TRUE);
        Sleep(16); // Para aproximadamente 60 FPS
    }

    return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    switch(Msg)
    {
        case WM_PAINT:
        {
            PAINTSTRUCT PS;
            HDC hdc = BeginPaint(hwnd, &PS);

            // Desenhar o fundo
            DrawImg(hdc, 0, 0, 960, 720, L"imagens/BOMBERMAN.bmp");

            // Desenhar o mapa
            DrawMap(&GameData.Map, hwnd);

            // Desenhar o sprite do jogador
            if (player.img != NULL)
            {
                HDC hdcMem = CreateCompatibleDC(hdc);
                SelectObject(hdcMem, player.img);
                BITMAP bm;
                GetObject(player.img, sizeof(bm), &bm);
                BitBlt(hdc, player.xPos, player.yPos, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);
                DeleteDC(hdcMem);
            }

            // Desenhar o sprite do inimigo
            if (inimigo.img != NULL)
            {
                HDC hdcMem = CreateCompatibleDC(hdc);
                SelectObject(hdcMem, inimigo.img);
                BITMAP bm;
                GetObject(inimigo.img, sizeof(bm), &bm);
                BitBlt(hdc, inimigo.xPos, inimigo.yPos, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);
                DeleteDC(hdcMem);
            }

            EndPaint(hwnd, &PS);
        }
        break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
        break;
        case WM_DESTROY:
            PostQuitMessage(0);
        break;
        default:
            return DefWindowProc(hwnd, Msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    const wchar_t WClassName[]  = L"Ternaria";
    MSG Msg;
    WNDCLASS Window = {};
    Window.lpfnWndProc = WndProc;
    Window.hInstance = hInstance;
    Window.lpszClassName = WClassName;

    if(!RegisterClass(&Window))
    {
        MessageBox(NULL, L"Window Class Registration Failed", L"Error", MB_ICONERROR | MB_OK);
        return 0;
    }

    HWND hwnd = CreateWindowEx
    (
        0,
        WClassName,
        L"Bomberman Explosion",
        WS_OVERLAPPEDWINDOW,
        500, 115, 960, 720,
        NULL, NULL, hInstance, NULL
    );

    if(hwnd == NULL)
    {
        MessageBox(NULL, L"Window Creation Failed", L"Error", MB_ICONERROR | MB_OK);
        return 0;
    }
    
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    Thread = CreateThread(NULL, 0, MainThread, &hwnd, 0, &ThreadID);

    while(GetMessage(&Msg, NULL, 0, 0))
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }

    return 0;
}
