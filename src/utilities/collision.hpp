// collision.hpp
// collision checkers. Does not handle collision, only detects it
#pragma once

#include <SFML/System/Vector2.hpp>

class entity;

namespace clsn
    {
        bool hasCollided(entity *firstSprite, entity *secondSprite);
        sf::Vector2f getOverlap(entity *firstSprite, entity *secondSprite);
    }