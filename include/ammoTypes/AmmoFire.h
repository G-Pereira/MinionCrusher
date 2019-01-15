#pragma once
#include "../types.h"
/// Extension of the AmmoType Class. A tower with this ammotype will damage minions.
class AmmoFire : public Ammo {
public:
	AmmoFire()
		: Ammo(1, 10, 0, 0, 1) {

	}

};