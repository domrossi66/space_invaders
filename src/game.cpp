#include "game.hpp"
#include <iostream>

Game::Game()
{
    shields = CreateShields();
}

Game::~Game()
{

}

void Game::Update()
{
    for(auto& lazer: spaceship.lazers)
    {
        lazer.Update();
    }

    DeleteInactiveLazers();
}

void Game::Draw()
{
    spaceship.Draw();

    for(auto& lazer: spaceship.lazers)
    {
        lazer.Draw();
    }

    for(auto& shield: shields)
    {
        shield.Draw();
    }
}

// Makes key presses corespond to spaceship actions
void Game::HandleInput()
{
    if(IsKeyDown(KEY_LEFT))
    {
        spaceship.MoveLeft();
    }
    else if(IsKeyDown(KEY_RIGHT))
    {
        spaceship.MoveRight();
    }
    else if(IsKeyDown(KEY_SPACE))
    {
        spaceship.Shoot();
    }
}

void Game::DeleteInactiveLazers()
{
    // Loop through vector to find inactive lazers
    for(auto i = spaceship.lazers.begin(); i != spaceship.lazers.end();)
    {
        if(!i -> active)    // Removes lazer if it is inactive
        {
            i = spaceship.lazers.erase(i);
        }
        else    // Move iterator to next element when lazer is active
        {
            ++i;
        }
    }
}

std::vector<Shield> Game::CreateShields()
{
    int shieldWidth = Shield::grid[0].size() * 3;   // Total columns is number of spaces in first row
    float gap = (GetScreenWidth() - (4 * shieldWidth)) / 5; // 5 gaps in screen, each size of space left over from screen size - 4 shields
    for(int i = 0; i < 4; i++)
    {
        float offsetX = (i + 1) * gap + i * shieldWidth;    // Horizontal position with equal spacing
        shields.push_back(Shield({offsetX, float(GetScreenHeight() - 100)}));   // Draw 4 shields evenly spaced and above the ship
    }
    return shields;
}
