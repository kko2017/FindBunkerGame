#pragma once

#include "SceneNode.h"
#include "SoundPlayer.h"

namespace GEX {

	//Forward Declaration
	class SoundPlayer;

	class SoundNode : public SceneNode												// inherits from SceneNode
	{
	public:
		explicit			SoundNode(SoundPlayer& player);							// explicit constructor passes the instance of SoundPlayer as parameter

		void				playSound(SoundEffectID sound, sf::Vector2f position);	// identify the sound and set up the position of it

		unsigned int		getCategory() const override;							// get category type

	private:
		SoundPlayer&		sounds_;

	};
}

