#pragma once
#include <raylib.h>

class Lazer
{
    public:
        Lazer(Vector2 position, int speed);
        void Update();
        void Draw();
        Rectangle Hitbox();
        bool active;
    private:
        Vector2 position;
        int speed;
};