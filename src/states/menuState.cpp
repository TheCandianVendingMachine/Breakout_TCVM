#include "menuState.hpp"
#include "../game/globals.hpp"

#include "gameState.hpp"
#include "highscoreState.hpp"

menuState::menuState()
    {
        _renderOvertop = false;
        _updateUnderneath = false;

        _state = MENU_STATE;
    }

void menuState::initialize()
    {
        auto window = globals::_stateMachine.getWindow();

        const int spacing = 50;

        clickableButton start;
        start.getText()->setFont(*globals::_fontManager.get("gameFont", false));
        start.setString("Start Game");
        start.setWindow(*window);
        start.setColour(sf::Color::Red);
        start.setPosition(sf::Vector2f((window->getSize().x / 2) - (start.getBounds().width / 2), (window->getSize().y / 2) - spacing));
        start.setFunction([] () 
            { 
                globals::_stateMachine.queueState(new gameState);
                globals::_stateMachine.popState();
            });

        clickableButton highscore;
        highscore.getText()->setFont(*globals::_fontManager.get("gameFont", false));
        highscore.setString("Highscores");
        highscore.setWindow(*window);
        highscore.setColour(sf::Color::Red);
        highscore.setPosition(sf::Vector2f((window->getSize().x / 2) - (highscore.getBounds().width / 2), (window->getSize().y / 2)));
        highscore.setFunction([] ()
            {
                globals::_stateMachine.queueState(new highscoreState);
            });

        clickableButton quit;
        quit.getText()->setFont(*globals::_fontManager.get("gameFont", false));
        quit.setString("Quit Game");
        quit.setWindow(*window);
        quit.setColour(sf::Color::Red);
        quit.setPosition(sf::Vector2f((window->getSize().x / 2) - (quit.getBounds().width / 2), (window->getSize().y / 2) + spacing));
        quit.setFunction([] ()
            { 
                globals::_stateMachine.getWindow()->close();
            });

        _buttons.push_back(quit);
        _buttons.push_back(highscore);
        _buttons.push_back(start);
    }

void menuState::render()
    {
        for (auto &but : _buttons)
            {
                but.render(*globals::_stateMachine.getWindow());
            }
    }

void menuState::update(sf::Time deltaTime)
    {
        for (auto &but : _buttons)
            {
                but.update();
            }
    }

void menuState::cleanup()
    {}
