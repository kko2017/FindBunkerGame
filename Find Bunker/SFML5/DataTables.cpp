#include "DataTables.h"
#include "JsonFrameParser.h"
#include "Animation2.h"


std::map<GEX::DynamicObjects::Type, GEX::DynamicObjectsData> GEX::initializeDynamicObjectsData()
{
	std::map<DynamicObjects::Type, DynamicObjectsData> data;

	// Set the character' data
	data[DynamicObjects::Type::Character].texture = TextureID::Character;
	data[DynamicObjects::Type::Character].isAlive = true;
	data[DynamicObjects::Type::Character].speed = 50.f;

	JsonFrameParser frames = JsonFrameParser("Media/Textures/ke2.json");

	data[DynamicObjects::Type::Character].animations[DynamicObjects::State::Down].addFrameSet(frames.getFramesFor("down"));
	data[DynamicObjects::Type::Character].animations[DynamicObjects::State::Down].setDuration(sf::seconds(1.f));
	data[DynamicObjects::Type::Character].animations[DynamicObjects::State::Down].setRepeating(true);
													 
	data[DynamicObjects::Type::Character].animations[DynamicObjects::State::Up].addFrameSet(frames.getFramesFor("up"));
	data[DynamicObjects::Type::Character].animations[DynamicObjects::State::Up].setDuration(sf::seconds(1.f));
	data[DynamicObjects::Type::Character].animations[DynamicObjects::State::Up].setRepeating(true);
												
	data[DynamicObjects::Type::Character].animations[DynamicObjects::State::Right].addFrameSet(frames.getFramesFor("right"));
	data[DynamicObjects::Type::Character].animations[DynamicObjects::State::Right].setDuration(sf::seconds(1.f));
	data[DynamicObjects::Type::Character].animations[DynamicObjects::State::Right].setRepeating(true);
													 
	data[DynamicObjects::Type::Character].animations[DynamicObjects::State::Left].addFrameSet(frames.getFramesFor("left"));
	data[DynamicObjects::Type::Character].animations[DynamicObjects::State::Left].setDuration(sf::seconds(1.f));
	data[DynamicObjects::Type::Character].animations[DynamicObjects::State::Left].setRepeating(true);

	// set the vehicle1's data
	data[DynamicObjects::Type::Vehicle1].texture = TextureID::Vehicle1;
	data[DynamicObjects::Type::Vehicle1].textureRect = sf::IntRect(0,0,96,45);
	data[DynamicObjects::Type::Vehicle1].isAlive = true;
	data[DynamicObjects::Type::Vehicle1].speed = 50.f;

	data[DynamicObjects::Type::Vehicle1].animations[DynamicObjects::State::Drive].addFrame(sf::IntRect(0, 0, 96, 45));
	data[DynamicObjects::Type::Vehicle1].animations[DynamicObjects::State::Drive].setDuration(sf::seconds(1.f));
	data[DynamicObjects::Type::Vehicle1].animations[DynamicObjects::State::Drive].setRepeating(true);
	

	// set the vehicle2's data
	data[DynamicObjects::Type::Vehicle2].texture = TextureID::Vehicle2;
	data[DynamicObjects::Type::Vehicle2].textureRect = sf::IntRect(0,0,95,44);
	data[DynamicObjects::Type::Vehicle2].isAlive = true;
	data[DynamicObjects::Type::Vehicle2].speed = 50.f;

	data[DynamicObjects::Type::Vehicle2].animations[DynamicObjects::State::Drive].addFrame(sf::IntRect(0, 0, 95, 44));
	data[DynamicObjects::Type::Vehicle2].animations[DynamicObjects::State::Drive].setDuration(sf::seconds(1.f));
	data[DynamicObjects::Type::Vehicle2].animations[DynamicObjects::State::Drive].setRepeating(true);

	// set the vehicle3's data
	data[DynamicObjects::Type::Vehicle3].texture = TextureID::Vehicle3;
	data[DynamicObjects::Type::Vehicle3].textureRect = sf::IntRect(0, 0, 94, 61);
	data[DynamicObjects::Type::Vehicle3].isAlive = true;
	data[DynamicObjects::Type::Vehicle3].speed = 50.f;
									  
	data[DynamicObjects::Type::Vehicle3].animations[DynamicObjects::State::Drive].addFrame(sf::IntRect(0, 0, 94, 61));
	data[DynamicObjects::Type::Vehicle3].animations[DynamicObjects::State::Drive].setDuration(sf::seconds(1.f));
	data[DynamicObjects::Type::Vehicle3].animations[DynamicObjects::State::Drive].setRepeating(true);

	// set the vehicle4's data
	data[DynamicObjects::Type::Vehicle4].texture = TextureID::Vehicle4;
	data[DynamicObjects::Type::Vehicle4].textureRect = sf::IntRect(0,51,96,45);
	data[DynamicObjects::Type::Vehicle4].isAlive = true;
	data[DynamicObjects::Type::Vehicle4].speed = -50.f;
									  
	data[DynamicObjects::Type::Vehicle4].animations[DynamicObjects::State::Drive].addFrame(sf::IntRect(0, 51, 96, 45));
	data[DynamicObjects::Type::Vehicle4].animations[DynamicObjects::State::Drive].setDuration(sf::seconds(1.f));
	data[DynamicObjects::Type::Vehicle4].animations[DynamicObjects::State::Drive].setRepeating(true);

	// set the vehicle5's data
	data[DynamicObjects::Type::Vehicle5].texture = TextureID::Vehicle5;
	data[DynamicObjects::Type::Vehicle5].textureRect = sf::IntRect(0, 52, 96, 44);
	data[DynamicObjects::Type::Vehicle5].isAlive = true;
	data[DynamicObjects::Type::Vehicle5].speed = -50.f;
									  
	data[DynamicObjects::Type::Vehicle5].animations[DynamicObjects::State::Drive].addFrame(sf::IntRect(0, 52, 96, 44));
	data[DynamicObjects::Type::Vehicle5].animations[DynamicObjects::State::Drive].setDuration(sf::seconds(1.f));
	data[DynamicObjects::Type::Vehicle5].animations[DynamicObjects::State::Drive].setRepeating(true);

	// set the vehicle6's data
	data[DynamicObjects::Type::Vehicle6].texture = TextureID::Vehicle6;
	data[DynamicObjects::Type::Vehicle6].textureRect = sf::IntRect(0, 33, 94, 61);
	data[DynamicObjects::Type::Vehicle6].isAlive = true;
	data[DynamicObjects::Type::Vehicle6].speed = -50.f;
									  
	data[DynamicObjects::Type::Vehicle6].animations[DynamicObjects::State::Drive].addFrame(sf::IntRect(0, 33, 94, 61));
	data[DynamicObjects::Type::Vehicle6].animations[DynamicObjects::State::Drive].setDuration(sf::seconds(1.f));
	data[DynamicObjects::Type::Vehicle6].animations[DynamicObjects::State::Drive].setRepeating(true);

	return data;
}

