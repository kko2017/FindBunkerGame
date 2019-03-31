#include "Animation.h"

#include <SFML/Graphics/RenderTarget.hpp>


GEX::Animation::Animation()
	: sprite_()
	, frameSize_()
	, numberOfFrames_(0)
	, currentFrame_(0)
	, duration_(sf::Time::Zero)
	, elapsedTime_(sf::Time::Zero)
	, repeat_(false)
{}

GEX::Animation::Animation(const sf::Texture & texture)
	: sprite_(texture)
	, frameSize_()
	, numberOfFrames_(0)
	, currentFrame_(0)
	, duration_(sf::Time::Zero)
	, elapsedTime_(sf::Time::Zero)
	, repeat_(false)
{}

void GEX::Animation::setTexture(const sf::Texture & texture)
{
	sprite_.setTexture(texture);
}

const sf::Texture * GEX::Animation::getTexture() const
{
	return sprite_.getTexture();
}

void GEX::Animation::setFrameSize(sf::Vector2i frameSize)
{
	frameSize_ = frameSize;
}

sf::Vector2i GEX::Animation::getFrameSize() const
{
	return frameSize_;
}

void GEX::Animation::setNumFrames(std::size_t numFrames)
{
	numberOfFrames_ = numFrames;
}

std::size_t GEX::Animation::getNumFrames() const
{
	return numberOfFrames_;
}

void GEX::Animation::setDuration(sf::Time duration)
{
	duration_ = duration;
}

sf::Time GEX::Animation::getDuration() const
{
	return duration_;
}

void GEX::Animation::setRepeating(bool flag)
{
	repeat_ = flag;
}

bool GEX::Animation::isRepeating() const
{
	return repeat_;
}

void GEX::Animation::restart()
{
	currentFrame_ = 0;
}

bool GEX::Animation::isFinished() const
{
	return currentFrame_ >= numberOfFrames_;
}

sf::FloatRect GEX::Animation::getLocalBounds() const
{
	return sf::FloatRect(getOrigin(), static_cast<sf::Vector2f>(getFrameSize()));
}

sf::FloatRect GEX::Animation::getGlobalBounds() const
{
	return getTransform().transformRect(getLocalBounds());
}

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

void GEX::Animation::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(sprite_, states);
}


