/**
* @file
* Animation.h
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

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>


namespace GEX {

	class Animation : public sf::Drawable, public sf::Transformable				// Inherits from the drawable, the transformable
	{
	public:
		Animation();															// Default constructor	
		Animation(const sf::Texture& texture);									// Copy constructor

		void						setFrameSize(sf::Vector2i frameSize);		// Setter of the frame size
		sf::Vector2i				getFrameSize() const;						// Getter of the frame size

		void						setNumFrames(std::size_t numFrames);		// Setter of the number of frames
		std::size_t					getNumFrames() const;						// Getter of the number of frames

		void						setDuration(sf::Time duration);				// Setter of the duration
		sf::Time					getDuration() const;						// Getter of the duration

		void						setRepeating(bool flag);					// Set repeating animation
		bool						isRepeating() const;						// if the animation of the entity is repeating, then it is tur

		void						restart();									// Restart the animation
		bool						isFinished() const;							// Checks whether or not game is finished

		sf::FloatRect				getLocalBounds() const;						// Get local bounds of animation
		sf::FloatRect				getGlobalBounds() const;					// Get global bounds of animation

		void						update(sf::Time dt);						// Update the animation

	private:
		void						draw(sf::RenderTarget& target,
									sf::RenderStates states) const override; 	// This draw method is overriden by draw() in sf::Drawable

	private:
		sf::Sprite					sprite_;
		sf::Vector2i				frameSize_;
		std::size_t					numberOfFrames_;
		std::size_t					currentFrame_;
		sf::Time					duration_;
		sf::Time					elapsedTime_;
		bool						repeat_;
	};

}
