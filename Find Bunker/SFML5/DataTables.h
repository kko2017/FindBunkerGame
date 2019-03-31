// 10.3
//

#pragma once
#include "TextureManager.h"
#include "Actor.h"
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

	struct ActorData {
		int			hitpoints;
		int			damageDone;
		float		speed;
		TextureID	texture;

		std::map<Actor::State, Animation2> animations;
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

	std::map<Actor::Type, ActorData> initializeActorData();
	
}

