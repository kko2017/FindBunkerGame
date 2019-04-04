#include "World.h"
#include "ParticleNode.h"
#include "DataTables.h"

#include <random>

namespace GEX {

	// Set the spawn data
	namespace {
		const std::vector<SpawnData> TABLE = initializeSpawnData();
	}

	// Create Random Engine
	namespace {
		std::random_device rn;
		std::mt19937_64 rnd(rn());
		const int MIN = 0;
		const int MAX = 7;
		std::uniform_int_distribution<int> range(MIN, MAX);
		int randomNumber = 0;
	}

	World::World(sf::RenderWindow& window)
		: window_(window)
		, worldView_(window.getDefaultView())
		, textures_()
		, sceneGraph_()
		, sceneLayers_()
		, worldBounds_(0.f, 0.f, worldView_.getSize().x, worldView_.getSize().y)
		, character_(nullptr)
		, signPost_(nullptr)
	{
		for (int i = 0; i < TABLE.size(); i++)
		{
			spawningTime_.push_back(TABLE.at(i).time);
			elapsedSpawningTime_.push_back(TABLE.at(i).time);
		}
		loadTextures();
		buildScene();
	}

	void World::update(sf::Time dt, CommandQueue& commands)
	{

		character_->setVelocity(0.f, 0.f);

		destroyEntitiesOutOfView();

		//run all the commands in the command queue
		while (!commandQueue_.isEmpty()) {
			sceneGraph_.onCommand(commandQueue_.pop(), dt);
		}

		handleCollisions();
		adaptPlayerPosition();
		adaptPlayerVelocity();

		addVehicles(dt);
		spawnVehicles();

		sceneGraph_.update(dt, commands);
		sceneGraph_.removeWrecks();

	}

	void World::adaptPlayerVelocity() {
		sf::Vector2f velocity = character_->getVelocity();
		if (velocity.x != 0.f && velocity.y != 0.f) {
			character_->setVelocity(velocity / std::sqrt(2.f));
		}
	}

	// Add a vehicle in the specific position.
	void World::addVehicle(DynamicObjects::Type type, float x, float y, float speed)
	{
		SpawnPoint spawnPoint(type, x, y, speed);
		vehicleSpawnPointes_.push_back(spawnPoint);
	}

	// Add vehicles in each position.
	void World::addVehicles(sf::Time dt)
	{
		for (int i = 0; i < spawningTime_.size(); i++)
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

			sceneLayers_[LowerAir]->attachChild(std::move(vehicles));
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
		sceneLayers_[UpperAir]->attachChild(std::move(bunker));
	}

	void World::addBunkers()
	{
		addBunker(StaticObjects::Type::Bunker);
		addBunker(StaticObjects::Type::Bunker);
	}


	sf::FloatRect World::getViewBounds() const
	{
		return sf::FloatRect(worldView_.getCenter() - (worldView_.getSize()/2.f), worldView_.getSize());	// center minus half size
	}

	sf::FloatRect World::getBattlefieldBounds() const
	{
		sf::FloatRect bounds = getViewBounds();
		bounds.top += 100.f;						// to up
		bounds.height -= 100.f;						// to bottom
		
		return bounds;
	}

	//10.18

	bool World::matchesCategories(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2)
	{
		unsigned int category1 = colliders.first->getCategory();
		unsigned int category2 = colliders.second->getCategory();

		if (type1 & category1 && type2 & category2) {		// If 1st category first hit to 2nd category, it works.
			return true;
		}
		else if (type1 & category2 && type2 & category1) {	// If 2nd category first hit to 1st category, it works.
			std::swap(colliders.first, colliders.second);
			return true;
		}
		else {
			return false;
		}
	}

	void World::destroyEntitiesOutOfView()
	{
		Command command;
		command.category = Category::Type::Projectile | Category::Type::Vehicle;
		command.action = derivedAction<Entity>([this](Entity& e, sf::Time dt)
		{
			if (!getBattlefieldBounds().intersects(e.getBoundingBox()))
				e.remove();
		});

		commandQueue_.push(command);
	}

