#pragma once
#include <raylib.h>

class Alien
{
    public:
        Alien(int type, Vector2 position);
        void Draw();
        void Update(int direction);
        int GetType();
        static Texture2D alienImages[3];    // Load each alien image once and apply instead of 55 aliens with set images
        static void UnloadImages();
        int type;
        Vector2 position;
    private:
};