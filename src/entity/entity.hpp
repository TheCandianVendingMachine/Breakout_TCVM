// entity.hpp
// base entity class
#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>

class entity
    {
        protected:
            sf::Sprite _sprite;

        public:
            virtual void draw(sf::RenderTarget &target);
            virtual void update(sf::Time deltaTime) = 0;
            virtual bool collide(sf::FloatRect other) = 0;

            void setPosition(sf::Vector2f pos);
            void setPosition(float X, float Y);

            sf::Vector2f getPosition();
            sf::Sprite *getSprite();

            virtual ~entity();

    };