#pragma once    // Ensures one time compliation to avoid dupliacte definitions
#include <raylib.h>
#include <vector>
#include "lazer.hpp"
class Spaceship
{
    public:
        Spaceship();
        ~Spaceship();
        void Draw();
        void MoveLeft();
        void MoveRight();
        void Shoot();
        std::vector<Lazer> lazers;
    private:
        Texture2D image;
        Vector2 position;
        double lastFire;
};