// level.hpp
// the game level. Loads levels from file and displays accordingly
#pragma once

#include <string>
#include <vector>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "../managers/events/observer.hpp"

class block;
class powerup;

class level : public observer
    {
        private:
            std::vector<block*> _blocks;
            std::vector<powerup> _powerups;

            unsigned int _blockSizeX;
            unsigned int _blockSizeY;

        public:
            level();
            level(unsigned int blockSizeX, unsigned int blockSizeY);

            void initialize();

            void load(const std::string &levelFilePath);
            bool getLevelCleared();

            std::vector<block*> *getBlocks();
            std::vector<powerup> *getPowerups();

			void alert(eventData data);

            void cleanup();
            ~level();

    };