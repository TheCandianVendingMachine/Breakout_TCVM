#include "powerup.hpp"

#include "../utilities/collision.hpp"
#include "../utilities/randomizer.hpp"

#include "../game/globals.hpp"

powerup::powerup(sf::Vector2f position) : _speed(150.f)
    {
        _sprite.setPosition(position);

        _impulse.y = _speed;

        _alive = true;

        _type = static_cast<powerUpTypes>(rndm::random(WIDE_PADDLE, EXTRA_LIFE));

        switch (_type)
            {
                case powerup::WIDE_PADDLE:
                    _sprite.setTexture(*globals::_textureManager.get("powerupLargePaddle", true));
                    break;
                case powerup::SHORT_PADDLE:
                    _sprite.setTexture(*globals::_textureManager.get("powerupSmallPaddle", true));
                    break;
                case powerup::EXTRA_LIFE:
                    _sprite.setTexture(*globals::_textureManager.get("powerupHealth", true));
                    break;
                default:
                    break;
            }
    }

void powerup::setAlive(bool value)
    {
        _alive = value;
    }

void powerup::draw(sf::RenderWindow &app)
    {
        if (_alive)
            {
                app.draw(_sprite);
            }
    }

void powerup::update(sf::Time deltaTime)
    {
        if (_alive)
            {
                _sprite.move(_impulse * deltaTime.asSeconds());
            }
    }

bool powerup::collide(entity *otherSprite)
    {
        if (_alive)
            {
                if (otherSprite->getEntityID() == PLAYER && clsn::hasCollided(this, otherSprite))
                    {
                        globals::_eventManager.alert(eventData(this, POWERUP_GAINED));
                        _powerupCountdown.start(sf::seconds(15));
                        return true;
                    }
            }
        return false;
    }

powerup::powerUpTypes powerup::getType() const
    {
        return _type;
    }

const bool powerup::countdownDone()
    {
        return _powerupCountdown.hasCountdownFinished();
    }

powerup::~powerup()
    {}
