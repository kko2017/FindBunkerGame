/**
* @file
* State.cpp
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

#include "State.h"
#include "StateStack.h"

namespace GEX {
	
	// Context struct has RenderWindow, Texture, Font, PlayerControl, MusicPlayer, and SoundPlayer as parameters
	State::Context::Context(sf::RenderWindow & window, 
		TextureManager & textures, 
		PlayerControl & player,
		MusicPlayer& music,
		SoundPlayer& sound)
		: window(&window)
		, textures(&textures)
		, player(&player)
		, music(&music)
		, sound(&sound)
	{}

	// Constructor has StateStack by reference and Context as a parameter
	// It initializes all member variables
	State::State(StateStack & stack, Context context)
		: stack_(&stack)
		, context_(context)
	{}

	// Defaul destructor
	State::~State()
	{}

	// This method requests adding states from the active stack
	void State::requestStackPush(GEX::StateID stateID)
	{
		stack_->pushState(stateID);
	}

	// This method requests removing states from the active stack
	void State::requestStackPop()
	{
		stack_->popState();
	}

	// This method requests completely emptying the active stack
	void State::requestStackClear()
	{
		stack_->clearStates();
	}

	// This getter method returns context
	State::Context State::getContext() const
	{
		return context_;
	}
}

