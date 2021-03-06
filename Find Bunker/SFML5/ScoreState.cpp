/**
* @file
* ScoreState.cpp
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

#include "ScoreState.h"
#include "TextureManager.h"
#include "Utility.h"
#include "FontManager.h"

#include <fstream>

// Constructor containing StateStack by reference and Context as parameters
ScoreState::ScoreState(GEX::StateStack & stack, Context context)
	: State(stack, context)
	, pressKeyText_()
	, scoreText_()
	, showText_(true)
	, textEffectTime_(sf::Time::Zero)
{
	backgroundSprite_.setTexture(context.textures->get(GEX::TextureID::ScoreScreen));

	pressKeyText_.setFillColor(sf::Color::White);
	pressKeyText_.setOutlineColor(sf::Color::Red);
	pressKeyText_.setOutlineThickness(3.5f);
	pressKeyText_.setStyle(sf::Text::Italic);
	pressKeyText_.setFont(GEX::FontManager::getInstance().get(GEX::FontID::Main));
	pressKeyText_.setCharacterSize(50);
	pressKeyText_.setString("Press any key to menu");
	centerOrigin(pressKeyText_);
	pressKeyText_.setPosition(1700.f, 1400.f);

	setScoreText(context);
}

// draw function overriding State draw member function sets the world view
void ScoreState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.draw(backgroundSprite_);

	if (showText_) 
	{
		window.draw(pressKeyText_);
	}

	window.draw(scoreText_);
}

// update function updates update of world and real time input of playerControl
bool ScoreState::update(sf::Time dt)
{
	textEffectTime_ += dt;

	if (textEffectTime_ >= sf::seconds(0.5f)) 
	{
		showText_ = !showText_;
		textEffectTime_ = sf::Time::Zero;
	}

	return true;
}

// this function handles pause events when pressing esc on the keyboard
bool ScoreState::handleEvent(const sf::Event & event)
{
	if (event.type == sf::Event::KeyPressed) 
	{
		requestStackPop();
		requestStackPush(GEX::StateID::Menu);
	}
	return true;
}

// Set the score text
void ScoreState::setScoreText(Context context)
{
	setScore();

	scoreText_.setFillColor(sf::Color::White);
	scoreText_.setOutlineThickness(1.5f);
	scoreText_.setFont(GEX::FontManager::getInstance().get(GEX::FontID::Main));
	scoreText_.setCharacterSize(50);
	scoreText_.setString("Time          Date\n\n" + score_);

	centerOrigin(scoreText_);
	scoreText_.setPosition(1700.f, 700.f);
}

// set score
void ScoreState::setScore()
{
	std::ifstream is;
	std::string record = "";
	std::string fileName = "Record/highRecord.txt";
	is.open(fileName);

	int i = 0;
	while (i < 10)
	{
		i++;
		std::getline(is, record);
		score_ += " " + record + "\n\n";
	}

	is.close();
}

