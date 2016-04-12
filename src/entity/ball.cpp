#include "ball.hpp"
#include "../game/globals.hpp"

ball::ball(sf::Vector2u windowSize) : _speed(400.f)
    {
        _sprite.setTexture(*globals::_textureManager.get("ballTexture"));
        _sprite.setOrigin(_sprite.getLocalBounds().width / 2, _sprite.getLocalBounds().height / 2);

        _windowSize = windowSize;

        initialize(sf::Vector2f(0, _speed));
    }

void ball::initialize(sf::Vector2f impulse)
    {
        _impulse = impulse;
    }

void ball::update(sf::Time deltaTime)
    {
        _sprite.move(_impulse * deltaTime.asSeconds());

        auto spritePos = _sprite.getPosition();
        auto spriteBound = _sprite.getLocalBounds();
        // If the ball is hitting the edge of the window, bounce off
        if (spritePos.x + (spriteBound.width / 2) >= _windowSize.x, spritePos.x - (spriteBound.width / 2) <= 0)
            {
                _impulse.x = -_impulse.x;
            }

        if (spritePos.y - (spriteBound.height / 2) <= 0)
            {
                _impulse.y = -_impulse.y;
            }
    }

bool ball::collide(entity &otherSprite)
    {
        auto other = *otherSprite.getSprite();

        sf::Vector2f centerFirst(_sprite.getPosition().x + (_sprite.getLocalBounds().width / 2),
                                 _sprite.getPosition().y + (_sprite.getLocalBounds().height / 2));

        sf::Vector2f centerSecond(other.getPosition().x + (other.getLocalBounds().width / 2),
                                  other.getPosition().y + (other.getLocalBounds().height / 2));


        sf::Vector2f distance(centerFirst - centerSecond);
        sf::Vector2f minDistance((_sprite.getLocalBounds().width / 2) + (other.getLocalBounds().width / 2),
                                 (_sprite.getLocalBounds().height / 2) + (other.getLocalBounds().height / 2));

        // if ball collides with a sprite, bounce off
        if (abs(distance.x) < minDistance.x && abs(distance.y) < minDistance.y)
            {
                sf::Vector2f overlap(distance.x > 0 ? minDistance.x - distance.x : -minDistance.x - distance.x,
                                     distance.y > 0 ? minDistance.y - distance.y : -minDistance.y - distance.y);

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

                if (otherSprite.getID() == BLOCK)
                    {
                        globals::_eventManager.alert(eventData(0, BALL_HIT_BLOCK));
                    }

                return true;
            }

        return false;
    }
