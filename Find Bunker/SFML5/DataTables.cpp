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

std::map<GEX::Actor::Type, GEX::ActorData> GEX::initializeActorData()
{
	std::map<Actor::Type, ActorData> data;

	data[Actor::Type::Hero2].texture = TextureID::Hero2;
	data[Actor::Type::Hero2].hitpoints = 100;
	data[Actor::Type::Hero2].speed = 50;

	JsonFrameParser frames = JsonFrameParser("Media/Textures/ke2.json");

	data[Actor::Type::Hero2].animations[Actor::State::Down].addFrameSet(frames.getFramesFor("down"));
	data[Actor::Type::Hero2].animations[Actor::State::Down].setDuration(sf::seconds(1.f));
	data[Actor::Type::Hero2].animations[Actor::State::Down].setRepeating(true);

	data[Actor::Type::Hero2].animations[Actor::State::Up].addFrameSet(frames.getFramesFor("up"));
	data[Actor::Type::Hero2].animations[Actor::State::Up].setDuration(sf::seconds(1.f));
	data[Actor::Type::Hero2].animations[Actor::State::Up].setRepeating(true);

	data[Actor::Type::Hero2].animations[Actor::State::Right].addFrameSet(frames.getFramesFor("right"));
	data[Actor::Type::Hero2].animations[Actor::State::Right].setDuration(sf::seconds(1.f));
	data[Actor::Type::Hero2].animations[Actor::State::Right].setRepeating(true);

	data[Actor::Type::Hero2].animations[Actor::State::Left].addFrameSet(frames.getFramesFor("left"));
	data[Actor::Type::Hero2].animations[Actor::State::Left].setDuration(sf::seconds(1.f));
	data[Actor::Type::Hero2].animations[Actor::State::Left].setRepeating(true);

	return data;
}