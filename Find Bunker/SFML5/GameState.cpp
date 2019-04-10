#include "GameState.h"

#include <vector>
#include <fstream>
#include <ctime>

GameState::GameState(GEX::StateStack & stack, Context context)
	: State(stack, context)
	, world_(*context.window, *context.sound)   // part of game state, render window
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
			return false;
		}
		else
		{
			world_.addCharacter();
		}
	}
	else if (world_.winGame()) 
	{
		saveRecord();
		player_.setMissionStatus(GEX::MissionStatus::MissionSuccess);
		requestStackPush(GEX::StateID::GameOver);
		return false;
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
	
	// get current date
	std::time_t now;
	struct tm timeInfo;
	char buffer[20];

	time(&now);
	localtime_s(&timeInfo, &now);

	strftime(buffer, 20, "%m-%d-%Y", &timeInfo);
	std::string str(buffer);

	// get socres
	std::vector<std::string> records;

	std::ifstream is;
	std::string record = "";
	std::string fileName = "Record/highRecord.txt";

	is.open(fileName);

	while (std::getline(is, record))
	{
		records.push_back(record);
	}

	is.close();

	static std::string tmp = "";
	if (tmp != std::to_string(world_.getFinalElapsedTime()) + "sec     " + str)
	{
		tmp = "";
	}

	if (tmp == "")
	{
		tmp = std::to_string(world_.getFinalElapsedTime()) + "sec     " + str;
		records.push_back(tmp);
		std::sort(records.begin(), records.end());

		std::remove(fileName.c_str());

		std::ofstream outFile(fileName, std::ios::app);
		for (int i = 0; i < records.size(); i++)
		{
			std::string tmp = records[i];
			outFile << tmp << std::endl;
		}

		records.clear();
		outFile.close();
	}
}
