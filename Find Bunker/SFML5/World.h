//
// The game world
//

#pragma once
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <vector>

#include "SceneNode.h"
#include "SpriteNode.h"
#include "TextureManager.h"
#include "DynamicObjects.h"
#include "StaticObjects.h"
#include "CommandQueue.h"

// forward declaration
namespace sf {

	class RenderWindow;

}

namespace GEX {

	class World
	{
	public:
		explicit							World(sf::RenderWindow& window);

		void								update(sf::Time dt, CommandQueue& commands);
		void								draw();
		CommandQueue&						getCommandQueue();

		
		bool								hasAlivePlayer() const;
		bool								hasPlayerReachedEnd() const;

	private:
		void								loadTextures();
		void								buildScene();
		void								adaptPlayerPosition();
		void								adaptPlayerVelocity();
		
		void								addVehicles(sf::Time dt);
		void								addVehicle(DynamicObjects::Type type, float x, float y, float speed);
		void								spawnVehicles();
		void								addBunker(StaticObjects::Type type);
		void								addBunkers();
		
		sf::FloatRect						getViewBounds() const;								// for battle ground view
		sf::FloatRect						getBattlefieldBounds() const;						//	battle ground view
		
		void								handleCollisions();
		bool								matchesCategories(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2);

		
		void								destroyEntitiesOutOfView();

	private:
		enum Layer {
			Behind = 0,
			Background,
			LowerAir,
			UpperAir,
			LayerCount
		};

		// 10.10
		struct SpawnPoint {
			SpawnPoint(DynamicObjects::Type _type, float _x, float _y, float _speed)
				: type(_type)
				, x(_x)
				, y(_y)
				, speed(_speed)
			{}
			DynamicObjects::Type type;						// member variable is public so we don't need to add _ to the name
			float	x;
			float   y;
			float	speed;
		};

	private:
		sf::RenderWindow&					window_;
		sf::View							worldView_;			// my viewPort
		TextureManager						textures_;

		SceneNode							sceneGraph_;
		std::vector<SceneNode*>				sceneLayers_;		// it is the vector of a raw pointer

		CommandQueue						commandQueue_;

		sf::FloatRect						worldBounds_;

		DynamicObjects*						character_;
		StaticObjects*						signPost_;

		std::vector<SpawnPoint>				vehicleSpawnPointes_;

		std::vector<int>					randomNums_;
		std::vector<sf::Time>				spawningTime_;
		std::vector<sf::Time>				elapsedSpawningTime_;
	};

}