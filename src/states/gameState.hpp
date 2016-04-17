// gameState.hpp
// the game state
#pragma once

#include "state.hpp"

#include "../game/gameWorld.hpp"
#include "../managers/observer.hpp"
#include "../utilities/countdown.hpp"

#include <SFML/Graphics/Text.hpp>

class gameState : public state, public observer
    {
        private:
            gameWorld _world;
            countdown _timer;

            bool _gameOver;
            bool _lostGame;

            // this is just the phrase "Lives Left: "
            const std::string _livesPrefix;
            sf::Text _livesText;
            sf::Text _gameOverText;

        public:
            gameState();
            void initialize();

            void render();
            void update(sf::Time deltaTime);

            void alert(eventData data);

            void cleanup();

            ~gameState();
    };