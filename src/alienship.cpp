#include "alienship.hpp"

AlienShip::AlienShip()
{
    image = LoadTexture("Graphics/alien_ship.png");
    visible = false;
}

AlienShip::~AlienShip()
{
    UnloadTexture(image);
}

void AlienShip::Spawn()
{
    position.y = 90;
    int startPosition = GetRandomValue(0,1);

    if(startPosition == 0)
    {
        position.x = 0;
        speed = 3;
    }
    else
    {
        position.x = GetScreenWidth() - image.width;
        speed = -3;
    }
    visible = true;
}

Rectangle AlienShip::Hitbox()
{
    if(visible)
    {
        return {position.x, position.y, float(image.width), float(image.height)};
    }
    else    // Make the hitbox non-existent when ship isn't on screen
    {
        return {position.x, position.y, 0, 0};
    }
}

void AlienShip::Update()
{
    if(visible)
    {
        position.x += speed;
        if(position.x > GetScreenWidth() - image.width || position.x < 0)
        {
            visible = false;
        }
    }
}

void AlienShip::Draw()
{
    if(visible)
    {
        DrawTextureV(image, position, WHITE);
    }
}