/**
* @file
* State.h
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
#include "TextureManager.h"
#include "StateIdentifier.h"
#include "CommandQueue.h"
#include "MusicPlayer.h"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <memory>


namespace GEX {
	// forward declarations
	class PlayerControl;
	class StateStack;
	class SoundPlayer;

	class State
	{
	public:
		typedef std::unique_ptr<State> Ptr;			// Unique pointer to State is defined as Ptr

		struct Context {							// Every screen needs to display some texts, sprites, draw to screen
													// And also we should avoid unnecessary memory wasting by loading same texture, font, player music, or sound
			Context(sf::RenderWindow& window, 		// Because of that fact, Context struct is created
				TextureManager& textures, 			
				PlayerControl& player, 
				MusicPlayer& music,
				SoundPlayer& sound);

			sf::RenderWindow*	window;
			TextureManager*		textures;
			PlayerControl*		player;
			MusicPlayer*		music;
			SoundPlayer*		sound;
		};

	public:
							State(StateStack& stack, Context context);		// Constructor has StateStack by reference and Context as a parameter
		virtual				~State();										// Virtual destructor

		virtual void		draw() = 0;										// Virtual abstract function for draw 
		virtual bool		update(sf::Time) = 0;							// Virtual abstract function for update
		virtual bool		handleEvent(const sf::Event&) = 0;				// Virtual abstract function for handling events


	protected:
		void				requestStackPush(StateID stateID);				// This method requests adding states from the active stack
		void				requestStackPop();								// This method requests removing states from the active stack
		void				requestStackClear();							// This method requests completely emptying the active stack

		Context				getContext() const;								// This getter method returns context

	private:
		StateStack*			stack_;
		Context				context_;

	};

}

