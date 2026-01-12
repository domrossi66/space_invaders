#pragma once    // Ensures one time compliation to avoid dupliacte definitions
#include <raylib.h>

class Spaceship
{
    public:
        Spaceship();
        ~Spaceship();
        void Draw();
        void MoveLeft();
        void MoveRight();
        void Shoot();
    private:
        Texture2D image;
        Vector2 position;
};