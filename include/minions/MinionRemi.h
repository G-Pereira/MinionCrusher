#pragma once

/// Stronger, very evil, minion. Extends the Minion class
class MinionRemi : public Minion {
public:
    MinionRemi(float x, float y)
            : Minion(x, y, 1, 1, 250, 20, 0.01F, 30, ObjectType::MINIONREMI) {

    }

    const ObjectType objectType = (ObjectType) 10;
};