#include "gameState.hpp"
#include "../game/globals.hpp"

gameState::gameState() : _livesPrefix("Lives Left: ")
    {
        _state = GAME_STATE;

        _renderOvertop = false;
        _updateUnderneath = false;
    }

void gameState::initialize()
    {
        _gameOver = false;
        _lostGame = false;

        auto windowSize = globals::_stateMachine.getWindow()->getSize();

        _livesText.setFont(*globals::_fontManager.get("gameFont", false));
        _livesText.setString(_livesPrefix + "3");
        // I have to have these magic numbers because the font is dumb and doesn't want to work properly
        _livesText.setPosition(windowSize.x - (_livesText.getGlobalBounds().width + 10),
                               windowSize.y - (_livesText.getGlobalBounds().height * 2));

        _gameOverText.setFont(*globals::_fontManager.get("gameFont", false));
        _gameOverText.setString("GAME OVER");
        _gameOverText.setColor(sf::Color::Red);
        _gameOverText.setCharacterSize(90);
        _gameOverText.setPosition((windowSize.x / 2) - (_gameOverText.getGlobalBounds().width / 2), windowSize.y / 2);

        globals::_eventManager.subscribe(this, LEVEL_CLEARED);
        globals::_eventManager.subscribe(this, LOSE_LIFE);
    }

void gameState::render()
    {
        _world.render(*globals::_stateMachine.getWindow());
        globals::_stateMachine.getWindow()->draw(_livesText);

        if (_gameOver && _lostGame)
            {
                globals::_stateMachine.getWindow()->draw(_gameOverText);
            }
    }

void gameState::update(sf::Time deltaTime)
    {
        if (!_gameOver)
            {
                _world.update(deltaTime);
            }
        else if (!_lostGame)
            {
                if (_timer.hasCountdownFinished())
                    {
                        _world.nextLevel();
                        _gameOver = false;

                        _world.initialize();
                    }
            }
        else
            {
                if (_timer.hasCountdownFinished())
                    {
                        globals::_stateMachine.popState();
                    }
            }
    }

void gameState::alert(eventData data)
    {
        switch (data._event)
            {
                case LEVEL_CLEARED:
                    _gameOver = true;
                    _timer.start(sf::seconds(3));
                case LOSE_LIFE:
                    if (data._data.intDat >= 0)
                        {
                            _livesText.setString(_livesPrefix + std::to_string(data._data.intDat));
                        }
                    else
                        {
                            _timer.start(sf::seconds(3));
                            _lostGame = true;
                            _gameOver = true;
                        }
                    break;
                default:
                    break;
            }
    }

void gameState::cleanup()
    {
        globals::_eventManager.unsubscribe(this, LEVEL_CLEARED);
        globals::_eventManager.unsubscribe(this, LOSE_LIFE);
        _world.cleanup();
    }

gameState::~gameState()
    {
        cleanup();
    }
