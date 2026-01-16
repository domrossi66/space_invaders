#include "spaceship.hpp"

Spaceship::Spaceship()
{
    // Make ship start in bottom center
    image = LoadTexture("Graphics/spaceship.png");
    position.x = (GetScreenWidth() - image.width)/2;
    position.y = GetScreenHeight() - image.height;

    lastFire = 0.0;
}

Spaceship::~Spaceship()
{
    UnloadTexture(image);
}

void Spaceship::Draw()
{
    DrawTextureV(image, position, WHITE);
}

void Spaceship::MoveLeft()
{
    position.x -= 7;
    if(position.x < 0)  // Ensure ship does not move offscreen
    {
        position.x = 0;
    }
}

void Spaceship::MoveRight()
{
    position.x += 7;
    if(position.x > GetScreenWidth() - image.width) // Ensure ship does not move offscreen
    {
        position.x = GetScreenWidth() - image.width;
    }
}

void Spaceship::Shoot()
{
    if(GetTime() - lastFire >= 0.35)    // Cool down of 350 ms between shots
    {
        lazers.push_back(Lazer({position.x + image.width/2 - 2, position.y}, -5));  // Make it shoot from center
        lastFire = GetTime();
    }
}

Rectangle Spaceship::Hitbox()
{
    return {position.x, position.y, float(image.width), float(image.height)};
}
