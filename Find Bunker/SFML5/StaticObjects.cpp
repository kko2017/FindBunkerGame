#include "StaticObjects.h"
#include "DataTables.h"
#include "Utility.h"

namespace {
	const std::map<GEX::StaticObjects::Type, GEX::StaticObjectData> TABLE = GEX::initializeStaticObjectsData();
}

GEX::StaticObjects::StaticObjects(Type type, const TextureManager & textures)
	: Entity(true)
	, type_(type)
	, sprite_(textures.get(TABLE.at(type).texture), TABLE.at(type).textureRect)
{
	centerOrigin(sprite_);
}

unsigned int GEX::StaticObjects::getCategory() const
{
	return Category::SignPost;
}

sf::FloatRect GEX::StaticObjects::getBoundingBox() const
{
	return getWorldTransform().transformRect(sprite_.getGlobalBounds());
}

void GEX::StaticObjects::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite_, states);
}


