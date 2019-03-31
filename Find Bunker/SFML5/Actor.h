#pragma once
#include "Entity.h"
#include <SFML/Graphics/Sprite.hpp>
#include "Animation2.h"
#include <map>


namespace GEX {
	class TextureManager;
	class TextNode;

	class Actor : public GEX::Entity
	{
	public:
		enum class Type
		{
			Hero2,
			Zombie1,
			Zombie2,
			Zombie3,
			Zombie4,
			Zombie5
		};

		enum class State {
			Up,
			Down,
			Left,
			Right,
			Dead
		};

	public:
		Actor(Type type, const GEX::TextureManager& textures);
		~Actor() = default;

		unsigned int	getCategory() const override;
		sf::FloatRect	getBoundingBox() const override;
		float			getMaxSpeed() const;
		virtual			void accelerate(sf::Vector2f velocity) override;

		void			setState(State state);
		bool			isMarkedForRemoval() const override;

	private:
		void			updateStates();
		void			updateCurrent(sf::Time dt, GEX::CommandQueue& commands) override;
		void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
		void			updateMovementPattern(sf::Time dt);



	private:
		Type										type_;
		State										state_;
		mutable sf::Sprite							sprite_;
		mutable std::map<State, Animation2>			animations_;
		TextNode*									healthDisplay_;

		float										travelDistance_;
		std::size_t									directionIndex_;
		bool										attack_;

	};
}

