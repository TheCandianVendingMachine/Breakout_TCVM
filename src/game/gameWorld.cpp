#include "gameWorld.hpp"
#include "../entity/entity.hpp"
#include "../entity/ball.hpp"

#include <algorithm>

#include "globals.hpp"

gameWorld::gameWorld()
    {
        _level = level(64, 32);
        _level.load("assets/levels/level_01.txt");

        for (auto &block : *_level.getBlocks())
            {
                _entities.push_back(block);
            }

		_ball = new ball(globals::_stateMachine.getWindow()->getSize());
		_ball->initialize(sf::Vector2f(0, -50));
		_ball->setPosition(globals::_stateMachine.getWindow()->getSize().x / 2, globals::_stateMachine.getWindow()->getSize().y);

		_player = nullptr;
		_entities.push_back(_ball);

		std::sort(_entities.begin(), _entities.end(), [](entity *entOne, entity *entTwo) {return entOne->getID() < entTwo->getID(); });
    }

void gameWorld::update(sf::Time deltaTime)
    {
        for (auto &ent : _entities)
            {
				if (ent->getID() != _ball->getID())
					{
						_ball->collide(ent);
					}

                ent->update(deltaTime);
            }
    }

void gameWorld::render(sf::RenderWindow &app)
    {
        for (auto &ent : _entities)
            {
                ent->draw(app);
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
	}

gameWorld::~gameWorld()
	{
		cleanup();
	}
