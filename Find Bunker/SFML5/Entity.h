

#pragma once
#include "SceneNode.h"

namespace GEX {

	// Entity inherits from SceneNode.
	class Entity : public SceneNode
	{
	public:
		explicit			Entity(int points);

		void				setVelocity(sf::Vector2f velocity);
		void				setVelocity(float vx, float vy);

		sf::Vector2f		getVelocity() const;

		virtual void		accelerate(sf::Vector2f velocity);
		void				accelerate(float vx, float vy);
		//9.26
		void				rotate(float r);

		//10.3
		int					getHitpoints() const;
		void				repair(int points);
		void				destroy();
		bool				isDestroyed() const override;

		//10.22, 10.26 -- add virtual
		virtual void				remove();

//10.4
	protected:
		void		updateCurrent(sf::Time dt, CommandQueue& commands) override;		// transformabel move()

	private:
		sf::Vector2f		velocity_;
		//9.26
		float				rotate_;

		//10.3
		int					hitpoints_;
	};

}

