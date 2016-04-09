// entity.hpp
// base entity class
#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>

class entity
    {
        protected:
            sf::Sprite _sprite;
            sf::Vector2f _impulse;

        public:
            virtual void draw(sf::RenderTarget &target);
            virtual void update(sf::Time deltaTime) = 0;
            virtual void move(sf::Vector2f impulse);

            void setPosition(sf::Vector2f pos);
            void setPosition(float X, float Y);

            sf::Vector2f getPosition();
            sf::Vector2f getImpulse() const;

            sf::Sprite *getSprite();

            virtual ~entity();

    };