#include "SoundPlayer.h"
#include "ResourceIdentifiers.h"

#include <cassert>

#include <SFML/Audio/Listener.hpp>
#include <SFML/System/Vector2.hpp>

namespace {
	// Sound coordinate system, point of view of a player in front of the screen:
	// X = left; Y = up; Z = back (out of the screen)
	const float ListenerZ = 300.f;
	const float Attenuation = 8.f;
	const float MinDistance2D = 200.f;
	const float MinDistance3D = std::sqrt(MinDistance2D*MinDistance2D + ListenerZ * ListenerZ);
}

// Default Constructor initiallizes all member variables
GEX::SoundPlayer::SoundPlayer()
	: soundBuffers_()
	, sounds_()
{
	loadBuffer(SoundEffectID::GetSignpost, "Media/Sound/get_signpost.wav");
	loadBuffer(SoundEffectID::KnockBunker, "Media/Sound/door_knock.wav");
	loadBuffer(SoundEffectID::OpenBunker, "Media/Sound/door_open.wav");
	loadBuffer(SoundEffectID::CharacterDead, "Media/Sound/character_dead.wav");
	loadBuffer(SoundEffectID::GetKey, "Media/Sound/get_key.wav");

	// Listener points towards the screen (default in SFML)
	sf::Listener::setDirection(0.f, 0.f, -1.f);
}

// set up the play of the sound
void GEX::SoundPlayer::play(SoundEffectID effect)
{
	play(effect, getListnerPosition());
}

// set up the play of the sound and the position of it
void GEX::SoundPlayer::play(SoundEffectID effect, sf::Vector2f position)
{
	sounds_.push_back(sf::Sound());
	sf::Sound& sound = sounds_.back();

	sound.setBuffer(*soundBuffers_[effect]);
	sound.setPosition(position.x, -position.y, 0.f);
	sound.setAttenuation(Attenuation);
	sound.setMinDistance(MinDistance3D);

	sound.play();
}

// stopped sound is removed
void GEX::SoundPlayer::removeStoppedSounds()
{
	sounds_.remove_if([](const sf::Sound& s) {
		return s.getStatus() == sf::Sound::Stopped;
	});
}

// set the listener's position
void GEX::SoundPlayer::setListnerPosition(sf::Vector2f position)
{
	sf::Listener::setPosition(position.x, -position.y, ListenerZ);
}

// get the listener's position
sf::Vector2f GEX::SoundPlayer::getListnerPosition() const
{
	sf::Vector3f pos = sf::Listener::getPosition();

	return sf::Vector2f(pos.x, -pos.y);
}

// set calling the sound from the file and loading the buffer
void GEX::SoundPlayer::loadBuffer(SoundEffectID id, const std::string path)
{
	std::unique_ptr<sf::SoundBuffer> buffer(new sf::SoundBuffer);
	if (!buffer->loadFromFile(path))
		throw std::runtime_error("Sound Effect Load Failed");

	auto inserted = soundBuffers_.insert(std::make_pair(id, std::move(buffer)));
	assert(inserted.second);
}
