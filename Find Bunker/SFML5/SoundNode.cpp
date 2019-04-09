#include "SoundNode.h"
#include "SoundPlayer.h"

// explicit constructor passes the instance of SoundPlayer as parameter
// it initiallizes all member variables
GEX::SoundNode::SoundNode(SoundPlayer & player)
	: SceneNode()
	, sounds_(player)
{}

// identify the sound and set up the position of it
void GEX::SoundNode::playSound(SoundEffectID sound, sf::Vector2f position)
{
	sounds_.play(sound, position);
}

// get category type
unsigned int GEX::SoundNode::getCategory() const
{
	return Category::Type::SoundEffect;
}
