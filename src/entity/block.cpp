#include "block.hpp"
#include "../game/globals.hpp"

#include <SFML/Graphics.hpp>

block::block()
    {
        _sprite.setTexture(*globals::_textureManager.get("blockTexture"));
		_entID = BLOCK;
    }

const bool block::getAlive() const
	{
		return _alive;
	}

void block::setAlive(bool alive)
	{
		_alive = alive;
	}

void block::draw(sf::RenderWindow &app)
	{
		if (_alive)
			{
				app.draw(_sprite);
			}
	}

void block::update(sf::Time deltaTime)
    {}
