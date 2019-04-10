/**
* @file
* World.h
* @author
* Kwangeun Oh
* @version 1.0
*
*
* @DESCRIPTION
* This is the Find Bunker game
*
* @section LICENSE
*
*
* Copyright 2019
* Permission to use, copy, modify, and/or distribute this software for
* any purpose with or without fee is hereby granted, provided that the
* above copyright notice and this permission notice appear in all copies.
*
* THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
* WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
* ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
* WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
* ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
* OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*
* @section Academic Integrity
* I certify that this work is solely my own and complies with
* NBCC Academic Integrity Policy (policy 1111)
*/


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
		void								addBoys(DynamicObjects::Type type);
		void								addGirls(DynamicObjects::Type type);
		void								addPoliceOfficers(DynamicObjects::Type type);

		
		sf::FloatRect						getViewBounds() const;
		sf::FloatRect						getFieldBounds() const;						
		
		bool								matchesCategories(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2);
		void								noPassing(SceneNode::Pair& colliders);
		void								handleBlockCollision(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2);
		void								handleSignpostCollision(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2);
		void								handleVehicleCollision(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2);
		void								handleBunkerCollision(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2);
		void								handleKeyCollision(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2);
		void								handlePeopleCollision(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2);
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