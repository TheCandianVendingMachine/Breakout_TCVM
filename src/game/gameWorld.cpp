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
        _level = new level(64, 32);
        _levelNumber = 0;

        nextLevel();

        sf::Vector2u windowSize = globals::_stateMachine.getWindow()->getSize();

		_ball = new ball(globals::_stateMachine.getWindow()->getSize());
		_player = new player(windowSize, sf::Vector2f(windowSize.x / 2.f, windowSize.y - 50.f));

        initialize();

		_entities.push_back(_player);
		_entities.push_back(_ball);

		std::sort(_entities.begin(), _entities.end(), [](entity *entOne, entity *entTwo) {return entOne->getID() < entTwo->getID(); });
    }

void gameWorld::initialize()
    {
        _ball->initialize(sf::Vector2f(0, 150));
        _player->initialize();
    }

void gameWorld::update(sf::Time deltaTime)
    {
        for (auto &ent : _entities)
            {
                ent->update(deltaTime);
            }

		for (auto &block : *_level->getBlocks())
			{
				if (block->getAlive()) 
					{
						_ball->collide(block);
					}
			}

        for (auto &power : *_level->getPowerups())
            {
                power.update(deltaTime);
                if (power.collide(_player))
                    {
                        power.setAlive(false);
                    }

                if (power.getPosition().y > globals::_stateMachine.getWindow()->getSize().y)
                    {
                        power.setAlive(false);
                    }
            }

        _ball->collide(_player);

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
				block->draw(app);
			}

        for (auto &power : *_level->getPowerups())
            {
                power.draw(app);
            }
    }

void gameWorld::nextLevel()
    {
        std::string levelString = "level_" + std::to_string(++_levelNumber);
        _level->load("assets/levels/" + levelString + ".txt");
    }

void gameWorld::cleanup()
	{
		if (_ball)
			{
				delete _ball;
				_ball = nullptr;
			}

		if (_player)
			{
				delete _player;
				_player = nullptr;
			}

		if (_level)
			{
				_level->cleanup();
				delete _level;
				_level = nullptr;
			}
	}

gameWorld::~gameWorld()
	{
		cleanup();
	}
