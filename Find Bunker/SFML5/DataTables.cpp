#include "DataTables.h"
#include "JsonFrameParser.h"
#include "Animation2.h"


std::map<GEX::DynamicObjects::Type, GEX::DynamicObjectsData> GEX::initializeDynamicObjectsData()
{
	std::map<DynamicObjects::Type, DynamicObjectsData> data;

	// Set the character' data
	data[DynamicObjects::Type::Character].texture = TextureID::Character;

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

	data[DynamicObjects::Type::Character].animations[DynamicObjects::State::Dead].addFrameSet(frames.getFramesFor("dead"));
	data[DynamicObjects::Type::Character].animations[DynamicObjects::State::Dead].setDuration(sf::seconds(1.f));
	data[DynamicObjects::Type::Character].animations[DynamicObjects::State::Dead].setRepeating(false);



	// set the RedCarToRight's data
	data[DynamicObjects::Type::RedCarToRight].texture = TextureID::RedCarToRight;
	data[DynamicObjects::Type::RedCarToRight].textureRect = sf::IntRect(0,0,96,45);

	data[DynamicObjects::Type::RedCarToRight].animations[DynamicObjects::State::Drive].addFrame(sf::IntRect(0, 0, 96, 45));
	data[DynamicObjects::Type::RedCarToRight].animations[DynamicObjects::State::Drive].setDuration(sf::seconds(1.f));
	data[DynamicObjects::Type::RedCarToRight].animations[DynamicObjects::State::Drive].setRepeating(true);
	

	// set the WhiteCarToRight's data
	data[DynamicObjects::Type::WhiteCarToRight].texture = TextureID::WhiteCarToRight;
	data[DynamicObjects::Type::WhiteCarToRight].textureRect = sf::IntRect(0,0,95,44);


	data[DynamicObjects::Type::WhiteCarToRight].animations[DynamicObjects::State::Drive].addFrame(sf::IntRect(0, 0, 95, 44));
	data[DynamicObjects::Type::WhiteCarToRight].animations[DynamicObjects::State::Drive].setDuration(sf::seconds(1.f));
	data[DynamicObjects::Type::WhiteCarToRight].animations[DynamicObjects::State::Drive].setRepeating(true);

	// set the TruckToRight's data
	data[DynamicObjects::Type::TruckToRight].texture = TextureID::TruckToRight;
	data[DynamicObjects::Type::TruckToRight].textureRect = sf::IntRect(0, 0, 94, 61);

									  
	data[DynamicObjects::Type::TruckToRight].animations[DynamicObjects::State::Drive].addFrame(sf::IntRect(0, 0, 94, 61));
	data[DynamicObjects::Type::TruckToRight].animations[DynamicObjects::State::Drive].setDuration(sf::seconds(1.f));
	data[DynamicObjects::Type::TruckToRight].animations[DynamicObjects::State::Drive].setRepeating(true);

	// set the RedCarToLeft's data
	data[DynamicObjects::Type::RedCarToLeft].texture = TextureID::RedCarToLeft;
	data[DynamicObjects::Type::RedCarToLeft].textureRect = sf::IntRect(0,51,96,45);

									  
	data[DynamicObjects::Type::RedCarToLeft].animations[DynamicObjects::State::Drive].addFrame(sf::IntRect(0, 51, 96, 45));
	data[DynamicObjects::Type::RedCarToLeft].animations[DynamicObjects::State::Drive].setDuration(sf::seconds(1.f));
	data[DynamicObjects::Type::RedCarToLeft].animations[DynamicObjects::State::Drive].setRepeating(true);

	// set the WhiteCarToLeft's data
	data[DynamicObjects::Type::WhiteCarToLeft].texture = TextureID::WhiteCarToLeft;
	data[DynamicObjects::Type::WhiteCarToLeft].textureRect = sf::IntRect(0, 52, 96, 44);

									  
	data[DynamicObjects::Type::WhiteCarToLeft].animations[DynamicObjects::State::Drive].addFrame(sf::IntRect(0, 52, 96, 44));
	data[DynamicObjects::Type::WhiteCarToLeft].animations[DynamicObjects::State::Drive].setDuration(sf::seconds(1.f));
	data[DynamicObjects::Type::WhiteCarToLeft].animations[DynamicObjects::State::Drive].setRepeating(true);

	// set the TruckToLeft's data
	data[DynamicObjects::Type::TruckToLeft].texture = TextureID::TruckToLeft;
	data[DynamicObjects::Type::TruckToLeft].textureRect = sf::IntRect(0, 33, 94, 61);

									  
	data[DynamicObjects::Type::TruckToLeft].animations[DynamicObjects::State::Drive].addFrame(sf::IntRect(0, 33, 94, 61));
	data[DynamicObjects::Type::TruckToLeft].animations[DynamicObjects::State::Drive].setDuration(sf::seconds(1.f));
	data[DynamicObjects::Type::TruckToLeft].animations[DynamicObjects::State::Drive].setRepeating(true);

	// set the BusToLeft's data
	data[DynamicObjects::Type::BusToLeft].texture = TextureID::BusToLeft;
	data[DynamicObjects::Type::BusToLeft].textureRect = sf::IntRect(0, 0, 96, 67);

	data[DynamicObjects::Type::BusToLeft].animations[DynamicObjects::State::Drive].addFrame(sf::IntRect(0, 0, 96, 67));
	data[DynamicObjects::Type::BusToLeft].animations[DynamicObjects::State::Drive].setDuration(sf::seconds(1.f));
	data[DynamicObjects::Type::BusToLeft].animations[DynamicObjects::State::Drive].setRepeating(true);

	return data;
}

