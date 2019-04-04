#pragma once
#include "Entity.h"
#include "TextureManager.h"

#include <vector>

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
		
		unsigned int						getCategory() const override;
		sf::FloatRect						getBoundingBox() const override;

		std::vector<std::pair<float, float>>	getObjectPosition();


	private:
		void								drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		Type								type_;
		sf::Sprite							sprite_;

		std::vector<std::pair<float, float>>	signPostPosition_;
		std::vector<std::pair<float, float>>	bunkerPosition_;
	};

}

