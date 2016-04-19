#include "player.hpp"
#include "../game/globals.hpp"
#include "../entity/powerup.hpp"
#include <SFML/Graphics.hpp>

player::player(sf::Vector2u windowSize, sf::Vector2f startPos) : _speed(250.f)
    {
		_windowSize = windowSize;
        _startPos = startPos;

        _entID = PLAYER;

		_lives = 3;

		_sprite.setTexture(*globals::_textureManager.get("playerTexture", true));
		_defaultSize = sf::Vector2f(_sprite.getGlobalBounds().width, _sprite.getGlobalBounds().height);
    }

void player::initialize()
    {
        _currentPower = nullptr;
        _sprite.setPosition(_startPos - sf::Vector2f(_sprite.getLocalBounds().width / 2, _sprite.getLocalBounds().height / 2));
        _impulse = sf::Vector2f(0, 0);

		globals::_keyboardManager.changeFunction("playerMovementLeftActive", [this]() { _impulse.x = -_speed; });
		globals::_keyboardManager.changeFunction("playerMovementLeftDeActive", [this]() { _impulse.x = 0; });

		globals::_keyboardManager.changeFunction("playerMovementRightActive", [this]() { _impulse.x = _speed; });
		globals::_keyboardManager.changeFunction("playerMovementRightDeActive", [this]() { _impulse.x = 0; });

		globals::_eventManager.subscribe(this, POWERUP_GAINED);
    }

void player::update(sf::Time deltaTime)
    {
        _sprite.move(_impulse * deltaTime.asSeconds());

        /* make sure the paddle can't leave the window */
        if (_sprite.getPosition().x + (_sprite.getGlobalBounds().width) > _windowSize.x)
            {
                _sprite.setPosition(_windowSize.x - _sprite.getGlobalBounds().width, _sprite.getPosition().y);
            }
        else if (_sprite.getPosition().x < 0)
            {
                _sprite.setPosition(0, _sprite.getPosition().y);
            }

        if (_currentPower)
            {
                if (_currentPower->countdownDone())
                    {
                        _currentPower = nullptr;
                    }
            }
        else if (_sprite.getGlobalBounds().width != _defaultSize.x)
            {
                _sprite.scale(_defaultSize.x / _sprite.getGlobalBounds().width, 1);
            }
    }

void player::alert(eventData data)
    {
        switch (data._data.powerDat->getType())
            {
                case powerup::WIDE_PADDLE:
                    {
                        float spriteSize = _sprite.getLocalBounds().width;
                        _sprite.scale((spriteSize + 50) / spriteSize, 1);
                        _currentPower = data._data.powerDat;
                    }
                    break;
                case powerup::SHORT_PADDLE:
                    {
                        float spriteSize = _sprite.getLocalBounds().width;
                        _sprite.scale((spriteSize - 50) / spriteSize, 1);
                        _currentPower = data._data.powerDat;
                    }
                    break;
                case powerup::EXTRA_LIFE:
                    _lives++;
                    globals::_eventManager.alert(eventData(_lives, LOSE_LIFE));
                    break;
                default:
                    _currentPower = nullptr;
                    break;
            }
    }

void player::decreaseLives()
	{
		_lives--;
        globals::_eventManager.alert(eventData(_lives, LOSE_LIFE));
	}

const int player::getLives() const
    {
        return _lives;
    }

bool player::playerDead() const
	{
		return _lives < 0;
	}

player::~player()
    {
        globals::_eventManager.unsubscribe(this, POWERUP_GAINED);
    }
