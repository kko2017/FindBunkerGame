/**
* @file
* GameOverState.cpp
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

#include "GameOverState.h"
#include "FontManager.h"
#include "Utility.h"
#include "PlayerControl.h"

// Constructor containing StateStack by reference and Context as parameters
// initializes the all member variables
GameOverState::GameOverState(GEX::StateStack & stack, Context context)
	: State(stack, context)
	, gameOverText_()
	, text_()
	, elapsedTime_(sf::Time::Zero)
{
	sf::Font& font = GEX::FontManager::getInstance().get(GEX::FontID::Main);
	sf::Vector2f windowSize(context.window->getSize());
	gameOverText_.setFont(font);

	if (context.player->getMissionStatus() == GEX::MissionStatus::MissionFailure) 
	{
		
		gameOverText_.setString("Mission Failure");
	}
	else 
	{

		gameOverText_.setString("Mission Success");
	}

	gameOverText_.setCharacterSize(150);
	centerOrigin(gameOverText_);
	gameOverText_.setPosition(0.5f * windowSize.x, 0.45f * windowSize.y);

	text_.setFont(font);
	text_.setCharacterSize(50);
	text_.setString("Press any key to score board");
	centerOrigin(text_);
	text_.setPosition(1000.f, 1000.f);

}

// draw function overriding State draw member function sets the world view
void GameOverState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(80, 80, 80, 35));
	backgroundShape.setSize(window.getView().getSize());

	window.draw(backgroundShape);
	window.draw(gameOverText_);
	window.draw(text_);
}

// update function updates update of world and real time input of playerControl
bool GameOverState::update(sf::Time dt)
{
	elapsedTime_ += dt;
	if (elapsedTime_ > sf::seconds(1.f)) 
	{
		requestStackClear();
		requestStackPush(GEX::StateID::Score);
	}

	return false;
}

// this function handles pause events when pressing esc on the keyboard
bool GameOverState::handleEvent(const sf::Event & event)
{
	return false;
}
