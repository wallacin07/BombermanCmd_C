/* Compile:
gcc main.c -o Ternaria.exe -l gdi32 -l msimg32
*/

#include "imports.h"
#include "render.c"

DWORD ThreadID;
HANDLE Thread;

struct ImportantStuff
{
    LList Map;
} GameData;

//Função da thread principal
DWORD WINAPI MainThread(LPVOID lpParam)
{
    HWND hwnd = *((HWND *)lpParam);

    int gameover = 0;
    character player;
    player.xPos = 10;
    player.yPos = 10;
    player.xSubPos = 0;
    player.ySubPos = 0;
    player.life = 10;
    player.damage = 1;
    player.img = NULL;

    zombie zombie;
    zombie.life = 12;
    zombie.damage = 2;
    zombie.img = NULL;

    LListCreate(&GameData.Map);

    readArchive(&GameData.Map);
    DrawMap(&GameData.Map, hwnd);
    /*
    while (gameover == 0)
    {

    }
    */
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    switch(Msg)
    {
        case WM_PAINT:
        {
            PAINTSTRUCT PS;
            HDC hdc = BeginPaint(hwnd, &PS);
            DrawImg(hdc, 0, 0, 960, 720, L"imagens/BackGround2.bmp");
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