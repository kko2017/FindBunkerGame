/**
* @file
* SoundNode.cpp
* @author
* Kwangeun Oh
* @version 1.0
*
*
* @DESCRIPTION
* This is the Find Bunker game
*
* @section LICENSE
*
*
* Copyright 2019
* Permission to use, copy, modify, and/or distribute this software for
* any purpose with or without fee is hereby granted, provided that the
* above copyright notice and this permission notice appear in all copies.
*
* THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
* WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
* ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
* WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
* ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
* OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*
* @section Academic Integrity
* I certify that this work is solely my own and complies with
* NBCC Academic Integrity Policy (policy 1111)
*/

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
