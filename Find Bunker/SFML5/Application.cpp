#include "Application.h"
#include "State.h"
#include "GameState.h"
#include "TitleState.h"
#include "MenuState.h"
#include "PauseState.h"
#include "GameOverState.h"
#include "FontManager.h"

const sf::Time Application::TIMEPERFRAME  = sf::seconds(1.0f / 60.f); // seconds per frame for 60 fps

Application::Application()
	: window_(sf::VideoMode(2048, 1536), "Find Bunker", sf::Style::Close)
	, player_()
	, textures_()
	, stateStack_(GEX::State::Context(window_,textures_, player_, music_))
{
	window_.setKeyRepeatEnabled(false);			//prevent user from keep pressing repeatedly
	
	GEX::FontManager::getInstance().load(GEX::FontID::Main,"Media/Sansation.ttf");
	textures_.load(GEX::TextureID::TitleScreen, "Media/Textures/intro.jpg");

	registerStates();
	stateStack_.pushState(GEX::StateID::Title);

}

void Application::run()
{		
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (window_.isOpen()) 
	{
		timeSinceLastUpdate += clock.restart();

		while (timeSinceLastUpdate > TIMEPERFRAME) 
		{	
			update(TIMEPERFRAME);
			processInput();

			if (stateStack_.isEmpty())
				window_.close();

			timeSinceLastUpdate -= TIMEPERFRAME;
		}

		render();
	}
}

void Application::processInput()
{
	sf::Event event;
	while (window_.pollEvent(event)) {
		stateStack_.handleEvent(event);
		
		if (event.type == sf::Event::Closed)
			window_.close();
	}
}

void Application::update(sf::Time deltaTime)
{
	stateStack_.update(deltaTime);
}

void Application::render()
{
	window_.clear();
	stateStack_.draw();

	window_.setView(window_.getDefaultView());
	window_.display();
}

void Application::registerStates()
{
	stateStack_.registerState<TitleState>(GEX::StateID::Title);
	stateStack_.registerState<MenuState>(GEX::StateID::Menu);
	stateStack_.registerState<GameState>(GEX::StateID::Game);
	stateStack_.registerState<PauseState>(GEX::StateID::Pause);
	stateStack_.registerState<GameOverState>(GEX::StateID::GameOver);
}


