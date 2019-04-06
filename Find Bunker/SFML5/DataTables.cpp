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

	// set the block1's data
	data[StaticObjects::Type::Block1].texture = TextureID::Block;
	data[StaticObjects::Type::Block1].textureRect = sf::IntRect(0, 0, 350, 450);

	// set the block1's data
	data[StaticObjects::Type::Block2].texture = TextureID::Block;
	data[StaticObjects::Type::Block2].textureRect = sf::IntRect(0, 0, 245, 450);

	// set the block1's data
	data[StaticObjects::Type::Block3].texture = TextureID::Block;
	data[StaticObjects::Type::Block3].textureRect = sf::IntRect(0, 0, 657, 450);

	// set the block1's data
	data[StaticObjects::Type::Block4].texture = TextureID::Block;
	data[StaticObjects::Type::Block4].textureRect = sf::IntRect(0, 0, 130, 450);

	// set the block1's data
	data[StaticObjects::Type::Block5].texture = TextureID::Block;
	data[StaticObjects::Type::Block5].textureRect = sf::IntRect(0, 0, 150, 300);

	// set the block1's data
	data[StaticObjects::Type::Block6].texture = TextureID::Block;
	data[StaticObjects::Type::Block6].textureRect = sf::IntRect(0, 0, 500, 300);

	// set the block1's data
	data[StaticObjects::Type::Block7].texture = TextureID::Block;
	data[StaticObjects::Type::Block7].textureRect = sf::IntRect(0, 0, 550, 300);

	// set the block1's data
	data[StaticObjects::Type::Block8].texture = TextureID::Block;
	data[StaticObjects::Type::Block8].textureRect = sf::IntRect(0, 0, 390, 300);

	// set the block1's data
	data[StaticObjects::Type::Block9].texture = TextureID::Block;
	data[StaticObjects::Type::Block9].textureRect = sf::IntRect(0, 0, 800, 137);

	// set the block1's data
	data[StaticObjects::Type::Block10].texture = TextureID::Block;
	data[StaticObjects::Type::Block10].textureRect = sf::IntRect(0, 0, 400, 137);

	// set the block1's data
	data[StaticObjects::Type::Block11].texture = TextureID::Block;
	data[StaticObjects::Type::Block11].textureRect = sf::IntRect(0, 0, 400, 137);

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

std::vector<GEX::SpawnBlockData> GEX::initializeSpawnBlockData()
{
	std::vector<SpawnBlockData> data;

	data.push_back(SpawnBlockData());
	data[0].type = StaticObjects::Type::Block1;
	data[0].x = 175.f;
	data[0].y = 1100.f;

	data.push_back(SpawnBlockData());
	data[1].type = StaticObjects::Type::Block2;
	data[1].x = 695.f;
	data[1].y = 1100.f;

	data.push_back(SpawnBlockData());
	data[2].type = StaticObjects::Type::Block3;
	data[2].x = 1360.f;
	data[2].y = 1100.f;

	data.push_back(SpawnBlockData());
	data[3].type = StaticObjects::Type::Block4;
	data[3].x = 1970.f;
	data[3].y = 1100.f;

	data.push_back(SpawnBlockData());
	data[4].type = StaticObjects::Type::Block5;
	data[4].x = 23.f;
	data[4].y = 510.f;

	data.push_back(SpawnBlockData());
	data[5].type = StaticObjects::Type::Block6;
	data[5].x = 563.f;
	data[5].y = 510.f;

	data.push_back(SpawnBlockData());
	data[6].type = StaticObjects::Type::Block7;
	data[6].x = 1153.f;
	data[6].y = 510.f;

	data.push_back(SpawnBlockData());
	data[7].type = StaticObjects::Type::Block8;
	data[7].x = 1845.f;
	data[7].y = 510.f;

	data.push_back(SpawnBlockData());
	data[8].type = StaticObjects::Type::Block9;
	data[8].x = 410.f;
	data[8].y = 77.f;

	data.push_back(SpawnBlockData());
	data[9].type = StaticObjects::Type::Block10;
	data[9].x = 1230.f;
	data[9].y = 77.f;

	data.push_back(SpawnBlockData());
	data[10].type = StaticObjects::Type::Block11;
	data[10].x = 1845.f;
	data[10].y = 77.f;

	return data;
}

