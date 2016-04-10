// gameState.hpp
// the game state
#pragma once

#include "state.hpp"

#include "../game/gameWorld.hpp"

class gameState : public state
    {
        private:
            gameWorld _world;

        public:
            gameState();
            void initialize();

            void render();
            void update(sf::Time deltaTime);

            void cleanup();

            ~gameState();
    };