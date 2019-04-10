/**
* @file
* StateObjects.cpp
* @author
* Kwangeun Oh
* @version 1.0
*
*
* @DESCRIPTION
* This is the Find Bunker game
*
* @section LICENSE
*
*
* Copyright 2019
* Permission to use, copy, modify, and/or distribute this software for
* any purpose with or without fee is hereby granted, provided that the
* above copyright notice and this permission notice appear in all copies.
*
* THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
* WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
* ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
* WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
* ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
* OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*
* @section Academic Integrity
* I certify that this work is solely my own and complies with
* NBCC Academic Integrity Policy (policy 1111)
*/

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

	// Initialize the keyPosition containing the eight positions.
	keyPosition_.emplace_back(1458, 687);
	keyPosition_.emplace_back(280, 687);
	keyPosition_.emplace_back(280, 327);
	keyPosition_.emplace_back(1458, 327);
	keyPosition_.emplace_back(1610, 327);
	keyPosition_.emplace_back(1458, 177);
	keyPosition_.emplace_back(848, 177);
	keyPosition_.emplace_back(1870, 837);
}

unsigned int GEX::StaticObjects::getCategory() const
{
	switch (type_)
	{
	case Type::Signpost:
		return Category::Signpost;
		break;
	case Type::Bunker:
		return Category::Bunker;
		break;
	case Type::Key:
		return Category::Key;
		break;
	case Type::Block1:
	case Type::Block2:
	case Type::Block3:
	case Type::Block4:
	case Type::Block5:
	case Type::Block6:
	case Type::Block7:
	case Type::Block8:
	case Type::Block9:
	case Type::Block10:
	case Type::Block11:
		return Category::Block;
		break;
	}
	return Category::None;
}

sf::FloatRect GEX::StaticObjects::getBoundingBox() const
{
	return getWorldTransform().transformRect(sprite_.getGlobalBounds());
}

std::vector<std::pair<float, float>> GEX::StaticObjects::getObjectPosition()
{
	if (type_ == Type::Signpost)
	{
		return signPostPosition_;
	}
	else if (type_ == Type::Bunker)
	{
		return bunkerPosition_;
	}
	else
	{
		return keyPosition_;
	}
}

void GEX::StaticObjects::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite_, states);
}