std::map<GEX::StaticObjects::Type, GEX::StaticObjectData> GEX::initializeStaticObjectsData()
{
	std::map<StaticObjects::Type, StaticObjectData> data;

	// set the signpost's data
	data[StaticObjects::Type::SignPost].texture = TextureID::SignPost;
	data[StaticObjects::Type::SignPost].textureRect = sf::IntRect(0,0,50,49);

	// set the bunker's data
	data[StaticObjects::Type::Bunker].texture = TextureID::Bunker;
	data[StaticObjects::Type::Bunker].textureRect = sf::IntRect(0, 0, 53, 70);

	return data;
}

std::vector<GEX::SpawnData> GEX::initializeSpawnData()
{
	std::vector<SpawnData> data;

	// Spawn Data of 2nd road
	data.push_back(SpawnData());
	data[0].type = DynamicObjects::Type::Vehicle1;
	data[0].time = sf::milliseconds(17523);
	data[0].x = 10.f;
	data[0].y = 1405.f;
	data[0].speed = 55.f;

	// Spawn Data of 1st road
	data.push_back(SpawnData());
	data[1].type = DynamicObjects::Type::Vehicle6;
	data[1].time = sf::milliseconds(13757);
	data[1].x = 2038.f;
	data[1].y = 1455.f;
	data[1].speed = -55.f;

	//  Spawn Data of 5th road
	data.push_back(SpawnData());
	data[2].type = DynamicObjects::Type::Vehicle3;
	data[2].time = sf::milliseconds(13854);
	data[2].x = 10.f;
	data[2].y = 232.f;
	data[2].speed = 50.f;

	// Spawn Data of 4th road
	data.push_back(SpawnData());
	data[3].type = DynamicObjects::Type::Vehicle5;
	data[3].time = sf::milliseconds(13854);
	data[3].x = 2038.f;
	data[3].y = 740.f;
	data[3].speed = -40.f;



	return data;
}

