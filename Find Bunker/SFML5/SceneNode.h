/**
* @file
* SceneNode.h
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
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Time.hpp>

#include "Category.h"


#include <vector>
#include <memory>
#include <set>


namespace GEX {

	//forward declaration
	class CommandQueue;
	struct Command;


	class SceneNode : public sf::Transformable, public sf::Drawable							// inherits from Transformable class and Drawable class
	{
	public:
		using Ptr = std::unique_ptr<SceneNode>;												// Unique pointer to SceneNode is declared as Ptr
		using Pair = std::pair<SceneNode*, SceneNode*>;										// Pair method with two SceneNodes is declared as Pair

	public:
								SceneNode(Category::Type category = Category::Type::None);	// Constructor passes the category type as parameter
		virtual				    ~SceneNode() = default;										// Virtual default destructor

								SceneNode(const SceneNode&) = delete;						// Delete the copy constructor
		SceneNode&				operator=(SceneNode&) = delete;								// Neutralize the function of operator=

		void					attachChild(Ptr child);										// attach the child to the container
		Ptr						detachChild(const SceneNode& ptr);							// detatch the child from the container

		void					update(sf::Time dt, CommandQueue& commands);				// update current scene and children scene

		sf::Vector2f			getWorldPosition() const;									// get the world position
		sf::Transform			getWorldTransform() const;									// get the world transform

		void					onCommand(const Command& command, sf::Time dt);				// this function is called every time Command is passed to the SceneNode
		virtual unsigned int	getCategory() const;										// get category type

		virtual sf::FloatRect	getBoundingBox() const;										// get the bounding box of entities


		void					checkSceneCollision(SceneNode& rootNode, 
														std::set<Pair>& collisionPair);		// verify colliding nodes with each other
		void					checkNodeCollision(SceneNode& node, 
														std::set<Pair>& collisionPair);		// verify colliding nodes with each other

		virtual bool			isDestroyed() const;										// checks whether the object is destroyed
		virtual bool			isMarkedForRemoval() const;									// checks whether the object is marked for removal
		void					removeWrecks();												// remove wrecks verified after calling the isMarkedForRemoval

	protected:
		virtual void			updateCurrent(sf::Time dt, CommandQueue& commands);			// virtual fuction updates the current scene
		void					updateChildren(sf::Time dt, CommandQueue& commands);		// update the shildren scene

	private:
		virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const;			// virtual function draws all SceneNode
		virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;	// virtual function draws current SceneNode
		void					drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;	// draws children SceneNode



	private:
		SceneNode *			parent_;
		std::vector<Ptr>	children_;
		Category::Type		defaultCategory_;

	};

	float	distance(const SceneNode& lhs, const SceneNode& rhs);		// get the distance between two Scene Nodes
	bool	collision(const SceneNode& lhs, const SceneNode& rhs);		// checks whether two scene nodes collide with each other
}

