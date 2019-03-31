#include "MenuState.h"
#include "Utility.h"
#include "FontManager.h"


MenuState::MenuState(GEX::StateStack & stack, Context context)
	: State(stack, context)
	, options_()
	, optionsIndex_(0)
{
	sf::Texture& texture = context.textures->get(GEX::TextureID::TitleScreen);
	

	backgroundSprite_.setTexture(texture);

	// set up menu


	// play option
	sf::Text playOption;
	playOption.setFillColor(sf::Color::Black);
	playOption.setOutlineColor(sf::Color::Red);
	playOption.setOutlineThickness(3.5f);
	playOption.setStyle(sf::Text::Italic);
	playOption.setCharacterSize(80);
	playOption.setFont(GEX::FontManager::getInstance().get(GEX::FontID::Main));
	playOption.setString("Play");
	centerOrigin(playOption);
	playOption.setPosition(context.window->getView().getSize() / 2.f);
	options_.push_back(playOption);

	// exit option
	sf::Text exitOption;
	exitOption.setFillColor(sf::Color::Black);
	exitOption.setOutlineColor(sf::Color::Red);
	exitOption.setOutlineThickness(3.5f);
	exitOption.setStyle(sf::Text::Italic);
	exitOption.setCharacterSize(80);
	exitOption.setFont(GEX::FontManager::getInstance().get(GEX::FontID::Main));
	exitOption.setString("Exit");
	centerOrigin(exitOption);
	exitOption.setPosition(playOption.getPosition() + sf::Vector2f(0.f, 80.f));
	options_.push_back(exitOption);

	updateOptionText();
}

void MenuState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	
	window.setView(window.getDefaultView());	
	window.draw(backgroundSprite_);

	for (const sf::Text& text : options_) {
		window.draw(text);
	}

}

bool MenuState::update(sf::Time dt)
{
	return true;
}

bool MenuState::handleEvent(const sf::Event & event)
{
	if (event.type != sf::Event::KeyPressed)
		return true;

	if (event.key.code == sf::Keyboard::Return) {
		if (optionsIndex_ == Play) {
			requestStackPop();
			requestStackPush(GEX::StateID::Game);
		}
		else if (optionsIndex_ == Exit) {
			requestStackPop();
		}
	}
	else if (event.key.code == sf::Keyboard::Up) {
		if (optionsIndex_ > 0)
			optionsIndex_--;
		else
			optionsIndex_ = options_.size() - 1;

		updateOptionText();
	}
	else if (event.key.code == sf::Keyboard::Down) {
		if (optionsIndex_ < options_.size() - 1)
			optionsIndex_++;
		else
			optionsIndex_ = 0;

		updateOptionText();
	}

	return true;
}

void MenuState::updateOptionText()
{
	if (options_.empty())
		return;

	for (sf::Text& text : options_) {
		text.setFillColor(sf::Color::White);
		text.setOutlineColor(sf::Color::Black);
	}

	options_[optionsIndex_].setFillColor(sf::Color::Magenta);

}
