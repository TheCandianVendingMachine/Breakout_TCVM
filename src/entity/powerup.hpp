// powerup.hpp
// changes some aspect of the game. Spawns from destroyed blocks and activates if it hits the player
#pragma once

#include "moveableEntity.hpp"
#include "../utilities/countdown.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

class powerup : public moveableEntity
    {
        public:
            enum powerUpTypes
                {
                    WIDE_PADDLE,
                    SHORT_PADDLE,
                    EXTRA_LIFE,
                };

        private:
            powerUpTypes _type;

            const float _speed;
            countdown _powerupCountdown;

            bool _alive;

        public:
            powerup(sf::Vector2f position);

            void setAlive(bool value);

            void draw(sf::RenderWindow &app);
            void update(sf::Time deltaTime);
            bool collide(entity *otherSprite);

            powerUpTypes getType() const;

            const bool countdownDone();

            ~powerup();

    };