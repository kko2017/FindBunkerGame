

#pragma once
#include "SceneNode.h"

namespace GEX {

	class Entity : public SceneNode
	{
	public:
		explicit			Entity(bool alive);

		void				setVelocity(sf::Vector2f velocity);
		void				setVelocity(float vx, float vy);

		sf::Vector2f		getVelocity() const;

		virtual void		accelerate(sf::Vector2f velocity);
		void				accelerate(float vx, float vy);

		void				destroy();
		bool				isAlive() const;
		bool				isDestroyed() const override;

		virtual void		remove();

	protected:
		void		updateCurrent(sf::Time dt, CommandQueue& commands) override;		// transformabel move()

	private:
		sf::Vector2f		velocity_;
		bool				alive_;
		bool				dead_;
	};

}

