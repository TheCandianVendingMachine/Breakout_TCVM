#include "block.hpp"
#include "../game/globals.hpp"

block::block()
    {
        _sprite.setTexture(*globals::_textureManager.add("assets/textures/block.png", "blockTexture"));
    }

void block::update(sf::Time deltaTime)
    {}

bool block::collide(sf::FloatRect other)
    {
    return false;
    }
