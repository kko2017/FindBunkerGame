#include "Application.h"
#include "State.h"
#include "GameState.h"
#include "TitleState.h"
#include "MenuState.h"
#include "PauseState.h"
#include "GameOverState.h"
#include "FontManager.h"

const sf::Time Application::TimePerFrame  = sf::seconds(1.0f / 60.f); // seconds per frame for 60 fps

Application::Application()
	: window_(sf::VideoMode(2048, 1536), "Find Bunker", sf::Style::Close)
	, player_()
	, textures_()
	, stateStack_(GEX::State::Context(window_,textures_, player_))
	, statisticText_()
	, statisticUpdateTime_()
	, statisticNumFrames_(0)
{
	window_.setKeyRepeatEnabled(false);			//prevent user from keep pressing repeatedly
	
	GEX::FontManager::getInstance().load(GEX::FontID::Main,"Media/Sansation.ttf");

	textures_.load(GEX::TextureID::TitleScreen, "Media/Textures/intro.jpg");

	statisticText_.setFont(GEX::FontManager::getInstance().get(GEX::FontID::Main));
	statisticText_.setPosition(5.0f, 5.0f);
	statisticText_.setCharacterSize(15.0f);
	statisticText_.setString("Frames / Second = \nTime / Update =");

	registerStates();
	stateStack_.pushState(GEX::StateID::Title);

}

void Application::run()
{		

	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (window_.isOpen()) {

		timeSinceLastUpdate += clock.restart(); // not adding now, reseting

		while (timeSinceLastUpdate > TimePerFrame) {
			
			processInput();
			update(TimePerFrame);

			if (stateStack_.isEmpty())
				window_.close();

			timeSinceLastUpdate -= TimePerFrame;
		}

		updatestatistics(timeSinceLastUpdate);
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
	window_.draw(statisticText_);
	window_.display();
}

void Application::updatestatistics(sf::Time deltaTime)
{
	statisticUpdateTime_ += deltaTime;
	statisticNumFrames_ += 1;
	if (statisticUpdateTime_ > sf::seconds(1)) {
		statisticText_.setString("Frames / Second = " + std::to_string(statisticNumFrames_) + "\n"
			+ "Time / Update  = " + std::to_string(statisticUpdateTime_.asMicroseconds() / statisticNumFrames_)
			+ " ms");

		// why?
		statisticUpdateTime_ -= sf::seconds(1);
		statisticNumFrames_ = 0;
	}
}

void Application::registerStates()
{
	stateStack_.registerState<TitleState>(GEX::StateID::Title);
	stateStack_.registerState<MenuState>(GEX::StateID::Menu);
	stateStack_.registerState<GameState>(GEX::StateID::Game);
	stateStack_.registerState<PauseState>(GEX::StateID::Pause);
	stateStack_.registerState<GameOverState>(GEX::StateID::GameOver);
}


