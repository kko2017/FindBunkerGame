#include "GameState.h"

GameState::GameState(GEX::StateStack & stack, Context context)
	: State(stack, context)
	, world_(*context.window)   // part of game state, render window
	, player_(*context.player)
{}

void GameState::draw()
{
	world_.draw();
}
//10.23
bool GameState::update(sf::Time dt)
{
	GEX::CommandQueue& commands = world_.getCommandQueue();
	world_.update(dt, commands);

	if (!world_.hasAlivePlayer())
	{
		if (world_.getLives() == 0)
		{
			player_.setMissionStatus(GEX::MissionStatus::MissionFailure);
			requestStackPush(GEX::StateID::GameOver);
		}
		else
		{
			world_.addCharacter();
		}
	}
	else if (world_.winGame()) {
		player_.setMissionStatus(GEX::MissionStatus::MissionSuccess);
		requestStackPush(GEX::StateID::GameOver);
	}

	player_.handleRealtimeInput(commands);

	return true;
}

bool GameState::handleEvent(const sf::Event & event)
{
	GEX::CommandQueue& commands = world_.getCommandQueue();
	player_.handleEvent(event, commands);

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) 
	{
		requestStackPush(GEX::StateID::Pause);
	}

	return true;
}
