/**
* @file
* ScoreState.h
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


#pragma once
#include "State.h"

class ScoreState : public GEX::State											// inherits from the State class
{
public:
	ScoreState(GEX::StateStack& stack, Context context);						// Constructor containing StateStack by reference and Context as parameters

	void						draw() override;								// draw function overriding State draw member function sets the world view
	bool						update(sf::Time dt) override;					// update function updates update of world and real time input of playerControl
	bool						handleEvent(const sf::Event& event) override;	// this function handles pause events when pressing esc on the keyboard

private:
	void						setScoreText(Context context);					// Setter for Score text
	void						setScore();										// Setter for Score

private:
	sf::Sprite					backgroundSprite_;
	sf::Text					pressKeyText_;
	sf::Text					scoreText_;
	bool						showText_;
	sf::Time					textEffectTime_;
	std::string					score_;
};

