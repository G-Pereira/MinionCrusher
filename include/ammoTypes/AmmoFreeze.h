#pragma once
#include "../types.h"
/// Extension of AmmoType. A tower with this ammotype will slow enemies instead of damaging them.
class AmmoFreeze : public Ammo {
public:
	AmmoFreeze()
		: Ammo(1., 0., 0., 0., 0.8F) {

	}

};
