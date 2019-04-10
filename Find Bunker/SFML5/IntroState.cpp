#include "IntroState.h"
#include "TextureManager.h"
#include "Utility.h"
#include "FontManager.h"

IntroState::IntroState(GEX::StateStack & stack, Context context)
	: State(stack, context)
	, pressKeyText_()
	, scoreText_()
	, showText_(true)
	, textEffectTime_(sf::Time::Zero)
{
	backgroundSprite_.setTexture(context.textures->get(GEX::TextureID::IntroScreen));

	pressKeyText_.setFillColor(sf::Color::White);
	pressKeyText_.setOutlineColor(sf::Color::Red);
	pressKeyText_.setOutlineThickness(3.5f);
	pressKeyText_.setStyle(sf::Text::Italic);
	pressKeyText_.setFont(GEX::FontManager::getInstance().get(GEX::FontID::Main));
	pressKeyText_.setCharacterSize(80);
	pressKeyText_.setString("Press any key to start");
	centerOrigin(pressKeyText_);
	pressKeyText_.setPosition(1600.f, 1200.f);

	setIntroText(context);
}

void IntroState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.draw(backgroundSprite_);

	if (showText_) {
		window.draw(pressKeyText_);
	}

	window.draw(scoreText_);
}

bool IntroState::update(sf::Time dt)
{
	textEffectTime_ += dt;

	if (textEffectTime_ >= sf::seconds(0.5f)) {
		showText_ = !showText_;
		textEffectTime_ = sf::Time::Zero;
	}

	return true;
}

bool IntroState::handleEvent(const sf::Event & event)
{
	if (event.type == sf::Event::KeyPressed) {
		requestStackPop();
		requestStackPush(GEX::StateID::Game);
	}
	return true;
}

void IntroState::setIntroText(Context context)
{
	scoreText_.setFillColor(sf::Color::White);
	scoreText_.setOutlineThickness(1.5f);
	scoreText_.setFont(GEX::FontManager::getInstance().get(GEX::FontID::Main));
	scoreText_.setCharacterSize(40);
	scoreText_.setString("All of sudden, a siren is loudly sounded\n\naround the city. Player working in\n\nthe office as usual does not understand\n\nwhat happens. Player finally realizes that\n\na dirty bomb is coming now\n\nand going to strike the city in any minute.\n\nOnly way to survive is that player finds\n\nand enters one of bunkers.");

	centerOrigin(scoreText_);
	scoreText_.setPosition(1600.f, 700.f);
}
