#pragma once
#include "State.h"

class ScoreState : public GEX::State
{
public:
	ScoreState(GEX::StateStack& stack, Context context);

	void						draw() override;
	bool						update(sf::Time dt) override;
	bool						handleEvent(const sf::Event& event) override;

private:
	void						setScoreText(Context context);
	void						setScore();

private:
	sf::Sprite					backgroundSprite_;
	sf::Text					pressKeyText_;
	sf::Text					scoreText_;
	bool						showText_;
	sf::Time					textEffectTime_;
	std::string					score_;
};

