// entity.hpp
// base entity class
#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>

class entity
    {
        public:
            enum entityID
                {
                    PLAYER,
                    BALL,
                    BLOCK,
                    POWER_UP,
                };

        protected:
            sf::Sprite _sprite;

            entityID _entID;
			const unsigned int _ID;

			static unsigned int _allIDs;

        public:
			entity();

            virtual void draw(sf::RenderTarget &target);
            virtual void update(sf::Time deltaTime) = 0;

            void setPosition(sf::Vector2f pos);
            void setPosition(float X, float Y);

            const entityID getEntityID() const;
			const unsigned int getID() const;

            sf::Vector2f getPosition();
            sf::Sprite *getSprite();

            virtual ~entity();

    };