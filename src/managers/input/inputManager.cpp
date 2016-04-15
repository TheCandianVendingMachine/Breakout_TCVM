#include "inputManager.hpp"

void inputManager::add(const std::string &name, sf::Keyboard::Key key, bool onPress, states activeState)
    {
        _inputs[name] = input(key, [] () {}, onPress, activeState);
    }

void inputManager::add(const std::string &name, sf::Keyboard::Key key, std::function<void()> onInput, bool onPress, states activeState)
    {
        _inputs[name]= input(key, onInput, onPress, activeState);
    }

void inputManager::changeFunction(const std::string &name, std::function<void()> func)
    {
        _inputs[name].setFunction(func);
    }

void inputManager::remove(const std::string &name)
    {
        auto it = _inputs.find(name);
        if (it != _inputs.end())
            {
                _inputs.erase(it);
            }
    }

void inputManager::handleInput(sf::Event &event, states currentState)
    {
        for (auto &key : _inputs)
            {
                key.second.execute(event, currentState);
            }
    }
