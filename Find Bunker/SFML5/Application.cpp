/**
* @file
* Application.cpp
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

#include "Application.h"
#include "State.h"
#include "GameState.h"
#include "ScoreState.h"
#include "TitleState.h"
#include "MenuState.h"
#include "IntroState.h"
#include "PauseState.h"
#include "GameOverState.h"
#include "FontManager.h"

const sf::Time Application::TIMEPERFRAME  = sf::seconds(1.0f / 60.f); // seconds per frame for 60 fps

Application::Application()
	: window_(sf::VideoMode(2048, 1536), "Find Bunker", sf::Style::Close)
	, player_()
	, textures_()
	, stateStack_(GEX::State::Context(window_,textures_, player_, music_, sound_))
{
	window_.setKeyRepeatEnabled(false);			//prevent user from keep pressing repeatedly
	
	GEX::FontManager::getInstance().load(GEX::FontID::Main,"Media/Sansation.ttf");
	textures_.load(GEX::TextureID::TitleScreen, "Media/Textures/Title.jpg");
	textures_.load(GEX::TextureID::IntroScreen, "Media/Textures/Intro.png");
	textures_.load(GEX::TextureID::ScoreScreen, "Media/Textures/Rank.png");

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
	stateStack_.registerState<IntroState>(GEX::StateID::Intro);
	stateStack_.registerState<MenuState>(GEX::StateID::Menu);
	stateStack_.registerState<GameState>(GEX::StateID::Game);
	stateStack_.registerState<PauseState>(GEX::StateID::Pause);
	stateStack_.registerState<ScoreState>(GEX::StateID::Score);
	stateStack_.registerState<GameOverState>(GEX::StateID::GameOver);
}


