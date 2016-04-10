#include "level.hpp"
#include "../entity/block.hpp"
#include <fstream>

#include "../utilities/strFuncs.hpp"

level::level(unsigned int blockSizeX, unsigned int blockSizeY)
    {
        _blockSizeX = blockSizeX;
        _blockSizeY = blockSizeY;
    }

void level::load(const std::string &levelFilePath)
    {
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
                                                        _blocks[currentBlockInArr++]->setPosition(currentTextPosX * (_blockSizeX + spacing), currentTextPosY * (_blockSizeY + spacing));
                                                    }
                                                else
                                                    {
                                                        _blocks.push_back(new block);
                                                        _blocks[currentBlockInArr++]->setPosition(currentTextPosX * (_blockSizeX + spacing), currentTextPosY * (_blockSizeY + spacing));
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
            }

        read.close();

        for (unsigned int i = currentBlockInArr; i < _blocks.size(); i++)
            {
                delete _blocks[currentBlockInArr];
                _blocks[currentBlockInArr] = nullptr;
            }
    }

std::vector<entity*> *level::getBlocks()
    {
        return &_blocks;
    }


void level::cleanup()
    {
        for (auto &block : _blocks)
            {
                delete block;
                block = nullptr;
            }
    }

level::~level()
    {
        cleanup();
    }
