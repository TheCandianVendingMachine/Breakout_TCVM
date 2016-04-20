#include "globals.hpp"

eventManager globals::_eventManager;

stateMachine globals::_stateMachine;
states globals::_gameStates;

resourceManager<sf::Texture> globals::_textureManager;
resourceManager<sf::Font> globals::_fontManager;

inputManager<sf::Keyboard::Key> globals::_keyboardManager;
inputManager<sf::Mouse::Button> globals::_mouseManager;

highscoreManager globals::_highscoreManager;