#include "Utility.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <cassert>
#include <random>				// use random distribution engine

void centerOrigin(sf::Sprite& sprite) {
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}


void centerOrigin(sf::Text& text) {
	sf::FloatRect bounds = text.getLocalBounds();
	text.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void centerOrigin(GEX::Animation & animation)
{
	sf::FloatRect bounds = animation.getLocalBounds();
	animation.setOrigin(std::floor(bounds.width / 2.f), std::floor(bounds.height / 2.f));	// The reason we use std::floor is for truncation.
}

float length(sf::Vector2f vector)
{
	return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}

sf::Vector2f unitVector(sf::Vector2f vector)
{
	assert(vector != sf::Vector2f(0.f, 0.f));

	return vector / length(vector);
}