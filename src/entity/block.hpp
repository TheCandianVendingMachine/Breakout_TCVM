// block.hpp
// a hittable block entity
#pragma once

#include "entity.hpp"

namespace sf
	{
		class RenderWindow;
	}

class block : public entity
    {
		private:
			bool _alive;

        public:
            block();

			const bool getAlive() const;
			void setAlive(bool alive);

			void draw(sf::RenderWindow &app);

            void update(sf::Time deltaTime);

			block & operator=(const block &other);

    };