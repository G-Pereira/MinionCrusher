#pragma once
class MinionRemi : public Minion {
public:
	MinionRemi(float x, float y)
		: Minion(x, y, 1, 1, 200, 20, 0.01F, 30) {

	}

	const ObjectType objectType = (ObjectType) 10;
};