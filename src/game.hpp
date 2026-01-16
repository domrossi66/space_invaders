#pragma once
#include "spaceship.hpp"
#include "shield.hpp"
#include "alien.hpp"
#include "alienship.hpp"

class Game
{
    public:
        Game();
        ~Game();
        void Draw();
        void Update();
        void HandleInput();
        bool run;
        int lives;
        int score;
        int highscore;
    private:
        Spaceship spaceship;
        void DeleteInactiveLazers();
        std::vector<Shield> CreateShields();
        std::vector<Alien> CreateAliens();
        void MoveAliens();
        void MoveDown(int distance);
        void AlienShoot();
        void CheckCollision();
        void GameOver();
        void Reset();
        void InitGame();
        void CheckHighScore();
        void SaveHighScore(int highscore);
        int GetHighScore();
        std::vector<Shield> shields;
        std::vector<Alien> aliens;
        int aliensDirection;
        std::vector<Lazer> alienLazers;
        constexpr static float alienLazerInterval = 0.45;   // Alien lazers fire every 450 ms 
        float lastAlienFire;
        AlienShip alienship;
        float alienShipSpawnInterval;
        float lastSpawn;
};