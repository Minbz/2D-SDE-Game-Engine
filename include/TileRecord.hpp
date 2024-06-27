#pragma once

#include <SDL3/SDL.h>
#include <string>

/**
 * A struct that represents a TileRecord.
 * A TileRecord is a record of a tile in the game.
 * It contains the filepath of the tile and whether it is collidable.
 */
struct TileRecord
{
    std::string filepath;
    bool collidable;
};