#include "GameOverState.h"
#include "FontManager.h"
#include "Utility.h"
#include "PlayerControl.h"

GameOverState::GameOverState(GEX::StateStack & stack, Context context)
	: State(stack, context)
	, gameOverText_()
	, text_()
	, elapsedTime_(sf::Time::Zero)
{
	sf::Font& font = GEX::FontManager::getInstance().get(GEX::FontID::Main);
	sf::Vector2f windowSize(context.window->getSize());
	gameOverText_.setFont(font);

	if (context.player->getMissionStatus() == GEX::MissionStatus::MissionFailure) {
		
		gameOverText_.setString("Mission Failure");
	}
	else {

		gameOverText_.setString("Mission Success");
	}

	gameOverText_.setCharacterSize(150);
	centerOrigin(gameOverText_);
	gameOverText_.setPosition(0.5f * windowSize.x, 0.45f * windowSize.y);

	text_.setFont(font);
	text_.setCharacterSize(50);
	text_.setString("Press any key to score board");
	centerOrigin(text_);
	text_.setPosition(1000.f, 1000.f);

}

void GameOverState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(80, 80, 80, 35));
	backgroundShape.setSize(window.getView().getSize());

	window.draw(backgroundShape);
	window.draw(gameOverText_);
	window.draw(text_);
}

bool GameOverState::update(sf::Time dt)
{
	elapsedTime_ += dt;
	if (elapsedTime_ > sf::seconds(1.f)) {
		requestStackClear();
		requestStackPush(GEX::StateID::Score);
	}

	return false;
}

bool GameOverState::handleEvent(const sf::Event & event)
{
	return false;
}
