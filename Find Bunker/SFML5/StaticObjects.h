/**
* @file
* StaticObjects.h
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
#include "Entity.h"
#include "TextureManager.h"

#include <vector>

namespace GEX {

	class StaticObjects : public Entity
	{
	public:
		enum class Type {						// Scoped enumeration class is for specific identifier in the type of the objects
			Signpost,
			Bunker,
			Key,
			Block1,
			Block2,
			Block3,
			Block4,
			Block5,
			Block6,
			Block7,
			Block8,
			Block9,
			Block10,
			Block11,
		};

	public:
												StaticObjects(Type type, const TextureManager& textures);	// constuctor that passes the type and the textures
												~StaticObjects() = default;									// default destructor
		
		unsigned int							getCategory() const override;								// get category type by the state type
		sf::FloatRect							getBoundingBox() const override;							// get the bounding box of the objects

		std::vector<std::pair<float, float>>	getObjectPosition();										// getter for the position of the static object


	private:
		void									drawCurrent(sf::RenderTarget& target,						// draw the current object
																sf::RenderStates states) const override;

	private:
		Type									type_;
		sf::Sprite								sprite_;

		std::vector<std::pair<float, float>>	signPostPosition_;
		std::vector<std::pair<float, float>>	bunkerPosition_;
		std::vector<std::pair<float, float>>	keyPosition_;
	};

}

