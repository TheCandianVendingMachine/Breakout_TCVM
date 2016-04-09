// input.hpp
// input object. What will happen when key is pressed, and what state it will be active in
#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>

#include <functional>

#include "../../states/states.hpp"

class input
    {
        private:
            sf::Keyboard::Key _input;

            std::function<void()> _onInput;
            bool _onPress;

            states _activeState;

        public:
            input(sf::Keyboard::Key key, std::function<void()> onInput, bool onPress, states activeState);
            void execute(sf::Event &event, states active);

            sf::Keyboard::Key getInput() const;
            states getState() const;

    };
