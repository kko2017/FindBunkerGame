/**
* @file
* StateStack.h
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
#include "StateIdentifier.h"
#include "State.h"
#include <functional>
#include <cassert>

// Turning the active state into a stack means that the current state is not a individual state anymore.
// For instance, the pause screen is not only displayed on the screen.
// The game screen is still shown in the background without motion, even if the pause screen is activated.
// To manage states efficiently and in an easy way, we create StateStack class.


namespace sf
{
	class Event;
	class RenderWindow;
}

namespace GEX {


	class StateStack
	{
	public:

		enum class Action {											// Action enum class is a scoped enumeration. Push, pop and clear are inside of the scope
			Push,
			Pop,
			Clear
		};

	public:

		explicit			StateStack(State::Context context);		// Contstructor has Context as parameter. In order to prevent from implicit conversion and copy initialization
																	// use explicit keyword
							~StateStack();							// Default Destructor

		template <typename T>
		void				registerState(GEX::StateID stateID);	// This function registers the derived state class

		void				update(sf::Time dt);					// The update function
		void				draw();									// The draw function
		void				handleEvent(const sf::Event& event);	// This function handles event

		void				pushState(GEX::StateID stateID);		// This function is for adding states
		void				popState();								// This function is for removing states
		void				clearStates();							// This function is for clearing states

		bool				isEmpty() const;						// This function checks if the stack is empty

	private:
		State::Ptr			createState(GEX::StateID stateID);		// This method takes an ID of a state, and returns a smart pointer to a newly created object of the corresponding state class
		void				applyPendingChanges();					// This method applys pendingChanges to the stack


	private:
		struct PendingChange {										// PendingChange struct is made for delayed processing operations done
			explicit		PendingChange(Action action, 			// Constructor has Action and StateID as a parameter
							StateID stateID = GEX::StateID::None);	// and use keyword explicit for prevention from implicit convention and copy intialization

			Action			action;
			GEX::StateID	stateID;
		};

	private:
		std::vector<State::Ptr>									stack_;
		std::vector<PendingChange>								pendingList_;
		State::Context											context_;
		std::map < GEX::StateID, std::function<State::Ptr()>>	factories_;

	};

	template <typename T>										// Template parameter T is the derived class we want to register
	void StateStack::registerState(GEX::StateID stateID) {		// This member function inserts mappings
		factories_[stateID] = [this]() {						// Lamda expression acts like a factory for the state
																// This lamda is assigned to the corresponding stateID in the map
			return State::Ptr(new T(*this, context_)); 			// It creates an object of the derived class T by passing StateStack and Context to its constructor
		};														// This object is wrapped into a unique pointer and returned as a base class pointer
	}


}