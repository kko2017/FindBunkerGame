#include "Utility.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <cassert>

#define _USE_MATH_DEFINES		// use math defines first that is preprocessor.
#include <cmath>				// put it on it second
#ifndef M_PI
#define M_PI (3.141592)
#endif

//10.23
#include <random>				// use random distribution engine

//10.23
namespace {						// unanimous namespace
	std::default_random_engine createRandomEngine() {
		auto seed = static_cast<unsigned long>(std::time(nullptr));
		return std::default_random_engine(seed);
	}
	auto RandomEngine = createRandomEngine();
}

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

float toDegree(float radian)
{
	return 180.f / static_cast<float>(M_PI) * radian;
}

float toRadian(float degree)
{
	return static_cast<float>(M_PI) / 180 * degree;
}

//10.23
int randomInt(int exclusiveMax)
{
	std::uniform_int_distribution<> distr(0, exclusiveMax - 1);
	return distr(RandomEngine);
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