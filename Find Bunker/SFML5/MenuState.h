//
//
#pragma once

#include "State.h"


class MenuState : public GEX::State
{
public:
	MenuState(GEX::StateStack& stack, Context context);

	void			draw() override;
	bool			update(sf::Time dt) override;
	bool			handleEvent(const sf::Event& event) override;

	void			updateOptionText();

private:
	enum OptionName {
		Play = 0,
		Exit
	};

	sf::Sprite				backgroundSprite_;

	std::vector<sf::Text>	options_;					// less than a size of text
	std::size_t				optionsIndex_;				// index of array

};

