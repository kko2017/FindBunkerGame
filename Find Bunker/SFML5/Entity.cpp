/**
* @file
* Entity.cpp
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

#include "Entity.h"
#include <cassert>


namespace GEX {
	Entity::Entity(bool alive)
		: alive_(alive)
		, dead_(false)
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

	void Entity::destroy()
	{
		alive_ = false;
		dead_ = true;
	}

	bool Entity::isAlive() const
	{
		return alive_;
	}

	bool Entity::isDestroyed() const
	{
		return (dead_ == true);
	}

	void Entity::remove()
	{
		destroy();
	}

	void Entity::updateCurrent(sf::Time dt, CommandQueue& commands) {
		move(velocity_ * dt.asSeconds());
	}
}
