#include "block.hpp"
#include "../game/globals.hpp"

block::block()
    {
        _sprite.setTexture(*globals::_textureManager.get("blockTexture"));
    }

void block::update(sf::Time deltaTime)
    {}

bool block::collide(entity &other)
    {
        return false;
    }
