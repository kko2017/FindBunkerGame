#include "SceneNode.h"
#include <algorithm>
#include <cassert>
#include "Category.h"
#include "Command.h"
#include "Utility.h"
//10.17
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace GEX
{

	SceneNode::SceneNode(Category::Type category)
		: children_()
		, parent_(nullptr)
		, defaultCategory_(category)
	{}


	void SceneNode::attachChild(Ptr child)
	{
		child->parent_ = this;
		children_.push_back(std::move(child));
	}

	SceneNode::Ptr SceneNode::detachChild(const SceneNode& node)
	{
		auto found = std::find_if(children_.begin(), children_.end(),
			[&](Ptr& p) {return &node == p.get(); });

		assert(found != children_.end());

		Ptr result = std::move(*found);
		children_.erase(found);

		return result;
	}

	void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
	{
		// default to do nothing
	}

	void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (const Ptr& child : children_)  // const
			child->draw(target, states);

	}

	void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		drawCurrent(target, states);
		drawChildren(target, states);
	}

	void SceneNode::update(sf::Time dt, CommandQueue& commands) {
		updateCurrent(dt, commands);
		updateChildren(dt, commands);
	}

	void SceneNode::updateCurrent(sf::Time dt, CommandQueue& commands)
	{
		// default to do nothing
	}

	void SceneNode::updateChildren(sf::Time dt, CommandQueue& commands)
	{
		for (Ptr& child : children_)  // no const
			child->update(dt, commands);
	}

	sf::Vector2f SceneNode::getWorldPosition() const
	{
		return getWorldTransform() * sf::Vector2f();
	}

	sf::Transform SceneNode::getWorldTransform() const
	{
		sf::Transform transform = sf::Transform::Identity;	// identity is a kinda starting point. it does nothing.

		for (const SceneNode* node = this; node != nullptr; node = node->parent_)
			transform = node->getTransform() * transform;

		return transform;
	}

	sf::FloatRect SceneNode::getBoundingBox() const
	{
		return sf::FloatRect();
	}

	// visit every single node, then calls checkNodeCollision()
	void SceneNode::checkSceneCollision(SceneNode & rootNode, std::set<Pair>& collisionPair)
	{
		checkNodeCollision(rootNode, collisionPair);
		for (Ptr& c : rootNode.children_)
			checkSceneCollision(*c, collisionPair);
	}

	void SceneNode::checkNodeCollision(SceneNode & node, std::set<Pair>& collisionPair)
	{
		if (this != &node && collision(*this, node) && !isDestroyed() && !node.isDestroyed())
			collisionPair.insert(std::minmax(this, &node));

		for (Ptr& c : children_)
			c->checkNodeCollision(node, collisionPair);
	}

	bool SceneNode::isDestroyed() const
	{
		return false;
	}

	bool SceneNode::isMarkedForRemoval() const
	{
		return isDestroyed();
	}

	void SceneNode::removeWrecks()
	{
		auto wreckFieldBegin = std::remove_if(children_.begin(), children_.end(), std::mem_fn(&SceneNode::isMarkedForRemoval));
		children_.erase(wreckFieldBegin, children_.end());

		std::for_each(children_.begin(), children_.end(), std::mem_fn(&SceneNode::removeWrecks));
	}

	// 9.20
	void SceneNode::onCommand(const Command & command, sf::Time dt)
	{
		// Command current node, if category matches
		if(command.category & getCategory())
			command.action(*this, dt);

		// Command children
		for (Ptr& child : children_)
			child->onCommand(command, dt);
	}

	//9.20
	unsigned int SceneNode::getCategory() const
	{
		//10.11
		return defaultCategory_;
	}

	//10.17
	float distance(const SceneNode & lhs, const SceneNode & rhs)
	{
		return length(lhs.getWorldPosition() - rhs.getWorldPosition());
	}
	bool collision(const SceneNode & lhs, const SceneNode & rhs)
	{
		// to get floatRectangle, use intersects
		return lhs.getBoundingBox().intersects(rhs.getBoundingBox());
	}
}
