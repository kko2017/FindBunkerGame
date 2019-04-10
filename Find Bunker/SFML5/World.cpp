/**
* @file
* World.cpp
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

#include "World.h"
#include "DataTables.h"
#include "SoundNode.h"
#include "TextNode.h"

#include <random>

namespace GEX 
{
	// Each container has the spawn data and the spawn block data
	namespace 
	{
		const std::vector<SpawnData> TABLE = initializeSpawnData();
		const std::vector<SpawnBlockData> TABLE2 = initializeSpawnBlockData();
	}

	// Create Random Engine
	namespace 
	{
		std::random_device rn;
		std::mt19937_64 rnd(rn());
		const int MIN = 0;
		const int MAX = 7;
		std::uniform_int_distribution<int> range(MIN, MAX);
		int randomNumber = 0;
	}

	World::World(sf::RenderTarget& outputTarget, SoundPlayer& sounds)
		: target_(outputTarget)
		, worldView_(outputTarget.getDefaultView())
		, textures_()
		, sounds_(sounds)
		, sceneGraph_()
		, sceneLayers_()
		, worldBounds_(0.f, 0.f, worldView_.getSize().x, worldView_.getSize().y)
		, character_(nullptr)
		, signpost_(nullptr)
		, key_(nullptr)
		, lives_(2)
		, gameTime_(sf::seconds(35))
		, winGame_(false)
		, isKey_(false)
		, grabKey_(false)
	{
		sceneTexture_.create(target_.getSize().x, target_.getSize().y);

		for (unsigned int i = 0; i < TABLE.size(); i++)
		{
			spawningTime_.push_back(TABLE.at(i).time);
			elapsedSpawningTime_.push_back(TABLE.at(i).time);
		}

		loadTextures();
		buildScene();
	}

	void World::update(sf::Time dt, CommandQueue& commands)
	{
		updateTimer(dt);

		if (!character_->isDestroyed())
		{
			checkGameTimeOver();
			character_->setVelocity(0.f, 0.f);

			destroyEntitiesOutOfView();
			handleCollisions();

			//run all the commands in the command queue
			while (!commandQueue_.isEmpty()) 
			{
				sceneGraph_.onCommand(commandQueue_.pop(), dt);
			}

			adaptPlayerPosition();
			adaptPlayerVelocity();

			addVehicles(dt);
			spawnVehicles();

			updateText();

			sceneGraph_.update(dt, commands);
			sceneGraph_.removeWrecks();
		}		
	}

	void World::adaptPlayerVelocity() {
		sf::Vector2f velocity = character_->getVelocity();
		if (velocity.x != 0.f && velocity.y != 0.f) 
		{
			character_->setVelocity(velocity / std::sqrt(2.f));
		}
	}

	// Add a vehicle in the specific position.
	void World::addVehicle(DynamicObjects::Type type, float x, float y, float speed)
	{
		SpawnPoint spawnPoint(type, x, y, speed);
		vehicleSpawnPointes_.push_back(spawnPoint);
	}

	void World::addCharacter()
	{
		std::unique_ptr<DynamicObjects> character(new DynamicObjects(DynamicObjects::Type::Character, textures_));
		character->setPosition(worldView_.getSize().x / 2.f, (worldView_.getSize().y));
		character_ = character.get();
		sceneLayers_[UpperField]->attachChild(std::move(character));
	}

	void World::addSignpost()
	{
		std::unique_ptr<StaticObjects> signPost(new StaticObjects(StaticObjects::Type::Signpost, textures_));

		randomNumber = range(rnd);
		randomNums_.push_back(randomNumber);
		float xPosition = signPost->getObjectPosition()[randomNumber].first;
		float yPosition = signPost->getObjectPosition()[randomNumber].second;

		signPost->setPosition(xPosition, yPosition);
		signpost_ = signPost.get();
		sceneLayers_[UpperField]->attachChild(std::move(signPost));
	}

	// Add vehicles in each position.
	void World::addVehicles(sf::Time dt)
	{
		for (unsigned int i = 0; i < spawningTime_.size(); i++)
		{
			elapsedSpawningTime_.at(i) += dt;

			if (spawningTime_.at(i) <= elapsedSpawningTime_.at(i))
			{
				addVehicle(TABLE.at(i).type, TABLE.at(i).x, TABLE.at(i).y, TABLE.at(i).speed);
				elapsedSpawningTime_.at(i) -= spawningTime_.at(i);
			}
		}
	}

	void World::spawnVehicles()
	{
		while (!vehicleSpawnPointes_.empty())
		{
			auto spawnPoint = vehicleSpawnPointes_.back();
			std::unique_ptr<DynamicObjects> vehicles(new DynamicObjects(spawnPoint.type, textures_));

			vehicles->setPosition(spawnPoint.x, spawnPoint.y);
			vehicles->setVelocity(spawnPoint.speed, 0.f);

			sceneLayers_[LowerField]->attachChild(std::move(vehicles));
			vehicleSpawnPointes_.pop_back();
		}
	}

	void World::addBunker(StaticObjects::Type type)
	{
		std::unique_ptr<StaticObjects> bunker(new StaticObjects(type, textures_));

		randomNumber = range(rnd);
		unsigned int i = 0;
		while (i < randomNums_.size())
		{
			if (randomNums_[i] != randomNumber)
			{
				i++;
			}
			else
			{
				randomNumber = range(rnd);
				i = 0;
			}
		}
		randomNums_.push_back(randomNumber);

		float x = bunker->getObjectPosition()[randomNumber].first;
		float y = bunker->getObjectPosition()[randomNumber].second;

		bunker->setPosition(x, y);
		sceneLayers_[LowerField]->attachChild(std::move(bunker));
	}

	void World::addBunkers()
	{
		addBunker(StaticObjects::Type::Bunker);
		addBunker(StaticObjects::Type::Bunker);
	}

	void World::addKey(StaticObjects::Type type)
	{
		std::unique_ptr<StaticObjects> key(new StaticObjects(type, textures_));

		randomNumber = range(rnd);
		float x = key->getObjectPosition()[randomNumber].first;
		float y = key->getObjectPosition()[randomNumber].second;

		key->setPosition(x, y);
		key_ = key.get();
		sceneLayers_[UpperField]->attachChild(std::move(key));
	}

	void World::addBlock(StaticObjects::Type type, float x, float y)
	{
		BlockPoint blockPoint(type, x, y);
		blockSpawnPointes_.push_back(blockPoint);
	}

	void World::addBlocks()
	{
		for (unsigned int i = 0; i < TABLE2.size(); i++)
		{
			addBlock(TABLE2.at(i).type, TABLE2.at(i).x, TABLE2.at(i).y);
		}
	}

	void World::spawnBlocks()
	{
		while (!blockSpawnPointes_.empty())
		{
			auto blockPoint = blockSpawnPointes_.back();
			std::unique_ptr<StaticObjects> block(new StaticObjects(blockPoint.type, textures_));
			block->setPosition(blockPoint.x, blockPoint.y);
			sceneLayers_[Behind]->attachChild(std::move(block));
			blockSpawnPointes_.pop_back();
		}
	}

	void World::addBoys(DynamicObjects::Type type)
	{
		std::unique_ptr<DynamicObjects> boy1(new DynamicObjects(DynamicObjects::Type::Boy, textures_));
		boy1->setPosition(1255.f, 170.f);
		sceneLayers_[LowerField]->attachChild(std::move(boy1));

		std::unique_ptr<DynamicObjects> boy2(new DynamicObjects(DynamicObjects::Type::Boy, textures_));
		boy2->setPosition(985.f, 930.f);
		sceneLayers_[UpperField]->attachChild(std::move(boy2));
	}

	void World::addGirls(DynamicObjects::Type type)
	{
		std::unique_ptr<DynamicObjects> girl1(new DynamicObjects(DynamicObjects::Type::Girl, textures_));
		girl1->setPosition(600.f, 680.f);
		sceneLayers_[LowerField]->attachChild(std::move(girl1));

		std::unique_ptr<DynamicObjects> girl2(new DynamicObjects(DynamicObjects::Type::Girl, textures_));
		girl2->setPosition(1720.f, 1150.f);
		sceneLayers_[LowerField]->attachChild(std::move(girl2));
	}

	void World::addPoliceOfficers(DynamicObjects::Type type)
	{
		std::unique_ptr<DynamicObjects> police1(new DynamicObjects(DynamicObjects::Type::Police, textures_));
		police1->setPosition(230.f, 500.f);
		sceneLayers_[LowerField]->attachChild(std::move(police1));

		std::unique_ptr<DynamicObjects> police2(new DynamicObjects(DynamicObjects::Type::Police, textures_));
		police2->setPosition(1610.f, 500.f);
		sceneLayers_[LowerField]->attachChild(std::move(police2));
	}

	sf::FloatRect World::getViewBounds() const
	{
		return sf::FloatRect(worldView_.getCenter() - (worldView_.getSize() / 2.f), worldView_.getSize());
	}

	sf::FloatRect World::getFieldBounds() const
	{
		sf::FloatRect bounds = getViewBounds();
		bounds.top += 100.f;						
		bounds.height -= 100.f;					

		return bounds;
	}

	void World::updateTimer(sf::Time dt)
	{
		gameTime_ -= dt;
	}

	void World::checkGameTimeOver()
	{
		if (gameTime_ <= sf::Time::Zero)
		{
			character_->destroy();
			character_->playLocalSound(commandQueue_, SoundEffectID::CharacterDead);
			lives_ = 0;
			isKey_ = false;
		}
	}

	void World::updateText()
	{
		textGameTimeAndLives_->setText("Lives: " + std::to_string(lives_)
			+ "     Time: " + std::to_string(static_cast<int>(gameTime_.asSeconds()))
		);
		textGameTimeAndLives_->setPosition(250.f, 50.f);
	}

	void World::updateSounds()
	{
		sounds_.setListnerPosition(character_->getWorldPosition());
		sounds_.removeStoppedSounds();
	}

	void World::destroyEntitiesOutOfView()
	{
		Command command;
		command.category = Category::Type::Vehicle;
		command.action = derivedAction<Entity>([this](Entity& e, sf::Time dt)
		{
			if (e.getBoundingBox().width >= 0 && !getFieldBounds().intersects(e.getBoundingBox()))
				e.remove();
		});
		commandQueue_.push(command);
	}

	bool World::matchesCategories(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2)
	{
		unsigned int category1 = colliders.first->getCategory();
		unsigned int category2 = colliders.second->getCategory();

		// If 1st category first hit to 2nd category, it works.
		if (type1 & category1 && type2 & category2) {		
			return true;
		}
		// If 2nd category first hit to 1st category, it works.
		else if (type1 & category2 && type2 & category1) {	
			std::swap(colliders.first, colliders.second);
			return true;
		}
		else {
			return false;
		}
	}

	void World::noPassing(SceneNode::Pair & colliders)
	{
		auto& firstObject = static_cast<DynamicObjects&>(*(colliders.first));
		auto& secondObject = static_cast<StaticObjects&>(*(colliders.second));

		auto sPos = secondObject.getPosition();
		auto fPos = firstObject.getPosition();

		auto diffPos = sPos - fPos;
		secondObject.setPosition(sPos);
		firstObject.setPosition(fPos - 0.05f * diffPos);
	}

	void World::handleBlockCollision(SceneNode::Pair & colliders, Category::Type type1, Category::Type type2)
	{
		if (matchesCategories(colliders, type1, type2))
		{
			noPassing(colliders);
		}
	}

	void World::handleSignpostCollision(SceneNode::Pair & colliders, Category::Type type1, Category::Type type2)
	{
		if (matchesCategories(colliders, type1, type2))
		{
			noPassing(colliders);
			character_->playLocalSound(commandQueue_, SoundEffectID::GetSignpost);
			addBunkers();
			signpost_->destroy();
		}
	}

	void World::handleVehicleCollision(SceneNode::Pair & colliders, Category::Type type1, Category::Type type2)
	{
		if (matchesCategories(colliders, type1, type2))
		{
			noPassing(colliders);
			character_->destroy();
			character_->playLocalSound(commandQueue_, SoundEffectID::CharacterDead);
			lives_--;
			if (lives_ == 0)
			{
				isKey_ = false;
			}
		}
	}

	void World::handleBunkerCollision(SceneNode::Pair & colliders, Category::Type type1, Category::Type type2)
	{
		if (matchesCategories(colliders, type1, type2))
		{
			if (grabKey_ == true)
			{
				character_->playLocalSound(commandQueue_, SoundEffectID::OpenBunker);
				winGame_ = true;
			}

			noPassing(colliders);
			if (isKey_ == false)
			{
				character_->playLocalSound(commandQueue_, SoundEffectID::KnockBunker);
				addKey(StaticObjects::Type::Key);
				isKey_ = true;
			}			
		}
	}

	void World::handleKeyCollision(SceneNode::Pair & colliders, Category::Type type1, Category::Type type2)
	{
		if (matchesCategories(colliders, type1, type2))
		{
			key_->destroy();
			character_->playLocalSound(commandQueue_, SoundEffectID::GetKey);
			grabKey_ = true;
		}
	}

	void World::handlePeopleCollision(SceneNode::Pair & colliders, Category::Type type1, Category::Type type2)
	{
		if (matchesCategories(colliders, type1, type2))
		{
			noPassing(colliders);
		}
	}

	void World::handleCollisions()
	{
		// build a list of colliding pairs of SceneNodes
		std::set<SceneNode::Pair> collisionPairs;
		sceneGraph_.checkSceneCollision(sceneGraph_, collisionPairs);

		for (SceneNode::Pair pair : collisionPairs) {
			handleBlockCollision(pair, Category::Type::Character, Category::Type::Block);
			handleSignpostCollision(pair, Category::Type::Character, Category::Type::Signpost);
			handleVehicleCollision(pair, Category::Type::Character, Category::Type::Vehicle);
			handleBunkerCollision(pair, Category::Type::Character, Category::Type::Bunker);
			handleKeyCollision(pair, Category::Type::Character, Category::Type::Key);
			handlePeopleCollision(pair, Category::Type::Character, Category::Type::People);
		}
	}

	void World::adaptPlayerPosition() {

		const float BORDER_DISTANCE = 20.f;
		sf::FloatRect viewBounds(worldView_.getCenter() - worldView_.getSize() / 2.f, worldView_.getSize());

		sf::Vector2f position = character_->getPosition();
		position.x = std::max(position.x, viewBounds.left + BORDER_DISTANCE);
		position.x = std::min(position.x, viewBounds.left + viewBounds.width - BORDER_DISTANCE);

		position.y = std::max(position.y, viewBounds.top + BORDER_DISTANCE);
		position.y = std::min(position.y, viewBounds.top + viewBounds.height - BORDER_DISTANCE);

		character_->setPosition(position);
	}

	void World::draw()
	{
		target_.setView(worldView_);
		target_.draw(sceneGraph_);
	}

	CommandQueue & World::getCommandQueue()
	{
		return commandQueue_;
	}

	int World::getLives()
	{
		return lives_;
	}

	int World::getFinalElapsedTime()
	{
		int elapsedTime = static_cast<int>(gameTime_.asSeconds());
		return 35 - elapsedTime;
	}

	bool World::hasAlivePlayer() const
	{
		return (!character_->isDestroyed() && !character_->finishedDeadAnimation());
	}

	bool World::winGame() const
	{
		return winGame_;
	}

	void World::loadTextures() {
		textures_.load(GEX::TextureID::City1, "Media/Textures/City1.png");
		textures_.load(GEX::TextureID::Character, "Media/Textures/ke2.png");
		textures_.load(GEX::TextureID::SignPost, "Media/Textures/SignPost.png");
		textures_.load(GEX::TextureID::Bunker, "Media/Textures/Bunker.png");
		textures_.load(GEX::TextureID::RedCarToRight, "Media/Textures/redcar2.png");
		textures_.load(GEX::TextureID::WhiteCarToRight, "Media/Textures/whitecar2.png");
		textures_.load(GEX::TextureID::TruckToRight, "Media/Textures/truck2.png");
		textures_.load(GEX::TextureID::RedCarToLeft, "Media/Textures/redcar.png");
		textures_.load(GEX::TextureID::WhiteCarToLeft, "Media/Textures/whitecar.png");
		textures_.load(GEX::TextureID::TruckToLeft, "Media/Textures/truck.png");
		textures_.load(GEX::TextureID::BusToLeft, "Media/Textures/bus2.png");
		textures_.load(GEX::TextureID::Block, "Media/Textures/Block1.jpg");
		textures_.load(GEX::TextureID::Key, "Media/Textures/key.png");
		textures_.load(GEX::TextureID::Boy, "Media/Textures/boy.png");	
		textures_.load(GEX::TextureID::Girl, "Media/Textures/girl.png");	
		textures_.load(GEX::TextureID::Police, "Media/Textures/policeman.png");	
	}
	
	void World::buildScene() {
		// Initalize layers
		for (int i = 0; i < LayerCount; ++i) {
			auto category = (i == UpperField) ? Category::Type::Scene : Category::Type::None;
			SceneNode::Ptr layer(new SceneNode(category));
			sceneLayers_.push_back(layer.get());						
			sceneGraph_.attachChild(std::move(layer));
		}

		//Sound Effects
		std::unique_ptr<SoundNode> sNode(new SoundNode(sounds_));
		sceneGraph_.attachChild(std::move(sNode));

		// Background
		sf::Texture& texture = textures_.get(TextureID::City1);
		sf::IntRect textureRect(worldBounds_);						

		std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
		backgroundSprite->setPosition(worldBounds_.left, worldBounds_.top);
		sceneLayers_[Background]->attachChild(std::move(backgroundSprite));

		// Text for displaying game time and lives
		std::unique_ptr<TextNode> text(new TextNode(""));
		textGameTimeAndLives_ = text.get();
		sceneGraph_.attachChild(std::move(text));

		// add blocks
		addBlocks();
		spawnBlocks();

		// add character object
		addCharacter();

		// add SignPost
		addSignpost();		

		// add People
		addBoys(DynamicObjects::Type::Boy);
		addGirls(DynamicObjects::Type::Girl);
		addPoliceOfficers(DynamicObjects::Type::Police);
	}
}


