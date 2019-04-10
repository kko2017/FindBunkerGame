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
