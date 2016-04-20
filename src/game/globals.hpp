// globals.hpp
// all global variables needed
#pragma once

#include "../states/stateMachine.hpp"
#include "../states/states.hpp"

#include "../managers/resourceManager.hpp"

#include "../managers/input/inputManager.hpp"

#include "../managers/events/eventManager.hpp"

#include "../managers/score/highscoreManager.hpp"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Window/Keyboard.hpp>

class globals
    {
        public:
            static eventManager _eventManager;

            static inputManager<sf::Keyboard::Key> _keyboardManager;
            static inputManager<sf::Mouse::Button> _mouseManager;

            static resourceManager<sf::Texture> _textureManager;
            static resourceManager<sf::Font> _fontManager;

            static stateMachine _stateMachine;
            static states _gameStates;

            static highscoreManager _highscoreManager;

    };