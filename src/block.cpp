#include "block.hpp"

Block::Block(Vector2 position)
{
    this -> position = position;
}

void Block::Draw()
{
    // Create 3x3 blocks
    DrawRectangle(position.x, position.y, 3, 3, {243,216,63,255});
}