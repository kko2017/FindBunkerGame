#include "TitleState.h"
#include "TextureManager.h"
#include "Utility.h"
#include "FontManager.h"

TitleState::TitleState(GEX::StateStack & stack, Context context)
	: State(stack, context)
	, text_()
	, showText_(true)
	, textEffectTime_(sf::Time::Zero)
{
	backgroundSprite_.setTexture(context.textures->get(GEX::TextureID::TitleScreen));
	text_.setFillColor(sf::Color::Black);
	text_.setOutlineColor(sf::Color::Red);
	text_.setOutlineThickness(3.5f);
	text_.setStyle(sf::Text::Italic);
	text_.setFont(GEX::FontManager::getInstance().get(GEX::FontID::Main));
	text_.setCharacterSize(80);
	text_.setString("Press any key to start");

	centerOrigin(text_);
	text_.setPosition(context.window->getView().getSize() / 2.f);

}

void TitleState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.draw(backgroundSprite_);

	if (showText_) {
		window.draw(text_);
	}

}

bool TitleState::update(sf::Time dt)
{
	textEffectTime_ += dt;

	if (textEffectTime_ >= sf::seconds(0.5f)) {
		showText_ = !showText_;
		textEffectTime_ = sf::Time::Zero;
	}

	return true;
}

bool TitleState::handleEvent(const sf::Event & event)
{
	if (event.type == sf::Event::KeyPressed) {
		requestStackPop();
		requestStackPush(GEX::StateID::Menu);
	}
	return true;
}
