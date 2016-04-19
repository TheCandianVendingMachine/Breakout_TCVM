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
        const int heightFromBottomOfScreen = 35;

        _gameOver = false;
        _lostGame = false;

        auto windowSize = globals::_stateMachine.getWindow()->getSize();

        _scoreManager.addNewScore("blockScore", sf::Vector2f(135, windowSize.y - heightFromBottomOfScreen));

        _scoreText.setFont(*globals::_fontManager.get("gameFont", false));
        _scoreText.setString("Score: ");
        _scoreText.setPosition(_scoreManager.getScore("blockScore")->getText().getPosition().x - _scoreText.getGlobalBounds().width,
                               _scoreManager.getScore("blockScore")->getText().getPosition().y);


        _livesText.setFont(*globals::_fontManager.get("gameFont", false));
        _livesText.setString(_livesPrefix + "3");
        // I have to have these magic numbers because the font is dumb and doesn't want to work properly
        _livesText.setPosition(windowSize.x - (_livesText.getGlobalBounds().width + 10),
                               windowSize.y - heightFromBottomOfScreen);

        _gameOverText.setFont(*globals::_fontManager.get("gameFont", false));
        _gameOverText.setString("GAME OVER");
        _gameOverText.setColor(sf::Color::Red);
        _gameOverText.setCharacterSize(90);
        _gameOverText.setPosition((windowSize.x / 2) - (_gameOverText.getGlobalBounds().width / 2), windowSize.y / 2);

        globals::_eventManager.subscribe(this, LEVEL_CLEARED);
        globals::_eventManager.subscribe(this, BALL_HIT_BLOCK);
        globals::_eventManager.subscribe(this, LOSE_LIFE);
    }

void gameState::render()
    {
        _world.render(*globals::_stateMachine.getWindow());

        globals::_stateMachine.getWindow()->draw(_livesText);

        globals::_stateMachine.getWindow()->draw(_scoreText);
        _scoreManager.render(*globals::_stateMachine.getWindow());

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
                case BALL_HIT_BLOCK:
                    if ((_scoreManager.getScore("blockScore")->getScore() + _scoreManager.getScore("blockScore")->getIncrementAmount()) % 100 == 0)
                        {
                            _scoreManager.getScore("blockScore")->setIncrementAmount(25);
                        }
                    else
                        {
                            _scoreManager.getScore("blockScore")->setIncrementAmount(10);
                        }
                    _scoreManager.incrementScore("blockScore");
                    break;
                case POWERUP_GAINED:
                    _scoreManager.getScore("blockScore")->setIncrementAmount(5);
                    _scoreManager.incrementScore("blockScore");
                    break;
                default:
                    break;
            }
    }

void gameState::cleanup()
    {
        globals::_eventManager.unsubscribe(this, LEVEL_CLEARED);
        globals::_eventManager.unsubscribe(this, LOSE_LIFE);
        globals::_eventManager.unsubscribe(this, BALL_HIT_BLOCK);
        _world.cleanup();
    }

gameState::~gameState()
    {
        cleanup();
    }
