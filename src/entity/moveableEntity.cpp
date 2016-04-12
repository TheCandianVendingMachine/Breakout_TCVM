#include "moveableEntity.hpp"

void moveableEntity::move(sf::Vector2f impulse)
    {
        _impulse = impulse;
    }

moveableEntity::~moveableEntity()
    {}
