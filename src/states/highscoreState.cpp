#include "highscoreState.hpp"
#include "../game/globals.hpp"

highscoreState::highscoreState()
    {}

void highscoreState::initialize()
    {
        sf::Text allScores;
        allScores.setFont(*globals::_fontManager.get("gameFont", true));
        allScores.setString("HIGHSCORES");
        allScores.setCharacterSize(50);
        allScores.setColor(sf::Color::Cyan);
        allScores.setPosition((globals::_stateMachine.getWindow()->getSize().x / 2) - (allScores.getGlobalBounds().width / 2), 0);
        _highscores.push_back(allScores);

        int count = 0;
        const int maxScoresDisplayed = 10;
        for (unsigned int i = 0; i < globals::_highscoreManager.getScores()->size() && i < maxScoresDisplayed; i++)
            {
                sf::Text newScore;
                newScore.setFont(*globals::_fontManager.get("gameFont", true));
                newScore.setString("RANK " + std::to_string(++count) + " - ");
                newScore.setPosition(allScores.getPosition().x + (allScores.getGlobalBounds().width / 10),
                                     /* 
                                     (i * X) - Distance Between Scores
                                     (allScores.getGlobalBounds().height + X) - Distance from "HIGHSCORES" text
                                     */
                                     (i * 40) + (allScores.getPosition().y + allScores.getGlobalBounds().height + 50));

                sf::Text score;
                score.setFont(*globals::_fontManager.get("gameFont", true));
                score.setString(std::to_string((*globals::_highscoreManager.getScores())[i]) + " Points");
                score.setPosition(newScore.getPosition().x + newScore.getGlobalBounds().width, newScore.getPosition().y);

                _highscores.push_back(newScore);
                _highscores.push_back(score);
            }

        _backButton.getText()->setFont(*globals::_fontManager.get("gameFont", true));
        _backButton.setString("Back To Menu");
        _backButton.setWindow(*globals::_stateMachine.getWindow());
        _backButton.setPosition(sf::Vector2f(_highscores.back().getPosition().x - (_backButton.getBounds().width / 2), _highscores.back().getPosition().y + 50));
        _backButton.setColour(sf::Color::Red);
        _backButton.setFunction([] () 
            {
                globals::_stateMachine.popState();
            });
    }

void highscoreState::render()
    {
        for (auto &point : _highscores)
            {
                globals::_stateMachine.getWindow()->draw(point);
            }

        _backButton.render(*globals::_stateMachine.getWindow());
    }

void highscoreState::update(sf::Time deltaTime)
    {
        _backButton.update();
    }

void highscoreState::cleanup()
    {}
