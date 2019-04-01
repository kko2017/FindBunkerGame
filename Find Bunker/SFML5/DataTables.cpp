#include "DataTables.h"
#include "JsonFrameParser.h"
#include "Animation2.h"


std::map<GEX::Projectile::Type, GEX::ProjectileData> GEX::initializeProjectileData()
{
	std::map<Projectile::Type, ProjectileData>data;
	//10.24
	data[Projectile::Type::AlliedBullet].damage = 10;
	data[Projectile::Type::AlliedBullet].speed = 300.f;
	data[Projectile::Type::AlliedBullet].texture = TextureID::Entities;
	data[Projectile::Type::AlliedBullet].textureRect = sf::IntRect(175, 64, 3, 14);

	data[Projectile::Type::EnemyBullet].damage = 10;
	data[Projectile::Type::EnemyBullet].speed = 300.f;
	data[Projectile::Type::EnemyBullet].texture = TextureID::Entities;
	data[Projectile::Type::EnemyBullet].textureRect = sf::IntRect(175, 64, 3, 14);

	data[Projectile::Type::Missile].damage = 30;
	data[Projectile::Type::Missile].speed = 200.f;
	data[Projectile::Type::Missile].texture = TextureID::Entities;
	data[Projectile::Type::Missile].textureRect = sf::IntRect(160, 64, 15, 24);

	return data;
}


//10.24
std::map<GEX::Particle::Type, GEX::ParticleData> GEX::initializeParticleData()
{
	std::map<GEX::Particle::Type, GEX::ParticleData> data;

	data[Particle::Type::Propellant].color = sf::Color(255, 255, 50);
	data[Particle::Type::Propellant].lifetime = sf::seconds(0.6f);

	data[Particle::Type::Smoke].color = sf::Color(50, 50, 50);
	data[Particle::Type::Smoke].lifetime = sf::seconds(4.f);

	return data;
	
}

std::map<GEX::DynamicObjects::Type, GEX::DynamicObjectsData> GEX::initializeDynamicObjectsData()
{
	std::map<DynamicObjects::Type, DynamicObjectsData> data;

	data[DynamicObjects::Type::Character].texture = TextureID::Character;
	data[DynamicObjects::Type::Character].isAlive = true;
	data[DynamicObjects::Type::Character].speed = 50;

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
													 
	return data;
}

std::map<GEX::StaticObjects::Type, GEX::StaticObjectData> GEX::initializeStaticObjectsData()
{
	std::map<StaticObjects::Type, StaticObjectData> data;

	data[StaticObjects::Type::SignPost].texture = TextureID::SignPost;
	data[StaticObjects::Type::SignPost].textureRect = sf::IntRect(0,0,50,49);

	data[StaticObjects::Type::Bunker].texture = TextureID::Bunker;
	data[StaticObjects::Type::Bunker].textureRect = sf::IntRect(0, 0, 53, 70);

	return data;
}

