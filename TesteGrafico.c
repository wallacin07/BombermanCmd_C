#ifndef UNICODE
#define UNICODE
#endif
//gcc testegrafico.c -o testegrafico.exe -l gdi32
#include <windows.h>

// Prototipo da função de procedimento da janela
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// Função principal
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    const wchar_t CLASS_NAME[] = L"Sample Window Class";

    WNDCLASS wc = { };

    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,                              // Estilo de janela estendido
        CLASS_NAME,                     // Nome da classe da janela
        L"Janela com Imagem de Fundo",  // Título da janela
        WS_OVERLAPPEDWINDOW,            // Estilo da janela
        CW_USEDEFAULT, CW_USEDEFAULT,   // Posição inicial da janela
        800, 600,                       // Largura e altura da janela
        NULL,                           // Handle da janela pai
        NULL,                           // Handle do menu
        hInstance,                      // Handle da instância do programa
        NULL                            // Parâmetros adicionais
    );

    if (hwnd == NULL)
    {
        MessageBox(NULL, L"Falha ao criar a janela!", L"Erro", MB_ICONERROR | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

// Função de procedimento da janela
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static HBITMAP hBitmap = NULL;

    switch (uMsg)
    {
        case WM_CREATE:
        {
            // Carrega a imagem BMP
            hBitmap = (HBITMAP)LoadImage(NULL, L"background.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
            if (hBitmap == NULL)
            {
                MessageBox(hwnd, L"Falha ao carregar a imagem de fundo!", L"Erro", MB_ICONERROR | MB_OK);
            }
        }
        break;

        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            if (hBitmap)
            {
                HDC hdcMem = CreateCompatibleDC(hdc);
                HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, hBitmap);

                BITMAP bitmap;
                GetObject(hBitmap, sizeof(bitmap), &bitmap);
                BitBlt(hdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hdcMem, 0, 0, SRCCOPY);

                SelectObject(hdcMem, hbmOld);
                DeleteDC(hdcMem);
            }

            EndPaint(hwnd, &ps);
        }
        break;

        case WM_DESTROY:
            DeleteObject(hBitmap);
            PostQuitMessage(0);
            return 0;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}