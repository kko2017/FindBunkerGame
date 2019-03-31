#include "Actor.h"
#include "TextureManager.h"
#include "JsonFrameParser.h"
#include "TextureManager.h"
#include "Utility.h"
#include "DataTables.h"
#include "TextNode.h"

namespace GEX
{
	namespace
	{
		const std::map<Actor::Type, ActorData> TABLE = initializeActorData();
	}

	Actor::Actor(Type type, const GEX::TextureManager& textures)
		: Entity(100)
		, type_(type)
		, state_(State::Right)
		, sprite_(textures.get(TABLE.at(type).texture))
		, travelDistance_(0.f)
		, directionIndex_(0)
		, attack_(false)

	{
		for (auto a : TABLE.at(type).animations)
		{
			animations_[a.first] = a.second;
		}

		sprite_.setTextureRect(sf::IntRect());

		centerOrigin(sprite_);
	}



	unsigned int Actor::getCategory() const
	{
		switch (type_)
		{
		case Type::Hero2:
			return Category::Hero;
			break;
		case Type::Zombie1:
		case Type::Zombie2:
		case Type::Zombie3:
		case Type::Zombie4:
		case Type::Zombie5:
			return Category::Zombie;
			break;
		}
	}

	void Actor::updateMovementPattern(sf::Time dt)
	{
		// movement pattern
		const std::vector<GEX::Direction> directions = TABLE.at(type_).directions;

		if (!directions.empty())
		{
			if (travelDistance_ > (directions[directionIndex_].distance))
			{
				directionIndex_ = (++directionIndex_) % directions.size();
				travelDistance_ = 0;
			}

			float radians = toRadian(directions[directionIndex_].angle + 90.f);
			float vx = getMaxSpeed() * std::cos(radians);
			float vy = getMaxSpeed() * std::sin(radians);

			setVelocity(vx, vy);
			travelDistance_ += getMaxSpeed() * dt.asSeconds();
		}
	}

	sf::FloatRect Actor::getBoundingBox() const
	{
		auto box = getWorldTransform().transformRect(sprite_.getGlobalBounds());
		box.width -= 30; // tighten up bounding box for more realistic collisions
		box.left += 15;
		return box;
	}

	float Actor::getMaxSpeed() const
	{
		return TABLE.at(type_).speed;
	}

	void Actor::accelerate(sf::Vector2f velocity)
	{
		switch (state_)
		{
		case State::Up:
		case State::Down:
		case State::Left:
		case State::Right:
			Entity::accelerate(velocity);
			break;
		default:
			break;
		}
	}

	void Actor::setState(State state)
	{
		state_ = state;
		animations_[state_].restart();
	}

	bool Actor::isMarkedForRemoval() const
	{
		//return isDestroyed() && animations_[state_].isFinished();
		return false;
	}

	void Actor::updateStates()
	{
		if (isDestroyed() && (state_ == State::Up || state_ == State::Down || state_ == State::Right
			|| state_ == State::Left) && state_ != State::Dead) {
			state_ = State::Dead;
			animations_.at(state_).restart();
		}

		if (state_ == State::Dead && animations_.at(state_).isFinished()) {
			state_ = State::Up;
			animations_.at(state_).restart();
			rebirth(true);
		}

		if ((state_ == State::Up || state_ == State::Down || state_ == State::Right
			|| state_ == State::Left) && getVelocity().x < -0.f) {
			state_ = State::Left;
		}


		if ((state_ == State::Up || state_ == State::Down || state_ == State::Left
			|| state_ == State::Right) && getVelocity().x > 0.f) {
			state_ = State::Right;
		}


		if ((state_ == State::Up || state_ == State::Down || state_ == State::Left
			|| state_ == State::Right) && getVelocity().y < -0.f) {
			state_ = State::Up;
		}


		if ((state_ == State::Up || state_ == State::Left || state_ == State::Right
			|| state_ == State::Down) && getVelocity().y > 0.f) {
			state_ = State::Down;
		}
	}

	void Actor::updateCurrent(sf::Time dt, GEX::CommandQueue & commands)
	{
		updateStates();

		auto rec = animations_.at(state_).update(dt);

		sprite_.setTextureRect(rec);
		centerOrigin(sprite_);

		if (state_ != State::Dead) // dont move it while dying
			Entity::updateCurrent(dt, commands);

		updateMovementPattern(dt);
	}

	void Actor::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
	{
		target.draw(sprite_, states);
	}
}