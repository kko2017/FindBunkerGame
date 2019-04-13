/**
* @file
* Command.h
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
#include <SFML/System/Time.hpp>
#include <functional>				// for functor, function operator
#include <cassert>

namespace GEX {

	// forward declaration
	class SceneNode;

	struct Command
	{
		Command();																// default constuctor
		std::function<void(SceneNode&, sf::Time)>	action;						// function object can be called on any object represented by a SceneNode
		unsigned int								category;					// category bits

	};

	template <typename GameObject, typename Function>
	std::function<void(SceneNode&, sf::Time)> derivedAction(Function fn) {
		return [=](SceneNode& node, sf::Time dt) {

			assert(dynamic_cast<GameObject*>(&node) != nullptr);				// Assert checks if cast is not null pointer

			fn(static_cast<GameObject&>(node), dt);								// downcast node and invoke function on it
		};
	}

}
