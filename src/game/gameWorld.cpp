#include "gameWorld.hpp"
#include "../entity/entity.hpp"
#include "../entity/block.hpp"
#include "../entity/player.hpp"
#include "../entity/ball.hpp"

#include <algorithm>

#include "globals.hpp"

gameWorld::gameWorld()
    {
        _level = new level(64, 32);
        _level->load("assets/levels/level_01.txt");

        sf::Vector2u windowSize = globals::_stateMachine.getWindow()->getSize();

		_ball = new ball(globals::_stateMachine.getWindow()->getSize());
		_ball->initialize(sf::Vector2f(0, 150));
		_ball->setPosition(windowSize.x / 2, windowSize.y - 100);

		_player = new player(windowSize, sf::Vector2f(windowSize.x / 2, windowSize.y - 50));

		_entities.push_back(_player);
		_entities.push_back(_ball);

		std::sort(_entities.begin(), _entities.end(), [](entity *entOne, entity *entTwo) {return entOne->getID() < entTwo->getID(); });
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

        _ball->collide(_player);
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
