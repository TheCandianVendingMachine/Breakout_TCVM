#include "gameState.hpp"
#include "../game/globals.hpp"

gameState::gameState()
    {
        _state = GAME_STATE;

        _renderOvertop = false;
        _updateUnderneath = false;
    }

void gameState::initialize()
    {
        
    }

void gameState::render()
    {
        _world.render(*globals::_stateMachine.getWindow());
    }

void gameState::update(sf::Time deltaTime)
    {
        _world.update(deltaTime);
    }

void gameState::cleanup()
    {
    }

gameState::~gameState()
    {
        cleanup();
    }
