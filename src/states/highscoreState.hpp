// highscoreState.hpp
// view all highscores
#pragma once

#include <vector>
#include <SFML/Graphics/Text.hpp>

#include "state.hpp"
#include "../UI/clickableButton.hpp"

class highscoreState : public state
    {
        private:
            std::vector<sf::Text> _highscores;

            clickableButton _backButton;

        public:
            highscoreState();

            void initialize();

            void render();
            void update(sf::Time deltaTime);

            void cleanup();
    };