#include "spaceship.hpp"

Spaceship::Spaceship()
{
    // Make ship start in bottom center
    image = LoadTexture("Graphics/spaceship.png");
    position.x = (GetScreenWidth() - image.width)/2;
    position.y = GetScreenHeight() - image.height - 100;
    //pewpew = LoadSound("Sounds/lazer.ogg");

    lastFire = 0.0;
}

Spaceship::~Spaceship()
{
    UnloadTexture(image);
    //UnloadSound(pewpew);
}

void Spaceship::Draw()
{
    DrawTextureV(image, position, WHITE);
}

void Spaceship::MoveLeft()
{
    position.x -= 7;
    if(position.x < 25)  // Ensure ship does not move offscreen
    {
        position.x = 25;
    }
}

void Spaceship::MoveRight()
{
    position.x += 7;
    if(position.x > GetScreenWidth() - image.width - 25) // Ensure ship does not move offscreen
    {
        position.x = GetScreenWidth() - image.width - 25;
    }
}

void Spaceship::Shoot()
{
    if(GetTime() - lastFire >= 0.35)    // Cool down of 350 ms between shots
    {
        lazers.push_back(Lazer({position.x + image.width/2 - 2, position.y}, -5));  // Make it shoot from center
        lastFire = GetTime();
        PlaySound(pewpew);
    }
}

void Spaceship::Reset()
{
    position.x = (GetScreenWidth() - image.width)/ 2.0f;
    position.y = GetScreenHeight() - image.height - 100;
    lazers.clear();
}

Rectangle Spaceship::Hitbox()
{
    return {position.x, position.y, float(image.width), float(image.height)};
}
