#include "ScoreState.h"
#include "TextureManager.h"
#include "Utility.h"
#include "FontManager.h"

#include <fstream>

ScoreState::ScoreState(GEX::StateStack & stack, Context context)
	: State(stack, context)
	, pressKeyText_()
	, scoreText_()
	, showText_(true)
	, textEffectTime_(sf::Time::Zero)
{
	backgroundSprite_.setTexture(context.textures->get(GEX::TextureID::ScoreScreen));

	pressKeyText_.setFillColor(sf::Color::White);
	pressKeyText_.setOutlineColor(sf::Color::Red);
	pressKeyText_.setOutlineThickness(3.5f);
	pressKeyText_.setStyle(sf::Text::Italic);
	pressKeyText_.setFont(GEX::FontManager::getInstance().get(GEX::FontID::Main));
	pressKeyText_.setCharacterSize(50);
	pressKeyText_.setString("Press any key to menu");
	centerOrigin(pressKeyText_);
	pressKeyText_.setPosition(1700.f, 1400.f);

	setScoreText(context);
}

void ScoreState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.draw(backgroundSprite_);

	if (showText_) {
		window.draw(pressKeyText_);
	}

	window.draw(scoreText_);
}

bool ScoreState::update(sf::Time dt)
{
	textEffectTime_ += dt;

	if (textEffectTime_ >= sf::seconds(0.5f)) {
		showText_ = !showText_;
		textEffectTime_ = sf::Time::Zero;
	}

	return true;
}

bool ScoreState::handleEvent(const sf::Event & event)
{
	if (event.type == sf::Event::KeyPressed) {
		requestStackPop();
		requestStackPush(GEX::StateID::Menu);
	}
	return true;
}

void ScoreState::setScoreText(Context context)
{
	setScore();

	scoreText_.setFillColor(sf::Color::White);
	scoreText_.setOutlineThickness(1.5f);
	scoreText_.setFont(GEX::FontManager::getInstance().get(GEX::FontID::Main));
	scoreText_.setCharacterSize(50);
	scoreText_.setString("Time          Date\n\n" + score_);

	centerOrigin(scoreText_);
	scoreText_.setPosition(1700.f, 700.f);
}

void ScoreState::setScore()
{
	std::ifstream is;
	std::string record = "";
	std::string fileName = "Record/highRecord.txt";
	is.open(fileName);

	int i = 0;
	while (i < 10)
	{
		i++;
		std::getline(is, record);
		score_ += " " + record + "\n\n";
	}

	is.close();
}

