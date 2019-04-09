#include "MusicPlayer.h"

// Default Constructor initiallizes member variables
GEX::MusicPlayer::MusicPlayer()
	: music_()
	, filenames_()
	, volume_(25)
{
	filenames_[MusicID::MissionTheme] = "Media/Music/suspect.flac";
	filenames_[MusicID::MenuTheme] = "Media/Music/Extreme_Energy_ROCK.flac";
}

// set up the play of the music
void GEX::MusicPlayer::play(MusicID theme)
{
	if (!music_.openFromFile(filenames_[theme]))
		throw std::runtime_error("Music could not open file");

	music_.setLoop(true);
	music_.play();
}

// set the stop of the music
void GEX::MusicPlayer::stop()
{
	music_.stop();
}

// set paused music
void GEX::MusicPlayer::setPaused(bool paused)
{
	if (paused)
		music_.pause();
	else
		music_.play();
}

// set up the volume
void GEX::MusicPlayer::setVolume(float volume)
{
	volume_ = volume;
	music_.setVolume(volume_);
}
