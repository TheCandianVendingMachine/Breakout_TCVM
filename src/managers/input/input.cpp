#include "input.hpp"

input::input(sf::Keyboard::Key key, std::function<void()> onInput, bool onPress, states activeState)
    {
        _input = key;
        
        _onInput = onInput;
        _onPress = onPress;

        _activeState = activeState;
    }

void input::execute(sf::Event &event, states active)
    {
        // if the active state is the current state, and the key is being pressed
        if (active == _activeState && event.key.code == _input && (_onPress ? event.type == sf::Event::KeyPressed : event.type == sf::Event::KeyReleased))
            {
                _onInput();
            }
    }

sf::Keyboard::Key input::getInput() const
    {
        return _input;
    }

states input::getState() const
    {
        return _activeState;
    }