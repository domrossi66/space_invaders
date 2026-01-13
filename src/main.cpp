#include <raylib.h>
#include "game.hpp"

int main() 
{
    int windowWidth = 750;
    int windowHeight = 700;
    Color background = {29, 29, 29, 255}; //Red, blue, green, opacity (this is gray rn)

    InitWindow(windowWidth, windowHeight, "Space Invaders Project");
    
    SetTargetFPS(60);

    Game game;

    while(WindowShouldClose() == false)
    {
        game.HandleInput();
        game.Update();
        BeginDrawing();
        ClearBackground(background);  // Make the background our desired color
        game.Draw();
        EndDrawing();
    }

    CloseWindow();
}