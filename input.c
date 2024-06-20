#include "imports.h"

void MoveLeft(character * Player, int Pixels)
{
    Player->xSubPos -= Pixels;
    if(Player->xSubPos < -16)
    {
        Player->xPos += (Player->xSubPos - 16)/32;
    }
}

void input(character * Player)
{
    if(GetAsyncKeyState(VK_W))
    {
    }
}