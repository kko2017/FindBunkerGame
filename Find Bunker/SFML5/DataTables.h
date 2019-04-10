/**
* @file
* DataTables.h
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


#pragma once
#include "TextureManager.h"
#include "DynamicObjects.h"
#include "StaticObjects.h"

#include <map>

namespace GEX {

	struct DynamicObjectsData {
		TextureID	texture;
		sf::IntRect textureRect;

		std::map<DynamicObjects::State, Animation2> animations;
	};

	struct StaticObjectData {
		TextureID	texture;
		sf::IntRect textureRect;
	};

	struct SpawnData {
		DynamicObjects::Type type;
		sf::Time			 time;
		float				 x;
		float				 y;
		float				 speed;
	};

	struct SpawnBlockData {
		StaticObjects::Type type;
		float				x;
		float				y;
	};

	std::map<DynamicObjects::Type, DynamicObjectsData>	initializeDynamicObjectsData();
	std::map<StaticObjects::Type, StaticObjectData>		initializeStaticObjectsData();
	std::vector<SpawnData>								initializeSpawnData();
	std::vector<SpawnBlockData>							initializeSpawnBlockData();
}

