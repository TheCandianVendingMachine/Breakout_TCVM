#include "globals.hpp"

eventManager globals::_eventManager;

stateMachine globals::_stateMachine;
states globals::_gameStates;

resourceManager<sf::Texture> globals::_textureManager;
resourceManager<sf::Font> globals::_fontManager;

inputManager globals::_keyboardManager;