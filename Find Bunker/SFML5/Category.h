//
//

#pragma once

namespace Category
{
	enum Type
	{
		None			 = 0,
		Scene			 = 1 << 0,	// << means bit shift  --> what is bit fields?
		Character		 = 1 << 1,	// 000000000000
		Vehicle			 = 1 << 2,	// 000000000001
		Bunker			 = 1 << 3,	// 000000000010
		EnemyProjectile  = 1 << 4,	// 000000000100
		AlliedProjectile = 1 << 5,
		AirSceneLayer	 = 1 << 6,
		Signpost	     = 1 << 7,
		Block			 = 1 << 8,

		Projectile = EnemyProjectile | AlliedProjectile
	};
}