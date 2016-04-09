// inputManager.hpp
// manages inputs. Can manage mosue and keyboard input
#pragma once

#include <vector>
#include <functional>

#include <SFML/Window/Keyboard.hpp>

#include "input.hpp"

class inputManager
    {
        private:
            std::vector<input> _inputs;

        public:
            void add(sf::Keyboard::Key key, std::function<void()> onInput, bool onPress, states activeState);
            void remove(sf::Keyboard::Key key, states state);

            void handleInput(sf::Event &event, states currentState);

    };