#include <raylib.h>
#include "game.hpp"
#include <string>

#ifdef PLATFORM_WEB
    #include <emscripten/emscripten.h>
#endif

Game* game = nullptr;
Font font;
Texture2D spaceshipImage;
Color background = {29, 29, 29, 255}; //Red, blue, green, opacity (this is gray rn)
Color interface = {243, 216, 63, 255};   //This is yellow rn


std::string FormatScore(int number, int digits)
{
    std::string score = std::to_string(number); // Score becomes string for updating
    int leadingZeros = digits - score.length(); // Determine how many leading zeros keep score at 5 digits
    return score = std::string(leadingZeros, '0') + score; // Display the score
}

void UpdateDrawFrame()
{
    UpdateMusicStream(game->music);
        game->HandleInput();
        game->Update();
        BeginDrawing();
        ClearBackground(background);  // Make the background our desired color
        DrawRectangleRoundedLinesEx({10, 10, 780, 780}, 0.18f, 20, 2, interface);  // {border}, roundness, smoothness, thickness, color
        DrawLineEx({25, 730}, {775, 730}, 3, interface);    // {point 1}, {point 2}, thickness, color

        // Level or game over text bottom right
        if(game->run)
        {
            DrawTextEx(font, "LEVEL 01", {570, 740}, 34, 2, interface); // Font, text, {position}, size, spacing, color
        }
        else
        {
            DrawTextEx(font, "GAME OVER", {570, 740}, 34, 2, interface);
        }

        // Display the lives as 3 spaceship icons bottom left
        float x = 50.0;
        for(int i = 0; i < game->lives; i++)
        {
            DrawTextureV(spaceshipImage, {x, 745}, WHITE);
            x += 50;
        }

        // Displaying score
        DrawTextEx(font, "SCORE", {55, 15}, 34, 2, interface);
        std::string scoreText = FormatScore(game->score, 5);
        DrawTextEx(font, scoreText.c_str(), {55,45}, 34, 2, interface);

        // Displaying highscore
        DrawTextEx(font, "HIGHSCORE", {555, 15}, 34, 2, interface);
        std::string highscoreText = FormatScore(game->highscore, 5);
        DrawTextEx(font, highscoreText.c_str(), {555, 45}, 34, 2, interface);

        game->Draw();
        EndDrawing();
}

int main() 
{
    int offset = 50;    // 50 pixel offset so we have room for user interface
    int windowWidth = 750;
    int windowHeight = 700;

    InitWindow(windowWidth + offset, windowHeight + 2 * offset, "Space Invaders Project");
    //InitAudioDevice();

    font = LoadFontEx("Font/mongram.ttf", 64, 0, 0);   // Font, pixel size, code point, code point count
    spaceshipImage = LoadTexture("Graphics/spaceship.png");
    
    SetTargetFPS(60);

    game = new Game();

#ifdef PLATFORM_WEB
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
    while(WindowShouldClose() == false)
    {
        UpdateDrawFrame();
    }
#endif

    delete game;
    //CloseAudioDevice();
    CloseWindow();
}