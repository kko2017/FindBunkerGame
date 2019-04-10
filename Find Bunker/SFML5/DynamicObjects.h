#pragma once
#include "Entity.h"
#include "Command.h"
#include "Animation2.h"
#include "ResourceIdentifiers.h"

#include <SFML/Graphics/Sprite.hpp>
#include <map>


namespace GEX {

	class TextureManager;
	class TextNode;

	class DynamicObjects : public Entity
	{
	public:
		enum class Type
		{
			Character,
			RedCarToRight,
			WhiteCarToRight,
			TruckToRight,
			RedCarToLeft,
			WhiteCarToLeft,
			TruckToLeft,
			BusToLeft,
			Boy,
			Girl,
			Police
		};

		enum class State {
			Up,
			Down,
			Left,
			Right,
			Dead,
			Drive
		};

	public:
		DynamicObjects(Type type, const TextureManager& textures);
		~DynamicObjects() = default;

		unsigned int	getCategory() const override;
		sf::FloatRect	getBoundingBox() const override;
		virtual			void accelerate(sf::Vector2f velocity) override;

		void			setState(State state);
		bool			finishedDeadAnimation() const;
		bool			isMarkedForRemoval() const override;
		void			playLocalSound(CommandQueue& commands,
										SoundEffectID effect);						// Plays the sound for specific action of the objects

	private:
		void			updateStates();
		void			updateCurrent(sf::Time dt, GEX::CommandQueue& commands) override;
		void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

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
