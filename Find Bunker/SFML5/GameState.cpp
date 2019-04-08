#include "GameState.h"

#include <vector>
#include <fstream>

GameState::GameState(GEX::StateStack & stack, Context context)
	: State(stack, context)
	, world_(*context.window)   // part of game state, render window
	, player_(*context.player)
{
	context.music->play(GEX::MusicID::MissionTheme);
}

void GameState::draw()
{
	world_.draw();
}

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
		saveRecord();
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

void GameState::saveRecord()
{
	std::vector<int> records;

	std::ifstream is;
	std::string record = "";
	std::string fileName = "Record/highRecord.txt";

	is.open(fileName);

	while (std::getline(is, record))
	{
		int tmp = std::stoi(record);
		records.push_back(tmp);
	}

	is.close();

	records.push_back(world_.getFinalElapsedTime());
	std::sort(records.begin(), records.end());

	std::remove(fileName.c_str());

	std::ofstream outFile(fileName, std::ios::app);
	for (int i = 0; i < 10; i++)
	{
		std::string tmp = std::to_string(records[i]);
		outFile << tmp << std::endl;
	}

	outFile.close();
}
