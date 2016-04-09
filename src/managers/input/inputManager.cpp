#include "inputManager.hpp"

void inputManager::add(sf::Keyboard::Key key, std::function<void()> onInput, bool onPress, states activeState)
    {
        _inputs.emplace_back(key, onInput, onPress, activeState);
    }

void inputManager::remove(sf::Keyboard::Key key, states state)
    {
        auto it = std::remove_if(_inputs.begin(), _inputs.end(), [key, state] (input &in) { return (in.getInput() == key && in.getState() == state);});

        if (it != _inputs.end())
            {
                _inputs.erase(it);
            }
    }

void inputManager::handleInput(sf::Event &event, states currentState)
    {
        for (auto &key : _inputs)
            {
                key.execute(event, currentState);
            }
    }
