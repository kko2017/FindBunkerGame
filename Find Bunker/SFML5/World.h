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
		explicit							World(sf::RenderTarget& outputTarget, SoundPlayer& sounds);	// explicit constructor having RenderTarget and SoundPlayer by references  as a parameter

		void								update(sf::Time dt, CommandQueue& commands);				// update function controls world scrolling and entity movement
		void								draw();														// draw function sets the current view and delegates the work to SceneNode 
		CommandQueue&						getCommandQueue();											// getter function to access CommandQueue from outside the world

		void								addCharacter();												// add the charcter on the game
		int									getLives();													// getter for lives
		int									getFinalElapsedTime();										// getter for final elapsed time
		bool								hasAlivePlayer() const;										// check whether the player is alive
		bool								winGame() const;											// check that the player fulfills the condition of the win

	private:
		void								loadTextures();												// this function loads textures
		void								buildScene();												// this function builds scene
		void								adaptPlayerPosition();										// this function sets up the area that the player can move around
		void								adaptPlayerVelocity();										// this function sets the velocity of the player

		void								addSignpost();												// add signpost on the game
		void								addVehicles(sf::Time dt);									// add vehicles on the game
		void								addVehicle(DynamicObjects::Type type,						// add a vehicle on the game
														float x, float y, float speed);
		void								spawnVehicles();											// sapwn vehicles added on the specified position
		void								addBunker(StaticObjects::Type type);						// add a bunker on the game
		void								addBunkers();												// add bunkers on the game
		void								addKey(StaticObjects::Type type);							// add a key on the game 
		void								addBlock(StaticObjects::Type type, float x, float y);		// add a block on the game
		void								addBlocks();												// add blocks on the game
		void								spawnBlocks();												// spawn blocks added on the specified position
		void								addBoys(DynamicObjects::Type type);							// add boys on the game
		void								addGirls(DynamicObjects::Type type);						// add girls on the game
		void								addPoliceOfficers(DynamicObjects::Type type);				// add police officers on the game

		
		sf::FloatRect						getViewBounds() const;										// get the view bounds of the screen
		sf::FloatRect						getFieldBounds() const;										// get the field bounds
		
		bool								matchesCategories(SceneNode::Pair& colliders,				// checks that two objects collides with each other
															Category::Type type1, Category::Type type2);
		void								noPassing(SceneNode::Pair& colliders);						// method for the character to be unable to pass through objects
		void								handleBlockCollision(SceneNode::Pair& colliders,			// character is unable to pass through blocks
															Category::Type type1, Category::Type type2);
		void								handleSignpostCollision(SceneNode::Pair& colliders,			// bunkers are randomly generated after the character meets the signpost
															Category::Type type1, Category::Type type2);
		void								handleVehicleCollision(SceneNode::Pair& colliders,			// character is killed right after the character collided with the vehicle
															Category::Type type1, Category::Type type2);
		void								handleBunkerCollision(SceneNode::Pair& colliders,			// key is generated in random after the character without a key meets the bunker,
															Category::Type type1, Category::Type type2);// player wins the game after the character with a key meets the bunker
		void								handleKeyCollision(SceneNode::Pair& colliders,				// player has the key right after player reaches a key
															Category::Type type1, Category::Type type2);
		void								handlePeopleCollision(SceneNode::Pair& colliders,			// character is unable to pass through people
															Category::Type type1, Category::Type type2);
		void								handleCollisions();											// This method implemente all handle collisions.

		
		void								destroyEntitiesOutOfView();									// entities are removed once they are out of the screen
		void								updateTimer(sf::Time dt);									// update the timer
		void								checkGameTimeOver();										// checks whether time is over
		void								updateText();												// update the lives and timer text
		void								updateSounds();												// update the sound effect

	private:
		enum Layer {																					// scoped enumeration for a unique identifier in each layer
			Behind = 0,
			Background,
			LowerField,
			UpperField,
			LayerCount
		};

		struct SpawnPoint {																				// Struct holds the source of the spawanPoint
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

		struct BlockPoint {																				// Struct holds the source of the spawanPoint
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