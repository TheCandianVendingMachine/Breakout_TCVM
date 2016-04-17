// paddle.hpp
// the paddle in the game
#pragma once

#include "moveableEntity.hpp"

class player : public moveableEntity
    {
        protected:
            sf::Vector2f _startPos;
			sf::Vector2u _windowSize;

            const float _speed;

			int _lives;

        public:
			player(sf::Vector2u windowSize, sf::Vector2f startPos);
            void initialize();

            void update(sf::Time deltaTime);

			void decreaseLives();
            const int getLives() const;

			bool playerDead() const;

    };