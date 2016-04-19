// paddle.hpp
// the paddle in the game
#pragma once

#include "moveableEntity.hpp"
#include "../managers/events/observer.hpp"

class powerup;

class player : public moveableEntity, public observer
    {
        protected:
            sf::Vector2f _startPos;
			sf::Vector2u _windowSize;

            sf::Vector2f _defaultSize;

            const float _speed;

			int _lives;

            powerup *_currentPower;

        public:
			player(sf::Vector2u windowSize, sf::Vector2f startPos);
            void initialize();

            void update(sf::Time deltaTime);

            void alert(eventData data);

			void decreaseLives();
            const int getLives() const;

			bool playerDead() const;

            ~player();

    };