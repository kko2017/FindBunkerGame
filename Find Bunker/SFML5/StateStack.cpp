/**
* @file
* StateStack.cpp
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

#include "StateStack.h"

// Contstructor has Context as parameter. In order to prevent from implicit conversion and copy initialization
// use explicit keyword. It initiallizes the member variables
GEX::StateStack::StateStack(State::Context context)
	: context_(context)
	, stack_()
	, pendingList_()
	, factories_()
{}

// Default Destructor
GEX::StateStack::~StateStack()
{}

// The update function
void GEX::StateStack::update(sf::Time dt)
{
	for (auto itr = stack_.rbegin(); itr != stack_.rend(); ++itr) {
		if (!(*itr)->update(dt)) {
			break;
		}
	}
}

// The draw function
void GEX::StateStack::draw()
{
	for (State::Ptr& state : stack_) {
		state->draw();
	}
}

// This function handles event
void GEX::StateStack::handleEvent(const sf::Event & event)
{
	for (auto itr = stack_.rbegin(); itr != stack_.rend(); ++itr) {
		if ((*itr)->handleEvent(event) == false) {
			break;
		}
	}

	applyPendingChanges();
}

// This function is for adding states
void GEX::StateStack::pushState(GEX::StateID stateID)
{
	pendingList_.push_back(PendingChange(Action::Push, stateID));
}

// This function is for removing states
void GEX::StateStack::popState()
{
	pendingList_.push_back(PendingChange(Action::Pop));
}

// This function is for clearing states
void GEX::StateStack::clearStates()
{
	pendingList_.push_back(PendingChange(Action::Clear));
}

// This function checks if the stack is empty
bool GEX::StateStack::isEmpty() const
{
	return stack_.empty();
}

// This method takes an ID of a state, and returns a smart pointer to a newly created object of the corresponding state class
GEX::State::Ptr GEX::StateStack::createState(GEX::StateID stateID)
{
	auto found = factories_.find(stateID);
	assert(found != factories_.end());


	return found->second();   // adding () means like making it function for execution. not member
}

// This method applys pendingChanges to the stack
void GEX::StateStack::applyPendingChanges()
{
	for (PendingChange change : pendingList_) {
		switch (change.action) {
		case Action::Push:
			stack_.push_back(createState(change.stateID));
			break;
		case Action::Pop:
			stack_.pop_back();
			break;
		case Action::Clear:
			stack_.clear();
			break;
		}
	}

	pendingList_.clear();
}

//It initiallizes the member variables
GEX::StateStack::PendingChange::PendingChange(Action action, StateID stateID)
	: action(action)
	, stateID(stateID)
{}
