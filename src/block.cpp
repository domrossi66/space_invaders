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

Rectangle Block::Hitbox()
{
    Rectangle hitbox;
    hitbox.x = position.x;
    hitbox.y = position.y;
    hitbox.width = 3;
    hitbox.height = 3;
    return hitbox;
}
