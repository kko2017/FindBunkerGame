/**
* @file
* PlayerControl.cpp
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

#include "PlayerControl.h"
#include "DynamicObjects.h"
#include "Command.h"
#include "CommandQueue.h"
#include "Category.h"

namespace GEX {

	// this struct deals with the velocity of the move of the dynamicObject
	struct DynamicObjectMover 
	{
		DynamicObjectMover(float vx, float vy)
			: velocity(vx, vy)
		{}

		void operator() (DynamicObjects& object, sf::Time dt) const 
		{
			object.accelerate(velocity);
		}
		sf::Vector2f velocity;
	};

	// Default Constructor initiallizes all member variables
	PlayerControl::PlayerControl()
		: currentMissionStatus_(MissionStatus::MissionRunning)
	{
		// set up bindings
		keyBindings_[sf::Keyboard::Left] = Action::MoveLeft;
		keyBindings_[sf::Keyboard::Right] = Action::MoveRight;
		keyBindings_[sf::Keyboard::Up] = Action::MoveUp;
		keyBindings_[sf::Keyboard::Down] = Action::MoveDown;

		// set up action bindings
		initializeAction();
	}
	 
	// handleEvent function reacts SFML events
	// Event by reference passes the original one to the ins
	// so, if I change the instance of Event, the original one is also changed.
	// Reference prevents from creating unnecessary copy.
	void PlayerControl::handleEvent(const sf::Event & event, CommandQueue & commands)
	{
		if (event.type == sf::Event::KeyPressed) 
		{
			auto found = keyBindings_.find(event.key.code);
			if (found != keyBindings_.end()) 
			{
				commands.push(actionBindings_[found->second]);
			}
		}
	}

	// handleRealTimeInput function handles real-time input
	void PlayerControl::handleRealtimeInput(CommandQueue & commands)
	{
		// traverse all assigned keys, look up action, generate command
		for (auto pair : keyBindings_) 
		{
			if (sf::Keyboard::isKeyPressed(pair.first) && isRealTimeAction(pair.second)) 
			{
				commands.push(actionBindings_[pair.second]);
			}
		}
	}

	// Setter for mission status
	void PlayerControl::setMissionStatus(MissionStatus status)
	{
		currentMissionStatus_ = status;
	}

	// Getter for mission status
	MissionStatus PlayerControl::getMissionStatus() const
	{
		return currentMissionStatus_;
	}

	// isRealTimeAction checks real-time action
	bool PlayerControl::isRealTimeAction(Action action) 
	{
		switch (action) 
		{
		case Action::MoveLeft:
		case Action::MoveRight:
		case Action::MoveUp:
		case Action::MoveDown:
			return true;
			break;
		default:
			return false;
			break;
		}
	}

	// intializeAction function sets all movements
	void PlayerControl::initializeAction()
	{
		const float playerSpeed = 200.f;

		actionBindings_[Action::MoveLeft].action = derivedAction<DynamicObjects>(DynamicObjectMover(-playerSpeed, 0.f));
		actionBindings_[Action::MoveRight].action = derivedAction<DynamicObjects>(DynamicObjectMover(+playerSpeed, 0.f));
		actionBindings_[Action::MoveUp].action = derivedAction<DynamicObjects>(DynamicObjectMover(0.f, -playerSpeed));
		actionBindings_[Action::MoveDown].action = derivedAction<DynamicObjects>(DynamicObjectMover(0.f, +playerSpeed));

		for (auto& pair : actionBindings_) 
		{
			pair.second.category = Category::Character;
		}		
	}

}