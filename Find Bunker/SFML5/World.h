//
// The game world
//

#pragma once
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "SceneNode.h"
#include "SpriteNode.h"
#include "TextureManager.h"
#include "Actor.h"
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

		//10.22
		bool								hasAlivePlayer() const;
		bool								hasPlayerReachedEnd() const;

	private:
		void								loadTextures();
		void								buildScene();
		void								adaptPlayerPosition();
		void								adaptPlayerVelocity();
		
		//10.10
		void								addEnemies();										// add spawnPoints of enemies
		void								addEnemy(Actor::Type type, float relX, float relY);
		void								spawnEnemies();										// call this in the my update function to the spawn point
		//10.10
		sf::FloatRect						getViewBounds() const;								// for battle ground view
		sf::FloatRect						getBattlefieldBounds() const;						//	battle ground view
		//10.18
		void								handleCollisions();
		bool								matchesCategories(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2);

		//10.22
		void								destroyEntitiesOutOfView();

	private:
		enum Layer {
			Background = 0,
			//10.25
			LowerAir,
			UpperAir,
			LayerCount
		};

		// 10.10
		struct SpawnPoint {
			SpawnPoint(Actor::Type _type, float _x, float _y)
				: type(_type)
				, x(_x)
				, y(_y)
			{}
			Actor::Type type;						// member variable is public so we don't need to add _ to the name
			float	x;
			float   y;
		};

	private:

		// you must declare things(fields?) in order
		// because if those are scrambled, a bug happens and then it is extremely hard to find and fix it.

		sf::RenderWindow&					window_;
		sf::View							worldView_;			// my viewPort
		TextureManager						textures_;

		SceneNode							sceneGraph_;
		std::vector<SceneNode*>				sceneLayers_;		// it is the vector of a raw pointer

		//9.24
		CommandQueue						commandQueue_;


		sf::FloatRect						worldBounds_;
		sf::Vector2f						spawnPosition_;

		float								scrollSpeed_;

		Actor*								playerAircraft_;

		//10.10
		std::vector<SpawnPoint>				enemySpawnPointes_;
	};

}