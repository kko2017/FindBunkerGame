#pragma once
#include "Entity.h"
#include "TextureManager.h"

namespace GEX {

	class StaticObjects : public Entity
	{
	public:
		enum class Type {
			SignPost,
			Bunker,
		};

	public:
						StaticObjects(Type type, const TextureManager& textures);
						~StaticObjects() = default;
		
		unsigned int	getCategory() const override;
		sf::FloatRect	getBoundingBox() const override;

	private:
		void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		Type			type_;
		sf::Sprite		sprite_;

	};

}

