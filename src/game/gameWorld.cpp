#include "gameWorld.hpp"
#include "../entity/entity.hpp"

gameWorld::gameWorld()
    {
        _level = level(64, 32);
        _level.load("assets/levels/level_01.txt");

        for (auto &block : *_level.getBlocks())
            {
                _entities.push_back(block);
            }
    }

void gameWorld::update(sf::Time deltaTime)
    {
        for (unsigned int i = 0; i < _entities.size(); i++)
            {
                if (i + 1 < _entities.size())
                    {
                        _entities[i]->collide(_entities[i + 1]->getSprite()->getGlobalBounds());
                    }

                _entities[i]->update(deltaTime);
            }

    }

void gameWorld::render(sf::RenderWindow &app)
    {
        for (auto &ent : _entities)
            {
                ent->draw(app);
            }
    }
