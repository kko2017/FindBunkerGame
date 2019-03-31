#include "Entity.h"
#include <cassert>


namespace GEX {
	Entity::Entity(bool alive)
		: alive_(alive)
	{
	}
	void Entity::setVelocity(sf::Vector2f velocity) {
		velocity_ = velocity;
	}

	void Entity::setVelocity(float vx, float vy) {
		velocity_.x = vx;
		velocity_.y = vy;
	}

	sf::Vector2f Entity::getVelocity() const {
		return velocity_;
	}

	void Entity::accelerate(sf::Vector2f velocity)
	{
		velocity_ += velocity;
	}

	void Entity::accelerate(float vx, float vy)
	{
		velocity_.x += vx;
		velocity_.y += vy;

	}

	void Entity::rebirth(bool alive)
	{
		alive_ = alive;
	}

	void Entity::destroy()
	{
		alive_ = false;
	}

	bool Entity::isDestroyed() const
	{
		return (alive_ == false);
	}

	void Entity::remove()
	{
		destroy();
	}

	void Entity::updateCurrent(sf::Time dt, CommandQueue& commands) {
		move(velocity_ * dt.asSeconds());
	}
}
