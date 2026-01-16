#include "game.hpp"
#include <iostream>

Game::Game()
{
    InitGame();
}

Game::~Game()
{
    Alien::UnloadImages();

}

void Game::Update()
{
    if(run)
    {
        double currentTime = GetTime();
    if(currentTime - lastSpawn > alienShipSpawnInterval)
    {
        alienship.Spawn();
        lastSpawn = GetTime();
        alienShipSpawnInterval = GetRandomValue(10,20);
    }

    for(auto& lazer: spaceship.lazers)
    {
        lazer.Update();
    }

    MoveAliens();
    AlienShoot();
    for(auto& lazer: alienLazers)
    {
        lazer.Update();
    }
    DeleteInactiveLazers();
    alienship.Update();
    CheckCollision();
    }
    else
    {
        if(IsKeyDown(KEY_ENTER))
        {
            Reset();
            InitGame();
        }
    }
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

    for(auto& alien: aliens)
    {
        alien.Draw();
    }

    for(auto& lazer: alienLazers)
    {
        lazer.Draw();
    }

    alienship.Draw();
}

// Makes key presses corespond to spaceship actions
void Game::HandleInput()
{
    if(run)
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

    // Loop through vector to find inactive alien lazers
    for(auto i = alienLazers.begin(); i != alienLazers.end();)
    {
        if(!i -> active)    // Removes lazer if it is inactive
        {
            i = alienLazers.erase(i);
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

std::vector<Alien> Game::CreateAliens()
{
    std::vector<Alien> aliens;
    for(int row = 0; row < 5; row++)
    {
        for(int col = 0; col < 11; col ++)
        {
            int alienType;
            if(row == 0)
            {
                alienType = 3;
            }
            else if(row == 1 || row == 2)
            {
                alienType = 2;
            }
            else
            {
                alienType = 1;
            }

            float x = 75 + col * 55; // Cell size for each alien is 55 x 55 pixels
            float y = 110 + row * 55; // There are additional offsets added so aliens start centered
            aliens.push_back(Alien(alienType, {x, y}));
        }
    }

    return aliens;
}

void Game::MoveAliens()
{
    for(auto& alien: aliens)
    {
        if(alien.position.x + alien.alienImages[alien.type - 1].width > GetScreenWidth())   // Move aliens left if they hit right side of screen
        {
            aliensDirection = -1;
            MoveDown(4);
        }
        if(alien.position.x < 0)    // Move aliens right if they hit left of screen
        {
            aliensDirection = 1;
            MoveDown(4);
        }
        alien.Update(aliensDirection);
    }
}

void Game::MoveDown(int distance)
{
    for(auto& alien: aliens)
    {
        alien.position.y += distance;
    }
}

void Game::AlienShoot()
{
    double currentTime = GetTime();
    if(currentTime - lastAlienFire >= alienLazerInterval && !aliens.empty())
    {
        int randomAlien = GetRandomValue(0, aliens.size()-1);
        Alien& alien = aliens[randomAlien];

        // Args for lazer are position and speed. This should be center of alien's x-axis and bottom of their y-axis
        // The same calculations are used from the spaceship lazers which make this so confusing to look at
        alienLazers.push_back(Lazer({alien.position.x + alien.alienImages[alien.type-1].width/2, 
        alien.position.y + alien.alienImages[alien.type-1].height/2}, 7));

        lastAlienFire = GetTime();
    }
}

void Game::CheckCollision()
{
    // ---- User Lazer Collisions----

    // Lazers hitting aliens
    for(auto& lazer: spaceship.lazers)
    {
        // Traverse through the aliens
        auto i = aliens.begin();
        while(i != aliens.end())
        {
            if(CheckCollisionRecs(i -> Hitbox(), lazer.Hitbox()))   // Check if the lazer hitbox collied with alien hitbox
            {
                i = aliens.erase(i);    // Kill alien if true
                lazer.active = false;   // Stop lazer if true
            }
            else
            {
                ++i;    // Check next alien if there was no collision
            }
        }

        // Lazers hitting shields 
        for(auto& shield: shields)
        {
            auto i = shield.blocks.begin();
            while(i != shield.blocks.end())
            {
                if(CheckCollisionRecs(i -> Hitbox(), lazer.Hitbox()))
                {
                    i = shield.blocks.erase(i);
                    lazer.active = false;
                }
                else
                {
                    ++i;
                }
            }
        }

        // Lazers hitting alien ship
        if(CheckCollisionRecs(alienship.Hitbox(), lazer.Hitbox()))
        {
            alienship.visible = false;
            lazer.active = false;

        }
    }

    // ---- Alien Collisons ----

    // Alien lazers hitting spaceship
    for(auto& lazer: alienLazers)
    {
        if(CheckCollisionRecs(lazer.Hitbox(), spaceship.Hitbox()))
        {
            lazer.active = false;
            lives --;
            if(lives == 0)
            {
                GameOver();
            }
        }

        // Alien lazers hitting shields 
        for(auto& shield: shields)
        {
            auto i = shield.blocks.begin();
            while(i != shield.blocks.end())
            {
                if(CheckCollisionRecs(i -> Hitbox(), lazer.Hitbox()))
                {
                    i = shield.blocks.erase(i);
                    lazer.active = false;
                }
                else
                {
                    ++i;
                }
            }
        }
    }

    // Alien hitting shields
    for(auto& alien: aliens)
    {
        for(auto& shield: shields)
        {
            auto i = shield.blocks.begin();
            while(i != shield.blocks.end())
            {
                if(CheckCollisionRecs(i -> Hitbox(), alien.Hitbox()))
                {
                    i = shield.blocks.erase(i);
                }
                else
                {
                    i++;
                }
            }
        }

        // Alien hitting spaceship
        if(CheckCollisionRecs(alien.Hitbox(), spaceship.Hitbox()))
        {
            GameOver();
        }
    }
}

void Game::GameOver()
{
    run = false;
}

// Reset to inital positions/lives after game over
void Game::InitGame()
{
    shields = CreateShields();
    aliens = CreateAliens();
    aliensDirection = 1;
    lastAlienFire = 0;
    lastSpawn = 0.0;
    alienShipSpawnInterval = GetRandomValue(10,20);
    lives = 3;
    run = true;
}

void Game::Reset()
{
    spaceship.Reset();
    aliens.clear();
    alienLazers.clear();
    shields.clear();
}