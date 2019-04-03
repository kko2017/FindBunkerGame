// 10.3
//

#pragma once
#include "TextureManager.h"
#include "DynamicObjects.h"
#include "StaticObjects.h"
#include "Projectile.h"
#include "Particle.h"

#include <map>

//#include "Animation2.h"

namespace GEX {

	struct Direction {
		Direction(float a, float d)
			: angle(a)
			, distance(d) 
		{}

		float angle;
		float distance;
	};

	struct DynamicObjectsData {
		bool		isAlive;
		float		speed;
		TextureID	texture;
		sf::IntRect textureRect;

		std::map<DynamicObjects::State, Animation2> animations;
		std::vector<Direction> directions;
	};

	struct StaticObjectData {
		TextureID	texture;
		sf::IntRect textureRect;
	};

	struct SpawnData {
		DynamicObjects::Type type;
		sf::Time			 time;
		float				 x;
		float				 y;
	};

	struct ProjectileData {
		
		int			damage;
		float		speed;
		TextureID	texture;

		sf::IntRect textureRect;
	};

	struct ParticleData {

		sf::Color		color;
		sf::Time		lifetime;
	};

	std::map<Projectile::Type, ProjectileData>			initializeProjectileData();
	std::map<Particle::Type, ParticleData>				initializeParticleData();

	std::map<DynamicObjects::Type, DynamicObjectsData>	initializeDynamicObjectsData();
	std::map<StaticObjects::Type, StaticObjectData>		initializeStaticObjectsData();
	std::vector<SpawnData>								initializeSpawnData();
}

