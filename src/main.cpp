#include <raylib.h>

int main() 
{
    int windowWidth = 750;
    int windowHeight = 700;
    Color gray = {29, 29, 29, 255};

    InitWindow(windowWidth, windowHeight, "Space Invaders Project");
    
    SetTargetFPS(60);

    while(WindowShouldClose() == false)
    {
        BeginDrawing();
        ClearBackground(gray);
        EndDrawing();
    }

    CloseWindow();
}