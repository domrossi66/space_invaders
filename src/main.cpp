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

    Font font = LoadFontEx("Font/mongram.ttf", 64, 0, 0);   // Font, pixel size, code point, code point count
    Texture2D spaceshipImage = LoadTexture("Graphics/spaceship.png");
    
    SetTargetFPS(60);

    Game game;

    while(WindowShouldClose() == false)
    {
        game.HandleInput();
        game.Update();
        BeginDrawing();
        ClearBackground(background);  // Make the background our desired color
        DrawRectangleRoundedLinesEx({10, 10, 780, 780}, 0.18f, 20, 2, interface);  // {border}, roundness, smoothness, thickness, color
        DrawLineEx({25, 730}, {775, 730}, 3, interface);    // {point 1}, {point 2}, thickness, color

        // Level or game over text bottom right
        if(game.run)
        {
            DrawTextEx(font, "LEVEL 01", {570, 740}, 34, 2, interface); // Font, text, {position}, size, spacing, color
        }
        else
        {
            DrawTextEx(font, "GAME OVER", {570, 740}, 34, 2, interface);
        }

        // Display the lives as 3 spaceship icons bottom left
        float x = 50.0;
        for(int i = 0; i < game.lives; i++)
        {
            DrawTextureV(spaceshipImage, {x, 745}, WHITE);
            x += 50;
        }

        game.Draw();
        EndDrawing();
    }

    CloseWindow();
}