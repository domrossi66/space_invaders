#include "lazer.hpp"
#include <iostream>

Lazer::Lazer(Vector2 position, int speed)
{
    this -> position = position;
    this -> speed = speed;
    active = true;
}

void Lazer::Draw()
{
    if(active)
    {
        DrawRectangle(position.x, position.y, 4, 15, {243, 216, 63, 255}); //  x, y, width, height, {color}
    }
}

Rectangle Lazer::Hitbox()
{
    Rectangle hitbox;
    hitbox.x = position.x;
    hitbox.y = position.y;
    hitbox.width = 4;
    hitbox.height = 15;
    return hitbox;
}

void Lazer::Update()
{
    position.y += speed;

    // Destroy lazer once offscreen to save memory
    if(active)
    {
        if(position.y > GetScreenHeight() - 100 || position.y < 25)
        {
            active = false;
        }
    }
}