	void World::handleCollisions()
	{
		// build a list of colliding pairs of SceneNodes
		std::set<SceneNode::Pair> collisionPairs;
		sceneGraph_.checkSceneCollision(sceneGraph_, collisionPairs);

		for (SceneNode::Pair pair : collisionPairs) {
			if (matchesCategories(pair, Category::Type::Character, Category::Type::Vehicle))
			{
				auto& hero = static_cast<DynamicObjects&>(*(pair.first));
				auto& zombie = static_cast<DynamicObjects&>(*(pair.second));
				
				auto zpos = zombie.getPosition();
				auto hpos = hero.getPosition();
				auto diffPos = zpos - hpos;
				zombie.setPosition(zpos + 0.2f * diffPos);
				hero.setPosition(hpos - 0.1f * diffPos);
			}
			/*else if (matchesCategories(pair, Category::Type::PlayerAircraft, Category::Type::Pickup))
			{
				auto& player = static_cast<Aircraft&>(*(pair.first));
				auto& pickup = static_cast<Pickup&>(*(pair.second));

				pickup.apply(player);
				pickup.destroy();
			}
			else if ((matchesCategories(pair, Category::Type::PlayerAircraft, Category::Type::EnemyProjectile)) ||
				(matchesCategories(pair, Category::Type::EnemyAircraft, Category::Type::AlliedProjectile))) 
			{
				auto& aircraft = static_cast<Aircraft&>(*(pair.first));
				auto& projectile = static_cast<Projectile&>(*(pair.second));

				aircraft.damage(projectile.getDamage());
				projectile.destroy();
			}*/
		}
	}

	//9.24
	void World::adaptPlayerPosition() {

		const float BORDER_DISTANCE = 40.f;
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
		window_.setView(worldView_);
		window_.draw(sceneGraph_);
	}

	CommandQueue & World::getCommandQueue()
	{
		return commandQueue_;
	}

	//10.22, 10.23
	bool World::hasAlivePlayer() const
	{
		return !character_->isDestroyed();
	}

	bool World::hasPlayerReachedEnd() const
	{
		return !worldBounds_.contains(character_->getPosition());
	}

	//10.24
	void World::loadTextures() {
		textures_.load(GEX::TextureID::City1, "Media/Textures/City1.png");
		textures_.load(GEX::TextureID::Particle, "Media/Textures/Particle.png");
		textures_.load(GEX::TextureID::Character, "Media/Textures/ke2.png");
		textures_.load(GEX::TextureID::SignPost, "Media/Textures/SignPost.png");
		textures_.load(GEX::TextureID::Bunker, "Media/Textures/Bunker.png");
		textures_.load(GEX::TextureID::Vehicle1, "Media/Textures/redcar2.png");
		textures_.load(GEX::TextureID::Vehicle2, "Media/Textures/whitecar2.png");
		textures_.load(GEX::TextureID::Vehicle3, "Media/Textures/truck2.png");
		textures_.load(GEX::TextureID::Vehicle4, "Media/Textures/redcar.png");
		textures_.load(GEX::TextureID::Vehicle5, "Media/Textures/whitecar.png");
		textures_.load(GEX::TextureID::Vehicle6, "Media/Textures/truck.png");
	}
	
	void World::buildScene() {
		// Initalize layers
		for (int i = 0; i < LayerCount; ++i) {
			auto category = (i == UpperAir) ? Category::Type::AirSceneLayer : Category::Type::None;
			SceneNode::Ptr layer(new SceneNode(category));
			sceneLayers_.push_back(layer.get());						// raw pointer to that layer(unique pointer).
			sceneGraph_.attachChild(std::move(layer));
		}

		// Particle System
		std::unique_ptr<ParticleNode>smoke(new ParticleNode(Particle::Type::Smoke, textures_));	// smoke part
		sceneLayers_[LowerAir]->attachChild(std::move(smoke));

		std::unique_ptr<ParticleNode>fire(new ParticleNode(Particle::Type::Propellant, textures_));	// fire part
		sceneLayers_[LowerAir]->attachChild(std::move(fire));

		// Background
		sf::Texture& texture = textures_.get(TextureID::City1);
		sf::IntRect textureRect(worldBounds_);							// it is size of my world

		std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
		backgroundSprite->setPosition(worldBounds_.left, worldBounds_.top);
		sceneLayers_[Background]->attachChild(std::move(backgroundSprite));

		// add character object
		std::unique_ptr<DynamicObjects> character(new DynamicObjects(DynamicObjects::Type::Character, textures_));
		character->setPosition(worldView_.getSize().x / 2.f, (worldView_.getSize().y));
		character_ = character.get();
		sceneLayers_[UpperAir]->attachChild(std::move(character));

		// add SignPost
		std::unique_ptr<StaticObjects> signPost(new StaticObjects(StaticObjects::Type::SignPost, textures_));	

		randomNumber = range(rnd);
		randomNums_.push_back(randomNumber);
		float xPosition = signPost->getObjectPosition()[randomNumber].first;
		float yPosition = signPost->getObjectPosition()[randomNumber].second;

		signPost->setPosition(xPosition, yPosition);
		signPost_ = signPost.get();
		sceneLayers_[LowerAir]->attachChild(std::move(signPost));
		
		// add Bunkers
		addBunkers();


	}
}


