#include "World.h"
//10.25
#include "ParticleNode.h"

namespace GEX {

	World::World(sf::RenderWindow& window)
		: window_(window)
		, worldView_(window.getDefaultView())
		, textures_()
		, sceneGraph_()
		, sceneLayers_()
		, worldBounds_(0.f, 0.f, worldView_.getSize().x, worldView_.getSize().y)
		, spawnPosition_(worldView_.getSize().x / 2.f, worldBounds_.height - (worldView_.getSize().y / 2.f))
		, scrollSpeed_(-50.f)
		, playerAircraft_(nullptr)
	{

		loadTextures();
		buildScene();

		worldView_.setCenter(spawnPosition_);
	}

	void World::update(sf::Time dt, CommandQueue& commands)
	{

		//9.24
		playerAircraft_->setVelocity(0.f, 0.f);

		//10.22
		destroyEntitiesOutOfView();

		//run all the commands in the command queue
		while (!commandQueue_.isEmpty()) {
			sceneGraph_.onCommand(commandQueue_.pop(), dt);
		}

		//10.18
		handleCollisions();
		//10.22
		sceneGraph_.removeWrecks();

		adaptPlayerVelocity();
		sceneGraph_.update(dt, commands);
		adaptPlayerPosition();
	
		//10.10
		spawnEnemies();

	}

	//9.24
	void World::adaptPlayerVelocity() {
		sf::Vector2f velocity = playerAircraft_->getVelocity();
		if (velocity.x != 0.f && velocity.y != 0.f) {
			playerAircraft_->setVelocity(velocity / std::sqrt(2.f));
		}
	}

	//10.10
	void World::addEnemies()
	{
		/*addEnemy(Actor::Type::Zombie1, -250.f, 200.f);
		addEnemy(Actor::Type::Zombie2, 0.f, 200.f);
		addEnemy(Actor::Type::Zombie3, 250.f, 200.f);

		addEnemy(Actor::Type::Zombie1, -250.f, 600.f);
		addEnemy(Actor::Type::Zombie2, 0.f, 600.f);


		addEnemy(Actor::Type::Zombie3, -70.f, 800.f);
		addEnemy(Actor::Type::Zombie1, 70.f, 800.f);

		addEnemy(Actor::Type::Zombie1, -170.f, 850.f);
		addEnemy(Actor::Type::Zombie2, 170.f, 850.f);

		std::sort(enemySpawnPointes_.begin(), enemySpawnPointes_.end(), 
			[](SpawnPoint lhs, SpawnPoint rhs)
			{
				return lhs.y < rhs.y;
			}
		);*/

	}

	void World::addEnemy(Actor::Type type, float relX, float relY)
	{
		//SpawnPoint	spawnPoint(type, spawnPosition_.x - relX, spawnPosition_.y = relY);
		//enemySpawnPointes_.push_back(spawnPoint);

	}

	void World::spawnEnemies()
	{
		while (!enemySpawnPointes_.empty() &&
			enemySpawnPointes_.back().y > getBattlefieldBounds().top) {
			
			auto spawnPoint = enemySpawnPointes_.back();
			std::unique_ptr<Actor> enemy(new Actor(spawnPoint.type, textures_));
			enemy->setPosition(spawnPoint.x, spawnPoint.y);
			//enemy->rotate(180);
			sceneLayers_[UpperAir]->attachChild(std::move(enemy));
			enemySpawnPointes_.pop_back();
		}
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
		command.category = Category::Type::Projectile | Category::Type::EnemyAircraft;
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
			if (matchesCategories(pair, Category::Type::Hero, Category::Type::Zombie))
			{
				auto& hero = static_cast<Actor&>(*(pair.first));
				auto& zombie = static_cast<Actor&>(*(pair.second));

				/*zombie.damage(hero.attackPoints());
				hero.damage(zombie.attackPoints());*/
				
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

		sf::Vector2f position = playerAircraft_->getPosition();
		position.x = std::max(position.x, viewBounds.left + BORDER_DISTANCE);
		position.x = std::min(position.x, viewBounds.left + viewBounds.width - BORDER_DISTANCE);

		position.y = std::max(position.y, viewBounds.top + BORDER_DISTANCE);
		position.y = std::min(position.y, viewBounds.top + viewBounds.height - BORDER_DISTANCE);

		playerAircraft_->setPosition(position);
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
		return !playerAircraft_->isDestroyed();
	}

	bool World::hasPlayerReachedEnd() const
	{
		return !worldBounds_.contains(playerAircraft_->getPosition());
	}

	//10.24
	void World::loadTextures() {
		textures_.load(GEX::TextureID::Entities, "Media/Textures/Entities.png");
		textures_.load(GEX::TextureID::City1, "Media/Textures/City1.jpg");
		textures_.load(GEX::TextureID::Particle, "Media/Textures/Particle.png");
		textures_.load(GEX::TextureID::Explosion, "Media/Textures/Explosion.png");
		textures_.load(GEX::TextureID::FinishLine, "Media/Textures/FinishLine.png");
		textures_.load(GEX::TextureID::Hero2, "Media/Textures/ke2.png");
		textures_.load(GEX::TextureID::Zombie1, "Media/Textures/Zombie1.png");
		textures_.load(GEX::TextureID::Zombie2, "Media/Textures/Zombie2.png");
		textures_.load(GEX::TextureID::Zombie3, "Media/Textures/Zombie3.png");
	}

	void World::buildScene() {
		// Initalize layers
		for (int i = 0; i < LayerCount; ++i) {
			//10.11, 10.25
			auto category = (i == UpperAir) ? Category::Type::AirSceneLayer : Category::Type::None;
			//10.11
			SceneNode::Ptr layer(new SceneNode(category));
			sceneLayers_.push_back(layer.get());						// raw pointer to that layer(unique pointer).
			sceneGraph_.attachChild(std::move(layer));
		}

		//10.25
		// Particle System
		std::unique_ptr<ParticleNode>smoke(new ParticleNode(Particle::Type::Smoke, textures_));	// smoke part
		sceneLayers_[LowerAir]->attachChild(std::move(smoke));

		std::unique_ptr<ParticleNode>fire(new ParticleNode(Particle::Type::Propellant, textures_));	// fire part
		sceneLayers_[LowerAir]->attachChild(std::move(fire));



		// Background
		sf::Texture& texture = textures_.get(TextureID::City1);
		sf::IntRect textureRect(worldBounds_);							// it is size of my world
		//texture.setRepeated(true);


		std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
		backgroundSprite->setPosition(worldBounds_.left, worldBounds_.top);
		sceneLayers_[Background]->attachChild(std::move(backgroundSprite));

		// add player aircraft & game object
		std::unique_ptr<Actor> leader(new Actor(Actor::Type::Hero2, textures_));
		leader->setPosition(worldView_.getSize().x / 2.f, (worldView_.getSize().y));
		leader->setVelocity(150.f, scrollSpeed_);
		playerAircraft_ = leader.get();
		sceneLayers_[UpperAir]->attachChild(std::move(leader));

		// add enemy aircrft
		addEnemies();

	}
}

