#include "ball.hpp"
#include "../game/globals.hpp"
#include "../utilities/collision.hpp"

ball::ball(sf::Vector2u windowSize) : _speed(300.f)
    {
        _sprite.setTexture(*globals::_textureManager.get("ballTexture", true));
        _sprite.setOrigin(_sprite.getLocalBounds().width / 2, _sprite.getLocalBounds().height / 2);

        _windowSize = windowSize;

        initialize(sf::Vector2f(0, _speed));
    }

void ball::initialize(sf::Vector2f impulse)
    {
        _impulse = impulse;
		setPosition(_windowSize.x / 2.f, _windowSize.y - 200.f);
    }

void ball::update(sf::Time deltaTime)
    {
        _sprite.move(_impulse * deltaTime.asSeconds());

        auto spritePos = _sprite.getPosition();
        auto spriteBound = _sprite.getLocalBounds();
        // If the ball is hitting the edge of the window, bounce off
        if (spritePos.x + (spriteBound.width / 2) >= _windowSize.x || spritePos.x - (spriteBound.width / 2) <= 0)
            {
                _impulse.x = -_impulse.x;
                if (spritePos.x < (_windowSize.x / 2))
                    {
                        _sprite.setPosition((spriteBound.width / 2), _sprite.getPosition().y);
                    }
                else
                    {
                        _sprite.setPosition(_windowSize.x - (spriteBound.width / 2), _sprite.getPosition().y);
                    }
            }

        if (spritePos.y - (spriteBound.height / 2) <= 0)
            {
                _impulse.y = -_impulse.y;
                _sprite.setPosition(_sprite.getPosition().x, (spriteBound.height / 2));
            }
    }

bool ball::collide(entity *otherSprite)
    {
        if (clsn::hasCollided(this, otherSprite))
            {
                auto firstObjBound = _sprite.getGlobalBounds();
                auto secondObjBound = otherSprite->getSprite()->getGlobalBounds();

                sf::Vector2f centerFirst(firstObjBound.left + (firstObjBound.width / 2),
                                         firstObjBound.top + (firstObjBound.height / 2));

                sf::Vector2f centerSecond(secondObjBound.left + (secondObjBound.width / 2),
                                          secondObjBound.top + (secondObjBound.height / 2));

                sf::Vector2f overlap = clsn::getOverlap(this, otherSprite);

                // find the new angle of bounce using trig
                float angle = std::atan2(centerSecond.y - centerFirst.y, centerSecond.x - centerFirst.x);
                // and get new velocity
                _impulse = sf::Vector2f(std::cos(angle), std::sin(angle)) * -_speed;

                // move the ball out of the paddle to avoid the ball getting stuck in the paddle
                if (abs(overlap.x) > abs(overlap.y))
                    {
                        // Y is shallow axis
                        _sprite.setPosition(_sprite.getPosition().x, _sprite.getPosition().y + overlap.y);
                    }
                else
                    {
                        // X is shallow axis
                        _sprite.setPosition(_sprite.getPosition().x + overlap.x, _sprite.getPosition().y);
                    }

                if (otherSprite->getEntityID() == BLOCK)
                    {
                        globals::_eventManager.alert(eventData(static_cast<int>(otherSprite->getID()), BALL_HIT_BLOCK));
                    }

                return true;
            }

        return false;
    }
