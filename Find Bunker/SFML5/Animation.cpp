/**
* @file
* Animation.cpp
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

#include "Animation.h"

#include <SFML/Graphics/RenderTarget.hpp>

// Default constructor initiallizes the member variables
GEX::Animation::Animation()
	: sprite_()
	, frameSize_()
	, numberOfFrames_(0)
	, currentFrame_(0)
	, duration_(sf::Time::Zero)
	, elapsedTime_(sf::Time::Zero)
	, repeat_(false)
{}

// Copy constructor initiallizes the member variables
GEX::Animation::Animation(const sf::Texture & texture)
	: sprite_(texture)
	, frameSize_()
	, numberOfFrames_(0)
	, currentFrame_(0)
	, duration_(sf::Time::Zero)
	, elapsedTime_(sf::Time::Zero)
	, repeat_(false)
{}

// Setter of the frame size
void GEX::Animation::setFrameSize(sf::Vector2i frameSize)
{
	frameSize_ = frameSize;
}

// Getter of the frame size
sf::Vector2i GEX::Animation::getFrameSize() const
{
	return frameSize_;
}

// Setter of the number of frames
void GEX::Animation::setNumFrames(std::size_t numFrames)
{
	numberOfFrames_ = numFrames;
}

// Getter of the number of frames
std::size_t GEX::Animation::getNumFrames() const
{
	return numberOfFrames_;
}

// Setter of the duration
void GEX::Animation::setDuration(sf::Time duration)
{
	duration_ = duration;
}

// Getter of the duration
sf::Time GEX::Animation::getDuration() const
{
	return duration_;
}

// Set repeating animation
void GEX::Animation::setRepeating(bool flag)
{
	repeat_ = flag;
}

// if the animation of the entity is repeating, then it is ture
bool GEX::Animation::isRepeating() const
{
	return repeat_;
}

// Restart the animation
void GEX::Animation::restart()
{
	currentFrame_ = 0;
}

// Checks whether or not game is finished
bool GEX::Animation::isFinished() const
{
	return currentFrame_ >= numberOfFrames_;
}

// Get local bounds of animation
sf::FloatRect GEX::Animation::getLocalBounds() const
{
	return sf::FloatRect(getOrigin(), static_cast<sf::Vector2f>(getFrameSize()));
}

// Get global bounds of animation
sf::FloatRect GEX::Animation::getGlobalBounds() const
{
	return getTransform().transformRect(getLocalBounds());
}

// Update the animation
void GEX::Animation::update(sf::Time dt)
{
	sf::Time timePerFrame = duration_ / static_cast<float>(numberOfFrames_);
	elapsedTime_ += dt;

	sf::Vector2i textureBounds(sprite_.getTexture()->getSize());
	sf::IntRect textureRect = sprite_.getTextureRect();

	if (currentFrame_ == 0)
		textureRect = sf::IntRect(0, 0, frameSize_.x, frameSize_.y);

	while (elapsedTime_ >= timePerFrame && (currentFrame_ <= numberOfFrames_ || repeat_)) {
		// move to next frame
		textureRect.left += textureRect.width;

		// got to next row if needed
		if (textureRect.left + textureRect.width > textureBounds.x) {
			textureRect.left = 0;
			textureRect.top += textureRect.height;
		}

		elapsedTime_ -= timePerFrame;

		if (repeat_) {
			currentFrame_ = (currentFrame_ + 1) % numberOfFrames_;
			if (currentFrame_ == 0)
				textureRect = sf::IntRect(0, 0, frameSize_.x, frameSize_.y);
		}
		else {
			currentFrame_++;
		}
	}

	sprite_.setTextureRect(textureRect);

}

// This draw method is overriden by draw() in sf::Drawable
void GEX::Animation::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(sprite_, states);
}


