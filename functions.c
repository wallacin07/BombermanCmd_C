#include "imports.h"

void DrawImg(HDC hdc, int PosX, int PosY, int Width, int Height, const wchar_t * ImgPath)
{
    BITMAP bm;
    HBITMAP Image = (HBITMAP)LoadImage(NULL, ImgPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    HDC BitmapDC = CreateCompatibleDC(hdc);
    SelectObject(BitmapDC, Image);
    GetObject((HGDIOBJ)Image, sizeof(bm), &bm);
    TransparentBlt(hdc, PosX, PosY, bm.bmWidth, bm.bmHeight, BitmapDC, 0, 0, Width, Height, RGB(255, 0, 255));
    DeleteDC(BitmapDC);
    DeleteObject(Image);
}

void DrawRect(HDC hdc, int PosX, int PosY, int Width, int Height, COLORREF Color)
{
    SelectObject(hdc, GetStockObject(DC_BRUSH));
    SetDCBrushColor(hdc, Color);
    Rectangle(hdc, PosX, PosY, PosX + Width, PosY + Height);
}