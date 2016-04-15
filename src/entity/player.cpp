#include "player.hpp"
#include "../game/globals.hpp"
#include <SFML/Graphics.hpp>

player::player(sf::Vector2u windowSize, sf::Vector2f startPos) : _speed(200)
    {
		_windowSize = windowSize;
        _startPos = startPos;

        _sprite.setTexture(*globals::_textureManager.get("playerTexture", true));

        globals::_keyboardManager.changeFunction("playerMovementLeftActive", [this] () { _impulse.x = -_speed; });
        globals::_keyboardManager.changeFunction("playerMovementLeftDeActive", [this] () { _impulse.x = 0; });

        globals::_keyboardManager.changeFunction("playerMovementRightActive", [this] () { _impulse.x = _speed; });
        globals::_keyboardManager.changeFunction("playerMovementRightDeActive", [this] () { _impulse.x = 0; });

		_lives = 3;

        initialize();
    }

void player::initialize()
    {
        _sprite.setPosition(_startPos - sf::Vector2f(_sprite.getLocalBounds().width / 2, _sprite.getLocalBounds().height / 2));
        _impulse = sf::Vector2f(0, 0);
    }

void player::update(sf::Time deltaTime)
    {
        if (_sprite.getPosition().x + _sprite.getLocalBounds().width > _windowSize.x)
            {
                _sprite.setPosition(_sprite.getPosition().x, _windowSize.x - _sprite.getLocalBounds().height);
            }
        else if (_sprite.getPosition().y < 0)
            {
                _sprite.setPosition(_sprite.getPosition().x, 0);
            }

        _sprite.move(_impulse * deltaTime.asSeconds());

        /* make sure the paddle can't leave the window */
        if (_sprite.getPosition().x + (_sprite.getLocalBounds().width) > _windowSize.x)
            {
                _sprite.setPosition(_windowSize.x - _sprite.getLocalBounds().width, _sprite.getPosition().y);
            }
        else if (_sprite.getPosition().x < 0)
            {
                _sprite.setPosition(0, _sprite.getPosition().y);
            }
    }

void player::decreaseLives()
	{
		_lives--;
	}

bool player::playerDead() const
	{
		return _lives <= 0;
	}
