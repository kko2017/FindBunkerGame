#include "PauseState.h"
#include "Utility.h"
#include "FontManager.h"


PauseState::PauseState(GEX::StateStack & stack, Context context)
	: State(stack, context)
	, pausedText_()
	, instructionText_()
{

	pausedText_.setFont(GEX::FontManager::getInstance().get(GEX::FontID::Main));
	pausedText_.setString("Game Paused");
	pausedText_.setFillColor(sf::Color::Black);
	pausedText_.setOutlineColor(sf::Color::Cyan);
	pausedText_.setOutlineThickness(3.5f);
	pausedText_.setStyle(sf::Text::Italic);
	pausedText_.setCharacterSize(80);
	centerOrigin(pausedText_);

	instructionText_.setFont(GEX::FontManager::getInstance().get(GEX::FontID::Main));
	instructionText_.setString("(Press Backspace to return to the main menu");
	instructionText_.setFillColor(sf::Color::Black);
	instructionText_.setOutlineColor(sf::Color::Cyan);
	instructionText_.setOutlineThickness(3.5f);
	instructionText_.setStyle(sf::Text::Italic);
	instructionText_.setCharacterSize(50);
	centerOrigin(instructionText_);

	sf::Vector2f viewSize = context.window->getView().getSize();
	pausedText_.setPosition(0.5f * viewSize.x, 0.4f * viewSize.y);
	instructionText_.setPosition(0.5f * viewSize.x, 0.5f * viewSize.y);

	context.music->setPaused(true);
}

// Destructor sets the false of paused method for music
PauseState::~PauseState()
{
	getContext().music->setPaused(false);
}

void PauseState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());
	
	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(100, 0, 0, 150));
	backgroundShape.setSize(window.getView().getSize());

	window.draw(backgroundShape);
	window.draw(pausedText_);
	window.draw(instructionText_);

}

bool PauseState::update(sf::Time dt)
{
	return false;
}

bool PauseState::handleEvent(const sf::Event & event)
{
	if (event.type != sf::Event::KeyPressed)
		return false;

	if (event.key.code == sf::Keyboard::Escape)
		requestStackPop();

	if (event.key.code == sf::Keyboard::BackSpace) 
	{
		requestStackClear();
		requestStackPush(GEX::StateID::Menu);
	}
	return false;
}
