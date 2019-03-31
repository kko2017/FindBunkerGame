#include "Entity.h"
#include <cassert>


namespace GEX {
	Entity::Entity(int points)
		: hitpoints_(points)
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
	//9.26
	void Entity::rotate(float r)
	{
		rotate_ += r;
	}


	//10.3
	int Entity::getHitpoints() const
	{
		return hitpoints_;
	}

	void Entity::repair(int points)
	{
		assert(points > 0);
		hitpoints_ += points;
	}

	void Entity::destroy()
	{
		hitpoints_ = 0;
	}

	bool Entity::isDestroyed() const
	{
		return (hitpoints_ <= 0);
	}

	void Entity::remove()
	{
		destroy();
	}



	void Entity::updateCurrent(sf::Time dt, CommandQueue& commands) {
		move(velocity_ * dt.asSeconds());
		//9.26
		setRotation(rotate_);
	}
}
