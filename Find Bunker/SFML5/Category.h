//
//

#pragma once

namespace Category
{
	enum Type
	{
		None			 = 0,
		Key				 = 1 << 0,	
		Character		 = 1 << 1,	
		Vehicle			 = 1 << 2,	
		Bunker			 = 1 << 3,	
		Scene			 = 1 << 4,
		Signpost	     = 1 << 5,
		Block			 = 1 << 6,
		SoundEffect		 = 1 << 7,
		People			 = 1 << 8
	};
}