#include "game.hpp"
#include <iostream>

Game::Game()
{

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
    std::cout << "Vector size: " << spaceship.lazers.size() << std::endl;   // Test above method works
}

void Game::Draw()
{
    spaceship.Draw();

    for(auto& lazer: spaceship.lazers)
    {
        lazer.Draw();
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