std::map<GEX::StaticObjects::Type, GEX::StaticObjectData> GEX::initializeStaticObjectsData()
{
	std::map<StaticObjects::Type, StaticObjectData> data;

	// set the signpost's data
	data[StaticObjects::Type::Signpost].texture = TextureID::SignPost;
	data[StaticObjects::Type::Signpost].textureRect = sf::IntRect(0,0,50,49);

	// set the bunker's data
	data[StaticObjects::Type::Bunker].texture = TextureID::Bunker;
	data[StaticObjects::Type::Bunker].textureRect = sf::IntRect(0, 0, 53, 70);

	// set the key's data
	data[StaticObjects::Type::Key].texture = TextureID::Key;
	data[StaticObjects::Type::Key].textureRect = sf::IntRect(0, 0, 50, 50);

	// set the block1's data
	data[StaticObjects::Type::Block1].texture = TextureID::Block;
	data[StaticObjects::Type::Block1].textureRect = sf::IntRect(0, 0, 350, 430);

	// set the block1's data
	data[StaticObjects::Type::Block2].texture = TextureID::Block;
	data[StaticObjects::Type::Block2].textureRect = sf::IntRect(0, 0, 245, 430);

	// set the block1's data
	data[StaticObjects::Type::Block3].texture = TextureID::Block;
	data[StaticObjects::Type::Block3].textureRect = sf::IntRect(0, 0, 657, 430);

	// set the block1's data
	data[StaticObjects::Type::Block4].texture = TextureID::Block;
	data[StaticObjects::Type::Block4].textureRect = sf::IntRect(0, 0, 130, 430);

	// set the block1's data
	data[StaticObjects::Type::Block5].texture = TextureID::Block;
	data[StaticObjects::Type::Block5].textureRect = sf::IntRect(0, 0, 150, 280);

	// set the block1's data
	data[StaticObjects::Type::Block6].texture = TextureID::Block;
	data[StaticObjects::Type::Block6].textureRect = sf::IntRect(0, 0, 500, 280);

	// set the block1's data
	data[StaticObjects::Type::Block7].texture = TextureID::Block;
	data[StaticObjects::Type::Block7].textureRect = sf::IntRect(0, 0, 550, 280);

	// set the block1's data
	data[StaticObjects::Type::Block8].texture = TextureID::Block;
	data[StaticObjects::Type::Block8].textureRect = sf::IntRect(0, 0, 390, 280);

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
	data[0].type = DynamicObjects::Type::RedCarToRight;
	data[0].time = sf::milliseconds(8000);
	data[0].x = 10.f;
	data[0].y = 1405.f;
	data[0].speed = 120.f;

	// Spawn Data of 1st road
	data.push_back(SpawnData());
	data[1].type = DynamicObjects::Type::WhiteCarToLeft;
	data[1].time = sf::milliseconds(8000);
	data[1].x = 2038.f;
	data[1].y = 1448.f;
	data[1].speed = -100.f;

	//  Spawn Data of 6th road
	data.push_back(SpawnData());
	data[2].type = DynamicObjects::Type::BusToLeft;
	data[2].time = sf::milliseconds(5000);
	data[2].x = 2038.f;
	data[2].y = 252.f;
	data[2].speed = -150.f;

	// Spawn Data of 4th road
	data.push_back(SpawnData());
	data[3].type = DynamicObjects::Type::TruckToLeft;
	data[3].time = sf::milliseconds(5000);
	data[3].x = 2038.f;
	data[3].y = 750.f;
	data[3].speed = -120.f;

	return data;
}

std::vector<GEX::SpawnBlockData> GEX::initializeSpawnBlockData()
{
	std::vector<SpawnBlockData> data;

	data.push_back(SpawnBlockData());
	data[0].type = StaticObjects::Type::Block1;
	data[0].x = 175.f;
	data[0].y = 1090.f;

	data.push_back(SpawnBlockData());
	data[1].type = StaticObjects::Type::Block2;
	data[1].x = 695.f;
	data[1].y = 1085.f;

	data.push_back(SpawnBlockData());
	data[2].type = StaticObjects::Type::Block3;
	data[2].x = 1360.f;
	data[2].y = 1085.f;

	data.push_back(SpawnBlockData());
	data[3].type = StaticObjects::Type::Block4;
	data[3].x = 1970.f;
	data[3].y = 1085.f;

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

