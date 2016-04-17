#include "game.hpp"
#include "globals.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

#include "../states/gameState.hpp"

void game::initializeWindow()
    {
        app = new sf::RenderWindow(sf::VideoMode(1170, 700), "Breakout", sf::Style::Close);
        app->setFramerateLimit(60.0f);
    }

void game::initializeSounds()
    {}

void game::initializeTextures()
    {
        globals::_textureManager.add("assets/textures/NO_TEXTURE.png", "defaultTexture");
        globals::_textureManager.setDefaultResource("defaultTexture");
        
        globals::_textureManager.add("assets/textures/block.png", "blockTexture");
        globals::_textureManager.add("assets/textures/ball.png", "ballTexture");
        globals::_textureManager.add("assets/textures/paddle.png", "playerTexture");

        globals::_fontManager.add("assets/textures/font/Squares_Bold_Free.otf", "gameFont");
    }

void game::initializeControls()
    {
        globals::_keyboardManager.add("playerMovementLeftActive", sf::Keyboard::Left, true, GAME_STATE);
        globals::_keyboardManager.add("playerMovementLeftDeActive", sf::Keyboard::Left, false, GAME_STATE);

        globals::_keyboardManager.add("playerMovementRightActive", sf::Keyboard::Right, true, GAME_STATE);
        globals::_keyboardManager.add("playerMovementRightDeActive", sf::Keyboard::Right, false, GAME_STATE);
    }

void game::initialize()
    {
        initializeWindow();
        initializeTextures();
        initializeSounds();
        initializeControls();

        globals::_stateMachine.setWindow(app);
        globals::_stateMachine.queueState(new gameState);
    }

void game::cleanup()
    {
        delete app;
        app = nullptr;

        if (globals::_stateMachine.getAllStates()->empty())
            {
                for (auto &state : *globals::_stateMachine.getAllStates())
                    {
                        globals::_stateMachine.popState();
                    }
            }
    }

void game::start()
    {
        initialize();

        sf::Clock deltaClock; 
        deltaClock.restart();

        float updateTime = 1.f / 60.f;

        sf::Time currentTime = deltaClock.getElapsedTime();
        float accumulator = 0.0f;

        while (app->isOpen())
            {
                sf::Time newTime = deltaClock.getElapsedTime();
                sf::Time deltaTime = newTime - currentTime;
                currentTime = newTime;

                accumulator += deltaTime.asSeconds();

                while (accumulator >= updateTime)
                    {
                        if (app->hasFocus())
                            {
                                globals::_stateMachine.tick(deltaTime);
                            }
                        accumulator -= updateTime;
                    }
                globals::_stateMachine.render();

            }

        cleanup();
        globals::_stateMachine.cleanup();
    }

game::~game()
    {
        cleanup();
        globals::_stateMachine.cleanup();
    }
