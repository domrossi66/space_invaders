#pragma once
#include <vector>
#include "block.hpp"

class Shield
{
    public:
        Shield(Vector2 position);
        void Draw();
        Vector2 position;
        std::vector<Block> blocks;  // All the blocks the obstacle is made of
        static std::vector<std::vector<int>> grid; // Grid made of 3x3 blocks
    private:
};