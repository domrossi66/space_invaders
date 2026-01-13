#pragma once
#include "spaceship.hpp"
#include "shield.hpp"

class Game
{
    public:
        Game();
        ~Game();
        void Draw();
        void Update();
        void HandleInput();
    private:
        Spaceship spaceship;
        void DeleteInactiveLazers();
        std::vector<Shield> CreateShields();
        std::vector<Shield> shields;
};