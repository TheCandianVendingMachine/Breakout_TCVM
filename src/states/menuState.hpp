// menuState.hpp
// The main menu for the game. Will just feature buttons
#pragma once

#include <vector>

#include "state.hpp"
#include "../UI/clickableButton.hpp"

class menuState : public state
    {
        private:
            std::vector<clickableButton> _buttons;

        public:
            menuState();

            void initialize();

            void render();
            void update(sf::Time deltaTime);

            void cleanup();

    };