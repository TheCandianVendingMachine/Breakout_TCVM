// moveableEntity.hpp
// an entity with an impulse
#pragma once

#include "entity.hpp"

class moveableEntity : public entity
    {
        protected:
            sf::Vector2f _impulse;

        public:
            void move(sf::Vector2f impulse);

            virtual ~moveableEntity();

    };