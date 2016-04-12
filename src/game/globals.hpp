// globals.hpp
// all global variables needed
#pragma once

#include "../states/stateMachine.hpp"
#include "../states/states.hpp"

#include "../managers/resourceManager.hpp"

#include "../managers/input/inputManager.hpp"

#include "../managers/eventManager.hpp"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Keyboard.hpp>

class globals
    {
        public:
            static eventManager _eventManager;

            static stateMachine _stateMachine;

            static resourceManager<sf::Texture> _textureManager;

            static inputManager _keyboardManager;

            static states _gameStates;
    };