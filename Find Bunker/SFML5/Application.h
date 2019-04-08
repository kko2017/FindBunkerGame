#pragma once
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>


#include "PlayerControl.h"
#include "MusicPlayer.h"
#include "TextureManager.h"
#include "StateStack.h"

class Application
{
public:
								Application();
	void						run();

private:

	void						processInput();
	void						update(sf::Time deltaTime);
	void						render();
	void						registerStates();

private:
	static const sf::Time		TIMEPERFRAME;

	sf::RenderWindow			window_;
	GEX::PlayerControl			player_;
	GEX::TextureManager			textures_;
	GEX::MusicPlayer			music_;
	GEX::StateStack				stateStack_;
};

