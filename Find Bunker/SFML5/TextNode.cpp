#include "TextNode.h"
#include "Utility.h"
#include "FontManager.h"
#include <SFML/Graphics/RenderTarget.hpp>

GEX::TextNode::TextNode(const std::string & text)
{
	text_.setFont(GEX::FontManager::getInstance().get(GEX::FontID::Main));
	text_.setCharacterSize(20);
	setText(text);
}

void GEX::TextNode::setText(const std::string & text)
{
	text_.setString(text);
	centerOrigin(text_);
}

void GEX::TextNode::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(text_, states);
}
