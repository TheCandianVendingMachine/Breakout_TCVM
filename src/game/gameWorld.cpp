#include "gameWorld.hpp"

#include "../entity/entity.hpp"
#include "../entity/block.hpp"
#include "../entity/player.hpp"
#include "../entity/ball.hpp"
#include "../entity/powerup.hpp"

#include "globals.hpp"

#include <algorithm>

gameWorld::gameWorld()
    {
        _level = std::make_shared<level>(level(64, 32));
        _levelNumber = 0;

        nextLevel();

        sf::Vector2u windowSize = globals::_stateMachine.getWindow()->getSize();

		_ball = std::make_shared<ball>(ball(globals::_stateMachine.getWindow()->getSize()));
		_player = std::make_shared<player>(player(windowSize, sf::Vector2f(windowSize.x / 2.f, windowSize.y - 50.f)));

        initialize();

		_entities.push_back(dynamic_cast<entity*>(&*_player));
		_entities.push_back(dynamic_cast<entity*>(&*_ball));

		std::sort(_entities.begin(), _entities.end(), [](entity *entOne, entity *entTwo) {return entOne->getID() < entTwo->getID(); });
    }

void gameWorld::initialize()
    {
        _ball->initialize(sf::Vector2f(0, 150));
        _player->initialize();
		_level->initialize();
    }

void gameWorld::update(sf::Time deltaTime)
    {
        for (auto &ent : _entities)
            {
                ent->update(deltaTime);
            }

		for (auto &block : *_level->getBlocks())
			{
				if (block.getAlive()) 
					{
						_ball->collide(dynamic_cast<entity*>(&block));
					}
			}

        for (auto &power : *_level->getPowerups())
            {
                power.update(deltaTime);
                if (power.collide(dynamic_cast<entity*>(&*_player)))
                    {
                        power.setAlive(false);
                    }

                if (power.getPosition().y > globals::_stateMachine.getWindow()->getSize().y)
                    {
                        power.setAlive(false);
                    }
            }

        _ball->collide(dynamic_cast<entity*>(&*_player));

		if (_ball->getPosition().y > globals::_stateMachine.getWindow()->getSize().y)
			{
				_player->decreaseLives();
				if (!_player->playerDead())
					{
                        initialize();
					}
			}

        if (_level->getLevelCleared())
            {
                globals::_eventManager.alert(eventData(0, LEVEL_CLEARED));
            }
    }

void gameWorld::render(sf::RenderWindow &app)
    {
        for (auto &ent : _entities)
            {
                ent->draw(app);
            }

		for (auto &block : *_level->getBlocks())
			{
				block.draw(app);
			}

        for (auto &power : *_level->getPowerups())
            {
                power.draw(app);
            }
    }

void gameWorld::setLevel(int levelNum)
    {
        _levelNumber = levelNum;
        std::string levelString = "level_" + std::to_string(levelNum);
        _level->load("assets/levels/" + levelString + ".txt");
    }

void gameWorld::nextLevel()
    {
        std::string levelString = "level_" + std::to_string(++_levelNumber);
        _level->load("assets/levels/" + levelString + ".txt");
    }

void gameWorld::cleanup()
	{
		_level->cleanup();
	}

gameWorld::~gameWorld()
	{
		cleanup();
	}
