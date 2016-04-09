#include "entity.hpp"
#include <SFML/Graphics.hpp>

void entity::draw(sf::RenderTarget &target)
    {
        target.draw(_sprite);
    }

void entity::move(sf::Vector2f impulse)
    {
        _impulse = impulse;
    }

void entity::setPosition(sf::Vector2f pos)
    {
        _sprite.setPosition(pos);
    }

void entity::setPosition(float X, float Y)
    {
        _sprite.setPosition(X, Y);
    }

sf::Vector2f entity::getPosition()
    {
        return _sprite.getPosition();
    }

sf::Vector2f entity::getImpulse() const
    {
        return _impulse;
    }

sf::Sprite *entity::getSprite()
    {
        return &_sprite;
    }

entity::~entity()
    {}
