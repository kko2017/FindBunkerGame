//
//	Scene Node
//

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


	class SceneNode : public sf::Transformable, public sf::Drawable
	{
	public:
		using Ptr = std::unique_ptr<SceneNode>;					// ???
		/*	typedef std::unique_ptr<SceneNode> Ptr;*/			// another way
		using Pair = std::pair<SceneNode*, SceneNode*>;

	public:
								SceneNode(Category::Type category = Category::Type::None);
		virtual				    ~SceneNode() = default;

								SceneNode(const SceneNode&) = delete;
		SceneNode&				operator=(SceneNode&) = delete;

		void					attachChild(Ptr child);
		Ptr						detachChild(const SceneNode& ptr);

		void					update(sf::Time dt, CommandQueue& commands);

		sf::Vector2f			getWorldPosition() const;
		sf::Transform			getWorldTransform() const;
		//9.20
		void					onCommand(const Command& command, sf::Time dt);
		virtual unsigned int	getCategory() const;

		//10.17
		virtual sf::FloatRect	getBoundingBox() const;

		//10.18
		void					checkSceneCollision(SceneNode& rootNode, std::set<Pair>& collisionPair);
		void					checkNodeCollision(SceneNode& node, std::set<Pair>& collisionPair);

		virtual bool			isDestroyed() const;
		//10.22
		virtual bool			isMarkedForRemoval() const;
		void					removeWrecks();

//10.4
	protected:
		// update the tree
		virtual void			updateCurrent(sf::Time dt, CommandQueue& commands);
		void					updateChildren(sf::Time dt, CommandQueue& commands);
		//10.4
	private:
		// draw the tree
		virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const;	//renderTarget means window
	   //void		draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
		void					drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;



	private:
		SceneNode *			parent_;
		std::vector<Ptr>	children_;

		//10.11
		Category::Type		defaultCategory_;

	};

	//10.17
	float	distance(const SceneNode& lhs, const SceneNode& rhs);
	//10.18
	bool	collision(const SceneNode& lhs, const SceneNode& rhs);
}

