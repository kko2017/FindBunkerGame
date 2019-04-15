/**
* @file
* Animation2.h
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

namespace sf{
	class Time;
}

using Frame = sf::IntRect;

namespace GEX {

	class Animation2{
	public:																		
		explicit Animation2(bool repeat = true);								// Constructor has the boolean repeat as a parameter

		void						addFrame(Frame frame);						// Add frames
		void						addFrameSet(std::vector<Frame> frames);		// Add frameset

		void						setDuration(sf::Time duration);				// Setter of duration
		sf::Time					getDuration() const;						// Getter of duration

		void						setRepeating(bool flag);					// set repeating animation
		bool						isRepeating() const;						// checks if the animation needs to be repeating

		void						restart();									// Restart the animation
		bool						isFinished() const;							// Checks if the animation is finished

		Frame						getCurrentFrame() const;					// Getter for current frame

		Frame						update(sf::Time dt);						// Update it following sf::Time
	
	private:

		std::vector<Frame>			frames_;
		std::size_t					currentFrame_;
		sf::Time					duration_;
		sf::Time					elapsedTime_;
		bool						repeat_;
	};
}
