#pragma once
#include "State.h"

class IntroState : public GEX::State
{
public:
	IntroState(GEX::StateStack& stack, Context context);

	void						draw() override;
	bool						update(sf::Time dt) override;
	bool						handleEvent(const sf::Event& event) override;

private:
	void						setIntroText(Context context);

private:
	sf::Sprite					backgroundSprite_;
	sf::Text					pressKeyText_;
	sf::Text					scoreText_;
	bool						showText_;
	sf::Time					textEffectTime_;
};

