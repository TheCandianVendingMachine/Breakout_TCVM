// inputManager.hpp
// manages inputs. Can manage mosue and keyboard input
#pragma once

#include <unordered_map>
#include <functional>

#include <SFML/Window/Keyboard.hpp>

#include "input.hpp"

class inputManager
    {
        private:
            std::unordered_map<std::string, input> _inputs;

        public:
            void add(const std::string &name, sf::Keyboard::Key key, bool onPress, states activeState);
            void add(const std::string &name, sf::Keyboard::Key key, std::function<void()> onInput, bool onPress, states activeState);

            void changeFunction(const std::string &name, std::function<void()> func);

            void remove(const std::string &name);

            void handleInput(sf::Event &event, states currentState);

    };