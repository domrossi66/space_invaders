#include <raylib.h>
#include "game.hpp"

int main() 
{
    int windowWidth = 750;
    int windowHeight = 700;
    Color gray = {29, 29, 29, 255}; //Red, blue, green, opacity

    InitWindow(windowWidth, windowHeight, "Space Invaders Project");
    
    SetTargetFPS(60);

    Game game;

    while(WindowShouldClose() == false)
    {
        game.HandleInput();

        BeginDrawing();
        ClearBackground(gray);  // Make the background our gray
        game.Draw();
        EndDrawing();
    }

    CloseWindow();
}