// level.hpp
// the game level. Loads levels from file and displays accordingly
#pragma once

#include <string>
#include <vector>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class entity;

class level
    {
        private:
            std::vector<entity*> _blocks;

            unsigned int _blockSizeX;
            unsigned int _blockSizeY;

        public:
            level() = default;
            level(unsigned int blockSizeX, unsigned int blockSizeY);

            void load(const std::string &levelFilePath);

            std::vector<entity*> *getBlocks();

            void cleanup();
            ~level();

    };