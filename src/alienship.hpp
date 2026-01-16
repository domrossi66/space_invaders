#pragma once
#include <raylib.h>

class AlienShip
{
    public:
        AlienShip();
        ~AlienShip();
        void Update();
        void Draw();
        void Spawn();
        bool visible;
    private:
        Vector2 position;
        Texture2D image;
        int speed;
};