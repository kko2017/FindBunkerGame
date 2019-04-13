/**
* @file
* PlayerControl.h
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
#include <map>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include "Command.h"
#include "Category.h"


namespace GEX {

	// forward declartion
	class CommandQueue;

	enum class Action {				// Scoped enum class is made for specific identifiers in actions
		MoveLeft,
		MoveRight,
		MoveUp,
		MoveDown,
	};

	enum class MissionStatus {		// Scoped enum class is made for specific identifiers in mission status
		MissionRunning,
		MissionSuccess,
		MissionFailure
	};


	class PlayerControl
	{
	public:
						PlayerControl();												// Default Constructor			

		void			handleEvent(const sf::Event& event, CommandQueue& commands);	// handleEvent function reacts SFML events
																						// Event by reference passes the original one to the ins
																						// so, if I change the instance of Event, the original one is also changed.
																						// Reference prevents from creating unnecessary copy.

		void			handleRealtimeInput(CommandQueue& commands);					// handleRealTimeInput function handles real-time input

		void			setMissionStatus(MissionStatus status);							// Setter for mission status
		MissionStatus	getMissionStatus() const;										// Getter for mission status

	private:
		void			initializeAction();												// intializeAction function sets all movements
		static bool		isRealTimeAction(Action action);								// isRealTimeAction checks real-time action
																						
	private:
		std::map<sf::Keyboard::Key, Action>		keyBindings_;
		std::map<Action, Command>				actionBindings_;
		MissionStatus							currentMissionStatus_;
	};

}