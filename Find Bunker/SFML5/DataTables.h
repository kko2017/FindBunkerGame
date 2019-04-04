// 10.3
//

#pragma once
#include "TextureManager.h"
#include "DynamicObjects.h"
#include "StaticObjects.h"
#include "Particle.h"

#include <map>

//#include "Animation2.h"

namespace GEX {

	struct DynamicObjectsData {
		bool		isAlive;
		float		speed;
		TextureID	texture;
		sf::IntRect textureRect;

		std::map<DynamicObjects::State, Animation2> animations;
	};

	struct StaticObjectData {
		TextureID	texture;
		sf::IntRect textureRect;
	};

	struct SpawnData {
		DynamicObjects::Type type;
		sf::Time			 time;
		float				 xDeparture;
		float				 yDeparture;
		float				 xArrival;
		float				 yArrival;
	};

	struct ParticleData {

		sf::Color		color;
		sf::Time		lifetime;
	};
	std::map<Particle::Type, ParticleData>				initializeParticleData();

	std::map<DynamicObjects::Type, DynamicObjectsData>	initializeDynamicObjectsData();
	std::map<StaticObjects::Type, StaticObjectData>		initializeStaticObjectsData();
	std::vector<SpawnData>								initializeSpawnData();
}

