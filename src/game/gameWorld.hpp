// gameWorld.hpp
// holds all entities, updates them, and manages the level
#pragma once

#include <vector>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>

#include <memory>

#include "level.hpp"

class entity;
class ball;
class player;

class gameWorld
    {
        private:
            std::shared_ptr<level> _level;

			std::shared_ptr<ball> _ball;
			std::shared_ptr<player> _player;

            std::vector<entity*> _entities;

            unsigned int _levelNumber;

        public:
            gameWorld();

            void initialize();

            void update(sf::Time deltaTime);
            void render(sf::RenderWindow &app);

            void setLevel(int levelNum);
            void nextLevel();

			void cleanup();
			~gameWorld();
    };