/**
* @file
* Entity.h
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
#include "SceneNode.h"

namespace GEX {

	class Entity : public SceneNode													// Entity class inherits from SceneNode class.
	{
	public:
		explicit			Entity(bool alive);										// constructor having points as parameters

		void				setVelocity(sf::Vector2f velocity);						// setter for velocity
		void				setVelocity(float vx, float vy);						// setter for velocity

		sf::Vector2f		getVelocity() const;									// getter for velocity

		virtual void		accelerate(sf::Vector2f velocity);						// set up the acceleration
		void				accelerate(float vx, float vy);							// set up the acceleration

		void				destroy();												// destroy the objects
		bool				isAlive() const;										// checks whether object is alive
		bool				isDestroyed() const override;							// checks whether it is destroyed

		virtual void		remove();												// remove it from the scene

	protected:
		void		updateCurrent(sf::Time dt, CommandQueue& commands) override;	// this function updates the current move

	private:
		sf::Vector2f		velocity_;
		bool				alive_;
		bool				dead_;
	};

}

