/**
 * Author: Remi Jonkman
 * Created on: 28-11-18
 * Last Modified: 28-11-18
 * Description: This file holds all type definitions and type declarations that are used throughout MinionCrusher
 * in various classes. Classes all have their own file.
 */

#ifndef MINIONCRUSHER_TYPES_H
#define MINIONCRUSHER_TYPES_H

/**
 * Structure holding the X, Y coordinates in a cartesian frame.
 */
struct CartesianCoordinates {
    float x;
    float y;
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
struct AmmoType {
    float speed;
    float damage;
    float blastRadius;
    float pierce;
    float slow;
};

/**
 * Enumeration defining diffent types of tiles
 */
enum class MapSlots : int {
    EMPTY = 0,
    RIGHT = 1,
    UP = 2,
    DOWN = 3,
    LEFT = 4
};

#endif //MINIONCRUSHER_TYPES_H
