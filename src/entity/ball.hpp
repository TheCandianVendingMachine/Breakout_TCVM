// ball.hpp
// the ball in the game. Collides with the paddle and blocks
#pragma once

#include "moveableEntity.hpp"

class ball : public moveableEntity
    {
        private:
            const float _speed;

            sf::Vector2u _windowSize;

        public:
            ball(sf::Vector2u windowSize);

            void initialize(sf::Vector2f impulse);

            void update(sf::Time deltaTime);
            bool collide(entity *otherSprite);

    };