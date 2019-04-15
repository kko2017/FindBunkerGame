/**
* @file
* SceneNode.cpp
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

#include "SceneNode.h"
#include <algorithm>
#include <cassert>
#include "Category.h"
#include "Command.h"
#include "Utility.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace GEX
{
	// Constructor passes the category type as parameter
	// It initiallizes all member variables
	SceneNode::SceneNode(Category::Type category)
		: children_()
		, parent_(nullptr)
		, defaultCategory_(category)
	{}

	// attach the child to the container
	void SceneNode::attachChild(Ptr child)
	{
		child->parent_ = this;
		children_.push_back(std::move(child));
	}

	// detatch the child from the container
	SceneNode::Ptr SceneNode::detachChild(const SceneNode& node)
	{
		auto found = std::find_if(children_.begin(), children_.end(),
			[&](Ptr& p) {return &node == p.get(); });

		assert(found != children_.end());

		Ptr result = std::move(*found);
		children_.erase(found);

		return result;
	}

	// virtual function draws current SceneNode
	void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
	{
		// default to do nothing
	}

	// draws children SceneNode
	void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (const Ptr& child : children_)
			child->draw(target, states);

	}

	// virtual function draws all SceneNode
	void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		drawCurrent(target, states);
		drawChildren(target, states);
	}

	// update current scene and children scene
	void SceneNode::update(sf::Time dt, CommandQueue& commands) 
	{
		updateCurrent(dt, commands);
		updateChildren(dt, commands);
	}

	// virtual fuction updates the current scene
	void SceneNode::updateCurrent(sf::Time dt, CommandQueue& commands)
	{
		// default to do nothing
	}

	// update the children scene
	void SceneNode::updateChildren(sf::Time dt, CommandQueue& commands)
	{
		for (Ptr& child : children_)  // no const
			child->update(dt, commands);
	}

	// get the world position
	sf::Vector2f SceneNode::getWorldPosition() const
	{
		return getWorldTransform() * sf::Vector2f();
	}

	// get the world transform
	sf::Transform SceneNode::getWorldTransform() const
	{
		sf::Transform transform = sf::Transform::Identity;	// identity is a kinda starting point. it does nothing.

		for (const SceneNode* node = this; node != nullptr; node = node->parent_)
			transform = node->getTransform() * transform;

		return transform;
	}

	// get the bounding box of entities
	sf::FloatRect SceneNode::getBoundingBox() const
	{
		return sf::FloatRect();
	}

	// verify colliding nodes with each other
	// visit every single node, then calls checkNodeCollision()
	void SceneNode::checkSceneCollision(SceneNode & rootNode, std::set<Pair>& collisionPair)
	{
		checkNodeCollision(rootNode, collisionPair);
		for (Ptr& c : rootNode.children_)
			checkSceneCollision(*c, collisionPair);
	}

	// verify colliding nodes with each other
	void SceneNode::checkNodeCollision(SceneNode & node, std::set<Pair>& collisionPair)
	{
		if (this != &node && collision(*this, node) && !isDestroyed() && !node.isDestroyed())
			collisionPair.insert(std::minmax(this, &node));

		for (Ptr& c : children_)
			c->checkNodeCollision(node, collisionPair);
	}

	// checks whether the object is destroyed
	bool SceneNode::isDestroyed() const
	{
		return false;
	}

	// checks whether the object is marked for removal
	bool SceneNode::isMarkedForRemoval() const
	{
		return isDestroyed();
	}

	// remove wrecks verified after calling the isMarkedForRemoval
	void SceneNode::removeWrecks()
	{
		auto wreckUpperFieldBegin = std::remove_if(children_.begin(), children_.end(), std::mem_fn(&SceneNode::isMarkedForRemoval));
		children_.erase(wreckUpperFieldBegin, children_.end());

		std::for_each(children_.begin(), children_.end(), std::mem_fn(&SceneNode::removeWrecks));
	}

	// this function is called every time Command is passed to the SceneNode
	void SceneNode::onCommand(const Command & command, sf::Time dt)
	{
		// Command current node, if category matches
		if(command.category & getCategory())
			command.action(*this, dt);

		// Command children
		for (Ptr& child : children_)
			child->onCommand(command, dt);
	}

	// get category type
	unsigned int SceneNode::getCategory() const
	{
		return defaultCategory_;
	}

	// get the distance between two Scene Nodes
	float distance(const SceneNode & lhs, const SceneNode & rhs)
	{
		return length(lhs.getWorldPosition() - rhs.getWorldPosition());
	}

	// checks whether two scene nodes collide with each other
	bool collision(const SceneNode & lhs, const SceneNode & rhs)
	{
		// to get floatRectangle, use intersects
		return lhs.getBoundingBox().intersects(rhs.getBoundingBox());
	}
}
