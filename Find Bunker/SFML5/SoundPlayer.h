/**
* @file
* SoundPlayer.h
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
#include "ResourceIdentifiers.h"

#include <map>
#include <list>
#include <string>
#include <memory>

#include <SFML/Audio/Sound.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

namespace GEX {

	class SoundPlayer
	{
	public:
		SoundPlayer();																// Default Constructor
		~SoundPlayer() = default;													// Default Destructor
		SoundPlayer(const SoundPlayer&) = delete;									// Delete the copy constructor
		SoundPlayer&			operator=(const SoundPlayer&) = delete;				// Delete the operator= of the copy constructor

		void					play(SoundEffectID effect);							// set up the play of the sound
		void					play(SoundEffectID effect, sf::Vector2f position);  // set up the play of the sound and the position of it

		void					removeStoppedSounds();								// stopped sound is removed
		void					setListnerPosition(sf::Vector2f position);			// set the listener's position
		sf::Vector2f			getListnerPosition() const;							// get the listener's position

	private:
		void					loadBuffer(SoundEffectID id, const std::string path); // set calling the sound from the file and loading the buffer


	private:
		std::map<SoundEffectID, std::unique_ptr<sf::SoundBuffer>>	soundBuffers_;
		std::list<sf::Sound>										sounds_;
	};
}
