#pragma once
class MinionMedium : public Minion {
public:
	MinionMedium(float x, float y)
		: Minion(x, y, 1, 1, 100, 5, 0.01F, 10, ObjectType::MINIONMEDIUM) {

	}

	const ObjectType objectType = (ObjectType) 9;
};