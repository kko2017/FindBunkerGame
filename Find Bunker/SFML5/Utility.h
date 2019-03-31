#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include "Animation.h"

namespace sf {
	class Sprite;
	class Text;
}


void centerOrigin(sf::Sprite& sprite);
void centerOrigin(sf::Text& text);
//10.26
void centerOrigin(GEX::Animation& animation);

//10.4
// Degree and radian conversion
float toDegree(float radian);
float toRadian(float degree);

// Random number generation
int randomInt(int exclusiveMax);

// Vector operation
float length(sf::Vector2f vector);
sf::Vector2f unitVector(sf::Vector2f vector);

