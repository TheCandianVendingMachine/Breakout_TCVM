// block.hpp
// a hittable block entity
#pragma once

#include "entity.hpp"

class block : public entity
    {
        public:
            block();

            void update(sf::Time deltaTime);
            bool collide(sf::FloatRect other);

    };