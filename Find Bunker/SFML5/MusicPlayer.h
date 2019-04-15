/**
* @file
* MusicPlayer.h
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
#include <string>
#include <SFML/Audio/Music.hpp>

namespace GEX 
{

	class MusicPlayer
	{
	public:
		MusicPlayer();															// Default Constructor
		~MusicPlayer() = default;												// Default Destructor
		MusicPlayer(const MusicPlayer&) = delete;								// Delete the copy constructor
		MusicPlayer&				operator=(const MusicPlayer&) = delete;		// lose the functions of operator=

		void						play(MusicID theme);						// set up the play of the music
		void						stop();										// set the stop of the music
		void						setPaused(bool paused);						// set paused music
		void						setVolume(float volume);					// set up the volume

	private:
		sf::Music						music_;
		std::map<MusicID, std::string>	filenames_;
		float							volume_;

	};
}
