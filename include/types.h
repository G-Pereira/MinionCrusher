/*
 * Author: Remi Jonkman
 * Created on: 28-11-18
 * Last Modified: 28-11-18
 * Description: This file holds all type definitions and type declarations that are used throughout MinionCrusher
 * in various classes. Classes all have their own file.
 */

#ifndef MINIONCRUSHER_TYPES_H
#define MINIONCRUSHER_TYPES_H

#include <cmath>
#include <string>
#include <iostream>

/**
 * Structure holding the X, Y coordinates in a cartesian frame.
 */
struct CartesianCoordinates {
    float x;
    float y;

    /** Allows subtracting two CartesianCoordinates */
    CartesianCoordinates operator-(const CartesianCoordinates &lhs) {
        return CartesianCoordinates{x - lhs.x, y - lhs.y};
    }

    /** Allows summing two CartesianCoordinates */
    CartesianCoordinates operator+(const CartesianCoordinates &lhs) {
        return CartesianCoordinates{x + lhs.x, y + lhs.y};
    }

    /** Checks whether the the distance between the operator and the target is within the defined range */
    float abs() const {
        return sqrt(pow(x, 2) + pow(y, 2));
    }
	bool operator==(const CartesianCoordinates &rhs) {
		if (rhs.x == x && rhs.y == y)
			return true;
		return false;
	}
	bool operator<(const CartesianCoordinates &rhs) {
		if (x + y < rhs.x + rhs.y)
			return true;
		return false;
	}
	bool operator>(const CartesianCoordinates &rhs) {
		if (x + y > rhs.x + rhs.y)
			return true;
		return false;
	}
};

/**
 * Structure holding the width and height of an object.
 */
struct ObjectSize {
    float width;
    float height;
};

/**
 * Structure holding all configuration parameters that influence the behavior of an ammo related type.
 */
class AmmoType {
public:
	AmmoType(float speed, float damage, float blastRadius, float pierce, float slow) 
		: speed(speed), damage(damage), blastRadius(blastRadius), pierce(pierce), slow(slow) {

	}
    float speed = 1;
    float damage = 1;
    float blastRadius = 0;
    float pierce = 0;
    float slow = 0;
};

/**
 * Enumeration defining diffent types of tiles. This determines in which direction a minion should move.
 */
enum class ObjectType : int {
    EMPTY = 0,
    RIGHT = 1,
    UP = 2,
    DOWN = 3,
    LEFT = 4,
	BASE = 5,
	TOWER1 = 6,
	TOWER2 = 7,
	TOWER3 = 8,
	MINIONMEDIUM = 9,
	MINIONREMI = 10
};

enum class ButtonTypes {
	idle,
	fireTower,
	freezeTower,
	startmap1,
	startmap2,
	pause,
};

#endif //MINIONCRUSHER_TYPES_H
