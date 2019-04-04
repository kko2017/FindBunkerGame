#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include "Animation.h"

namespace sf {
	class Sprite;
	class Text;
}

void centerOrigin(sf::Sprite& sprite);
void centerOrigin(sf::Text& text);
void centerOrigin(GEX::Animation& animation);

// Vector operation
float length(sf::Vector2f vector);
sf::Vector2f unitVector(sf::Vector2f vector);

