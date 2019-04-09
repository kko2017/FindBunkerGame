#pragma once

#include "State.h"

class PauseState : public GEX::State
{
public:
					PauseState(GEX::StateStack& stack, Context context);
					~PauseState();											
	void			draw() override;
	bool			update(sf::Time dt) override;
	bool			handleEvent(const sf::Event& event) override;

private:
	sf::Text		pausedText_;
	sf::Text		instructionText_;

};

