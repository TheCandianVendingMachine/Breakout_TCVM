#include "level.hpp"
#include <fstream>

#include "../entity/block.hpp"
#include "../entity/powerup.hpp"

#include "../utilities/strFuncs.hpp"
#include "../utilities/randomizer.hpp"

#include "../game/globals.hpp"

level::level()
	{
		_blockSizeX = 0;
		_blockSizeY = 0;
	}

level::level(unsigned int blockSizeX, unsigned int blockSizeY)
    {
        _blockSizeX = blockSizeX;
        _blockSizeY = blockSizeY;
    }

void level::initialize()
    {
		globals::_eventManager.subscribe(this, BALL_HIT_BLOCK);
    }

void level::load(const std::string &levelFilePath)
    {
        _powerups.clear();

        std::ifstream read(levelFilePath);
        std::string line = "";

        unsigned int currentBlockInArr = 0;

        unsigned int currentTextPosX = 0;
        unsigned int currentTextPosY = 0;

        unsigned int spacing = 0;

        if (read.is_open())
            {
                while (std::getline(read, line))
                    {
                        // level options
                        auto linePhrase = strfn::doesStringContain(line, "spacing");
                        if (linePhrase.second)
                            {
                                spacing = std::stoul(strfn::splitString(line, '=').second);
                            }
                        else
                            {
                                for (auto &chr : line)
                                    {
                                        if (chr == '1')
                                            {
                                                if (currentBlockInArr < _blocks.size())
                                                    {
                                                        _blocks[currentBlockInArr++].setPosition(currentTextPosX * (_blockSizeX + spacing), currentTextPosY * (_blockSizeY + spacing));
                                                    }
                                                else
                                                    {
														_blocks.emplace_back();
                                                        _blocks[currentBlockInArr++].setPosition(currentTextPosX * (_blockSizeX + spacing), currentTextPosY * (_blockSizeY + spacing));
                                                    }
                                            }
                                        else if (chr == '#')
                                            {
                                                // if I want to clarify something on the level, # can be used at the end of a line to
                                                // comment a certain phrase
                                                break;
                                            }

                                        currentTextPosX++;
                                    }

                                currentTextPosY++;
                                currentTextPosX = 0;
                            }
                    }

                read.close();
            }
        else
            {
                globals::_eventManager.alert(eventData(0, ALL_LEVELS_CLEARED));
            }

		for (auto it = _blocks.begin() + currentBlockInArr; it != _blocks.end();)
            {
				it = _blocks.erase(it);
            }

        for (auto &ent : _blocks)
            {
                ent.setAlive(true);
            }
    }

bool level::getLevelCleared()
    {
        for (auto &ent : _blocks)
            {
                if (ent.getAlive())
                    {
                        return false;
                    }
            }

        return true;
    }

std::vector<block> *level::getBlocks()
    {
        return &_blocks;
    }

std::vector<powerup> *level::getPowerups()
    {
        return &_powerups;
    }

void level::alert(eventData data)
	{
        switch (data._event)
            {
                case BALL_HIT_BLOCK:
                    {
						auto it = std::find_if(_blocks.begin(), _blocks.end(),
							[data](block &ent) { return ent.getID() == data._data.intDat; });
						if (it != _blocks.end())
							{
								it->setAlive(false);
							}

                        // (1/X)% chance of spawning a power up on block hit
                        bool powerSpawn = (rndm::random(0, 10) == 1);
                        if (powerSpawn)
                            {
                                _powerups.emplace_back(it->getPosition());
                            }
					}
                default:
                    break;
            }
	}


void level::cleanup()
    {
		globals::_eventManager.unsubscribe(this, BALL_HIT_BLOCK);
    }

level::~level()
    {
        //cleanup();
    }
