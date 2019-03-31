#include "Animation2.h"



GEX::Animation2::Animation2(bool repeat)
	: currentFrame_(0)
	, duration_(sf::Time::Zero)
	, elapsedTime_(sf::Time::Zero)
	, repeat_(repeat)
{}

void GEX::Animation2::addFrame(Frame frame)
{
	frames_.emplace_back(frame);
}

void GEX::Animation2::addFrameSet(std::vector<Frame> frames)
{
	frames_ = frames;
}


void GEX::Animation2::setDuration(sf::Time duration)
{
	duration_ = duration;
}

sf::Time GEX::Animation2::getDuration() const
{
	return duration_;
}

void GEX::Animation2::setRepeating(bool flag)
{
	repeat_ = flag;
}

bool GEX::Animation2::isRepeating() const
{
	return repeat_;
}

void GEX::Animation2::restart()
{
	currentFrame_ = 0;
}

bool GEX::Animation2::isFinished() const
{
	return (!repeat_ && currentFrame_ >= frames_.size());
}

Frame GEX::Animation2::getCurrentFrame() const
{
	return frames_[currentFrame_ >= frames_.size() ? frames_.size() - 1 : currentFrame_];
}


Frame GEX::Animation2::update(sf::Time dt)
{
	sf::Time timePerFrame = duration_ / static_cast<float>(frames_.size());
	elapsedTime_ += dt;

	// while we have a frame to progress
	while (elapsedTime_ >= timePerFrame && (currentFrame_ < frames_.size() || repeat_)) {
		
		// And progress to next frame
		elapsedTime_ -= timePerFrame;
		currentFrame_++;

		if (repeat_) {
			currentFrame_ %= frames_.size();
				
		}
	}

	return getCurrentFrame();
}