//
//

#pragma once

namespace Category
{
	enum Type
	{
		None			 = 0,
		Scene			 = 1 << 0,	// << means bit shift  --> what is bit fields?
		PlayerAircraft	 = 1 << 1,	// 000000000000
		AlliedAircraft	 = 1 << 2,	// 000000000001
		EnemyAircraft	 = 1 << 3,	// 000000000010
		EnemyProjectile  = 1 << 4,	// 000000000100
		AlliedProjectile = 1 << 5,
		AirSceneLayer	 = 1 << 6,
		Pickup			 = 1 << 7,
		ParticleSystem	 = 1 << 8,
		Zombie			 = 1 << 9,
		Hero			 = 1 << 10,

		Aircraft = PlayerAircraft | AlliedAircraft | EnemyAircraft,
		Projectile = EnemyProjectile | AlliedProjectile
	};
}