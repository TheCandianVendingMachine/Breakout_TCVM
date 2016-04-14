// gameWorld.hpp
// holds all entities, updates them, and manages the level
#pragma once

#include <vector>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>

#include "level.hpp"

class entity;
class ball;
class player;

class gameWorld
    {
        private:
            level *_level;

			ball *_ball;
			player *_player;

            std::vector<entity*> _entities;

        public:
            gameWorld();

            void update(sf::Time deltaTime);
            void render(sf::RenderWindow &app);

			void cleanup();
			~gameWorld();
    };