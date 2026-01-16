#include <raylib.h>
#include "game.hpp"

int main() 
{
    int offset = 50;    // 50 pixel offset so we have room for user interface
    int windowWidth = 750;
    int windowHeight = 700;
    Color background = {29, 29, 29, 255}; //Red, blue, green, opacity (this is gray rn)
    Color interface = {243, 216, 63, 255};   //This is yellow rn

    InitWindow(windowWidth + offset, windowHeight + 2 * offset, "Space Invaders Project");
    
    SetTargetFPS(60);

    Game game;

    while(WindowShouldClose() == false)
    {
        game.HandleInput();
        game.Update();
        BeginDrawing();
        ClearBackground(background);  // Make the background our desired color
        DrawRectangleRoundedLinesEx({10, 10, 780, 780}, 0.18f, 20, 2, YELLOW);  // {border}, roundness, smoothness, thickness, color
        game.Draw();
        EndDrawing();
    }

    CloseWindow();
}