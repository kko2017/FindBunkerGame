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
	// forward declaration
	class SoundPlayer;
	class TextNode;

	class World
	{
	public:
		explicit							World(sf::RenderTarget& outputTarget, SoundPlayer& sounds);

		void								update(sf::Time dt, CommandQueue& commands);
		void								draw();
		CommandQueue&						getCommandQueue();

		void								addCharacter();
		int									getLives();
		int									getFinalElapsedTime();
		bool								hasAlivePlayer() const;
		bool								winGame() const;

	private:
		void								loadTextures();
		void								buildScene();
		void								adaptPlayerPosition();
		void								adaptPlayerVelocity();

		void								addSignpost();
		void								addVehicles(sf::Time dt);
		void								addVehicle(DynamicObjects::Type type, float x, float y, float speed);
		void								spawnVehicles();
		void								addBunker(StaticObjects::Type type);
		void								addBunkers();
		void								addKey(StaticObjects::Type type);
		void								addBlock(StaticObjects::Type type, float x, float y);
		void								addBlocks();
		void								spawnBlocks();
		
		sf::FloatRect						getViewBounds() const;
		sf::FloatRect						getFieldBounds() const;						
		
		bool								matchesCategories(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2);
		void								noPassing(SceneNode::Pair& colliders);
		void								handleBlockCollision(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2);
		void								handleSignpostCollision(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2);
		void								handleVehicleCollision(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2);
		void								handleBunkerCollision(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2);
		void								handleKeyCollision(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2);
		void								handleCollisions();

		
		void								destroyEntitiesOutOfView();
		void								updateTimer(sf::Time dt);
		void								checkGameTimeOver();
		void								updateText();
		void								updateSounds();

	private:
		enum Layer {
			Behind = 0,
			Background,
			LowerField,
			UpperField,
			LayerCount
		};

		struct SpawnPoint {
			SpawnPoint(DynamicObjects::Type _type, float _x, float _y, float _speed)
				: type(_type)
				, x(_x)
				, y(_y)
				, speed(_speed)
			{}
			DynamicObjects::Type type;
			float	x;
			float   y;
			float	speed;
		};

		struct BlockPoint {
			BlockPoint(StaticObjects::Type _type, float _x, float _y)
				: type(_type)
				, x(_x)
				, y(_y)
			{}
			StaticObjects::Type type;
			float	x;
			float	y;
		};

	private:

		sf::RenderTarget&					target_;
		sf::RenderTexture					sceneTexture_;
		sf::View							worldView_;			
		TextureManager						textures_;
		SoundPlayer&						sounds_;

		SceneNode							sceneGraph_;
		std::vector<SceneNode*>				sceneLayers_;		

		CommandQueue						commandQueue_;

		sf::FloatRect						worldBounds_;

		DynamicObjects*						character_;
		StaticObjects*						signpost_;
		StaticObjects*						key_;

		std::vector<SpawnPoint>				vehicleSpawnPointes_;
		std::vector<BlockPoint>				blockSpawnPointes_;

		std::vector<int>					randomNums_;
		std::vector<sf::Time>				spawningTime_;
		std::vector<sf::Time>				elapsedSpawningTime_;

		int									lives_;
		sf::Time							gameTime_;
		TextNode*							textGameTimeAndLives_;
		bool								winGame_;
		bool								isKey_;
		bool								grabKey_;
	};

}