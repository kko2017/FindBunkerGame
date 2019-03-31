// 10.3
//

#pragma once
#include "TextureManager.h"
#include "DynamicObjects.h"
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

		std::map<DynamicObjects::State, Animation2> animations;
		std::vector<Direction> directions;
	};

	struct ProjectileData {
		
		int			damage;
		float		speed;
		TextureID	texture;
		//10.24
		sf::IntRect textureRect;
	};

	struct ParticleData {

		sf::Color		color;
		sf::Time		lifetime;
	};

	std::map<Projectile::Type, ProjectileData> initializeProjectileData();
	std::map<Particle::Type, ParticleData> initializeParticleData();

	std::map<DynamicObjects::Type, DynamicObjectsData> initializeDynamicObjectsData();	
}

