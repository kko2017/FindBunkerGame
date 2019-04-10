// 10.22
//
#pragma once
#include "State.h"

class GameOverState : public GEX::State
{
public:
	GameOverState(GEX::StateStack& stack, Context context);


	void			draw() override;
	bool	update(sf::Time dt) override;
	bool			handleEvent(const sf::Event& event) override;

private:
	sf::Text		gameOverText_;
	sf::Text		text_;
	sf::Time		elapsedTime_;
};

