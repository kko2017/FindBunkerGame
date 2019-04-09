#pragma once
#include "TextureManager.h"
#include "DynamicObjects.h"
#include "StaticObjects.h"

#include <map>

namespace GEX {

	struct DynamicObjectsData {
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
		float				 x;
		float				 y;
		float				 speed;
	};

	struct SpawnBlockData {
		StaticObjects::Type type;
		float				x;
		float				y;
	};

	std::map<DynamicObjects::Type, DynamicObjectsData>	initializeDynamicObjectsData();
	std::map<StaticObjects::Type, StaticObjectData>		initializeStaticObjectsData();
	std::vector<SpawnData>								initializeSpawnData();
	std::vector<SpawnBlockData>							initializeSpawnBlockData();
}

