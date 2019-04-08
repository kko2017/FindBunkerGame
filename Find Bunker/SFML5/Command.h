//
//

#pragma once
#include <SFML/System/Time.hpp>
#include <functional>				// for functor, function operator
#include <cassert>

//9.20

namespace GEX {

	// forward declaration
	class SceneNode;	// full decoration

	struct Command
	{
		Command();		
		std::function<void(SceneNode&, sf::Time)>	action;						// function pointer
		unsigned int								category;					// bit UpperField, enumeration

	};

	template <typename GameObject, typename Function>							// template means place holder
	std::function<void(SceneNode&, sf::Time)> derivedAction(Function fn) {
		return [=](SceneNode& node, sf::Time dt) {

			assert(dynamic_cast<GameObject*>(&node) != nullptr);

			fn(static_cast<GameObject&>(node), dt);
		};
	}

}
