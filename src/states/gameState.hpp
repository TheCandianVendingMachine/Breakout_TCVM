// gameState.hpp
// the game state
#pragma once

#include "state.hpp"

#include "../game/gameWorld.hpp"
#include "../managers/events/observer.hpp"
#include "../utilities/countdown.hpp"

#include "../managers/score/scoreManager.hpp"

#include <SFML/Graphics/Text.hpp>

class gameState : public state, public observer
    {
        private:
            scoreManager _scoreManager;

            gameWorld _world;
            countdown _timer;

            bool _gameOver;
            bool _lostGame;

            // this is just the phrase "Lives Left: "
            const std::string _livesPrefix;
            sf::Text _livesText;
            sf::Text _gameOverText;

            sf::Text _scoreText;

        public:
            gameState();
            void initialize();

            void render();
            void update(sf::Time deltaTime);

            void alert(eventData data);

            void cleanup();

            ~gameState();
    };