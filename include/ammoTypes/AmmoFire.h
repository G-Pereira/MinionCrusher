#pragma once
#include "../types.h"
/// Extension of the AmmoType Class. A tower with this ammotype will damage minions.
class AmmoFire : public AmmoType {
public:
	AmmoFire()
		: AmmoType(1, 10, 0, 0, 1) {

	}

};