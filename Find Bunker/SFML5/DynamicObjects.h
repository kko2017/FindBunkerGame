/**
* @file
* DynamicObjects.h
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
#include "Entity.h"
#include "Command.h"
#include "Animation2.h"
#include "ResourceIdentifiers.h"

#include <SFML/Graphics/Sprite.hpp>
#include <map>


namespace GEX {

	class TextureManager;
	class TextNode;

	class DynamicObjects : public Entity
	{
	public:
		enum class Type															// Scoped enumeration class is for specific identifier in the type of the objects
		{
			Character,
			RedCarToRight,
			WhiteCarToRight,
			TruckToRight,
			RedCarToLeft,
			WhiteCarToLeft,
			TruckToLeft,
			BusToLeft,
			Boy,
			Girl,
			Police
		};

		enum class State {														// Scoped enumeration class is for specific identifier in the state of the objects
			Up,
			Down,
			Left,
			Right,
			Dead,
			Drive
		};

	public:
		DynamicObjects(Type type, const TextureManager& textures);				// constuctor that passes the type and the textures
		~DynamicObjects() = default;											// default destructor

		unsigned int	getCategory() const override;							// get category type by the state type
		sf::FloatRect	getBoundingBox() const override;						// get the bounding box of the objects
		virtual			void accelerate(sf::Vector2f velocity) override;		// set acceleration of the velocity of the objects

		void			setState(State state);									// set the state of the objects
		bool			finishedDeadAnimation() const;							// checks whether the death animation is finished
		bool			isMarkedForRemoval() const override;					// checks whether the objects is marked for removal
		void			playLocalSound(CommandQueue& commands,
										SoundEffectID effect);					// Plays the sound for specific action of the objects

	private:
		void			updateStates();											// update the states of the objects 
		void			updateCurrent(sf::Time dt,
						GEX::CommandQueue& commands) override;					// update the current events of the objects
		void			drawCurrent(sf::RenderTarget& target,
						sf::RenderStates states) const override;				// draw the current object
																	
	private:
		Type										type_;
		State										state_;
		mutable sf::Sprite							sprite_;
		mutable std::map<State, Animation2>			animations_;
		TextNode*									healthDisplay_;

		float										travelDistance_;
		std::size_t									directionIndex_;
		bool										attack_;
	};

}
