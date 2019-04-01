#include "StaticObjects.h"
#include "DataTables.h"
#include "Utility.h"

#include <random>

namespace {
	const std::map<GEX::StaticObjects::Type, GEX::StaticObjectData> TABLE = GEX::initializeStaticObjectsData();
}

GEX::StaticObjects::StaticObjects(Type type, const TextureManager & textures)
	: Entity(true)
	, type_(type)
	, sprite_(textures.get(TABLE.at(type).texture), TABLE.at(type).textureRect)
{
	centerOrigin(sprite_);

	// Initialize the signPostPosition containing the eight positions.
	signPostPosition_.emplace_back(1458, 687);
	signPostPosition_.emplace_back(280, 687);
	signPostPosition_.emplace_back(280, 327);
	signPostPosition_.emplace_back(1458, 327);
	signPostPosition_.emplace_back(1610, 327);
	signPostPosition_.emplace_back(1458, 177);
	signPostPosition_.emplace_back(848, 177);
	signPostPosition_.emplace_back(1870, 837);

	// Initialize the bunkerPosition containing the eight positions.
	bunkerPosition_.emplace_back(230, 177);
	bunkerPosition_.emplace_back(640, 177);
	bunkerPosition_.emplace_back(1870, 177);
	bunkerPosition_.emplace_back(20, 687);
	bunkerPosition_.emplace_back(2028, 687);
	bunkerPosition_.emplace_back(948, 687);
	bunkerPosition_.emplace_back(155, 1353);
	bunkerPosition_.emplace_back(1972, 1353);
}

unsigned int GEX::StaticObjects::getCategory() const
{
	return Category::SignPost;
}

sf::FloatRect GEX::StaticObjects::getBoundingBox() const
{
	return getWorldTransform().transformRect(sprite_.getGlobalBounds());
}

std::vector<std::pair<int, int>> GEX::StaticObjects::getObjectPosition()
{
	if (type_ == Type::SignPost)
	{
		return signPostPosition_;
	}
	else
	{
		return bunkerPosition_;
	}
}

void GEX::StaticObjects::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite_, states);
}


