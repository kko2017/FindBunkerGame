#include "DynamicObjects.h"
#include "Command.h"
#include "TextNode.h"
#include "Utility.h"
#include "DataTables.h"
#include "SoundNode.h"
#include "CommandQueue.h"
#include "TextureManager.h"
#include "JsonFrameParser.h"
#include "TextureManager.h"

namespace GEX {

	namespace
	{
		// the TABLE container holds the data of the dynamic objects 
		const std::map<DynamicObjects::Type, DynamicObjectsData> TABLE = initializeDynamicObjectsData();
	}

	DynamicObjects::DynamicObjects(Type type, const TextureManager& textures)
		: Entity(true)
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

		if (DynamicObjects::getCategory() == Category::Type::Vehicle)
		{
			state_ = State::Drive;
		}

		sprite_.setTextureRect(sf::IntRect());
		centerOrigin(sprite_);
	}

	unsigned int DynamicObjects::getCategory() const
	{
		switch (type_)
		{
		case Type::Character:
			return Category::Character;
			break;
		case Type::RedCarToRight:
		case Type::WhiteCarToRight:
		case Type::TruckToRight:
		case Type::RedCarToLeft:
		case Type::WhiteCarToLeft:
		case Type::TruckToLeft:
		case Type::BusToLeft:
			return Category::Vehicle;
			break;
		}
		return Category::None;
	}

	sf::FloatRect DynamicObjects::getBoundingBox() const
	{
		auto box = getWorldTransform().transformRect(sprite_.getGlobalBounds());
		box.width -= 30; // tighten up bounding box for more realistic collisions
		box.left += 15;
		return box;
	}

	void DynamicObjects::accelerate(sf::Vector2f velocity)
	{
		switch (state_)
		{
		case State::Up:
		case State::Down:
		case State::Left:
		case State::Right:
		case State::Drive:
			Entity::accelerate(velocity);
			break;
		default:
			break;
		}
	}

	void DynamicObjects::setState(State state)
	{
		state_ = state;
		animations_[state_].restart();
	}

	bool DynamicObjects::finishedDeadAnimation() const
	{
		return state_ == State::Dead && animations_.at(state_).isFinished();
	}

	bool DynamicObjects::isMarkedForRemoval() const
	{
		if (type_ == Type::Character) {
			return isDestroyed() && state_ == State::Dead && animations_[state_].isFinished();
		}

		return isDestroyed();
	}

	void DynamicObjects::playLocalSound(CommandQueue & commands, SoundEffectID effect)
	{
		Command playSoundCommand;
		playSoundCommand.category = Category::Type::SoundEffect;
		playSoundCommand.action = derivedAction<SoundNode>(
			std::bind(&SoundNode::playSound, std::placeholders::_1, effect, getWorldPosition()));

		commands.push(playSoundCommand);
	}

	void DynamicObjects::updateStates()
	{
		if (isDestroyed() && (state_ == State::Up || state_ == State::Down || state_ == State::Right
			|| state_ == State::Left) && state_ != State::Dead) {
			state_ = State::Dead;
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

	void DynamicObjects::updateCurrent(sf::Time dt, GEX::CommandQueue & commands)
	{
		updateStates();

		auto rec = animations_.at(state_).update(dt);

		sprite_.setTextureRect(rec);
		centerOrigin(sprite_);

		if (state_ != State::Dead) // dont move it while dying
			Entity::updateCurrent(dt, commands);
	}

	void DynamicObjects::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
	{
		target.draw(sprite_, states);
	}
}
