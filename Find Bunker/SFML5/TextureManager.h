#pragma once
//
// Texture Manager:
// manage game resoures

#pragma once
#include <map>	   // container
#include <memory> // for using smart pointer 
#include <SFML/Graphics.hpp>
#include "ResourceIdentifiers.h"

namespace GEX {

	
	class TextureManager
	{
	public:
		TextureManager();
		~TextureManager();

		void				load(TextureID id, const std::string& path);   // no need to copy string thats why use &.
		sf::Texture&		get(TextureID id) const;

	private:
		std::map<TextureID, std::unique_ptr<sf::Texture>>	textures_;
	};
}

