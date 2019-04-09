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
		SoundPlayer();										// Default Constructor
		~SoundPlayer() = default;							// Default Destructor
		SoundPlayer(const SoundPlayer&) = delete;			// Delete the copy constructor
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
