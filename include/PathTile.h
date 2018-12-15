/**
 * Author: Remi Jonkman
 * Created on: 28-11-18
 * Last Modified: 28-11-18
 */
#ifndef MINIONCRUSHER_PATHTILE_H
#define MINIONCRUSHER_PATHTILE_H

#include "MapObject.h"

class PathTile : public MapObject {
public:
    PathTile(float x, float y, float width, float height, const MapSlots type);

    PathTile(CartesianCoordinates coordinates, ObjectSize dimensions, const MapSlots type);

    const MapSlots &getType() const;	/// Get the direction of the tile

	void Render(SDL_Renderer * renderer) override;

private:
    const MapSlots type;				/// Holds the direction of the tile
};


#endif //MINIONCRUSHER_PATHTILE_H
