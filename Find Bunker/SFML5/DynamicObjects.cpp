#include "DynamicObjects.h"



namespace GEX {



	DynamicObjects::DynamicObjects(Type type, const TextureManager& textures)
		: Entity(100)
		, type_(type)
		, state_(State::Right)
		, sprite_()
		, travelDistance_(0.f)
		, directionIndex_(0)
		, attack_(false)
	{
	}

}

