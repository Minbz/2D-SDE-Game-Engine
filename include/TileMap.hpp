#pragma once

#include <SDL3/SDL.h>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

#include "GameEntity.hpp"
#include "TileRecord.hpp"

/**
 * A struct that represents a TileMap.
 * A TileMap is a map of tiles that can be placed in the game.
 */
struct TileMap
{
    /**
     * Constructor for TileMap.
     * @param mapWidth The width of the map.
     * @param mapHeight The height of the map.
     * @param numOfTileRow The number of rows of tiles.
     * @param numOfTileColumn The number of columns of tiles.
     */
    TileMap(int mapWidth, int mapHeight, int numOfTileRow, int numOfTileColumn);

    /**
     * Destructor for TileMap.
     */
    ~TileMap();

    /**
     * Add a tile type to the map to be used to fill the map.
     * @param tileName The name of the tile.
     * @param filepath The path to the file to load.
     * @param collidable Whether the tile is collidable.
     */
    void AddTileType(std::string tileName, std::string filepath, bool collidable);

    /**
     * Place a tile that's previously added at a specific position in the map.
     * A tile of class GameEntity is created and placed in the map.
     * @param tileName The name of the tile to place.
     * @param rowNum The row number to place the tile.
     * @param columnNum The column number to place the tile.
     * @see GameEntity
     */
    void PlaceTileAt(std::string tileName, int rowNum, int columnNum);

    /**
     * Erase a tile at a specific position in the map.
     * @param rowNum The row number to erase the tile.
     * @param columnNum The column number to erase the tile.
     */
    void EraseTileAt(int rowNum, int columnNum);

    /**
     * Create texture components for all tiles in the map onto the game.
     * This function is separated from PlaceTileAt to speed up the loading process.
     * @param game The game to load to as an SDLGraphicsProgram.
     * @see SDLGraphicsProgram
     */
    void LoadToGame(std::shared_ptr<SDLGraphicsProgram> game);

    /**
     * Check if a specific tile is colliding with a target entity.
     * @param target The target entity to check collision with.
     * @return Whether the tile is colliding with the target entity.
     */
    bool HasCollisionWith(std::shared_ptr<GameEntity> target);

    /**
     * Get the width of the map.
     * @return The width of the map.
     */
    int GetMapWidth() const;

    /**
     * Get the height of the map.
     * @return The height of the map.
     */
    int GetMapHeight() const;

    /**
     * Get the width of a tile.
     * @return The width of a tile.
     */
    float GetTileWidth() const;

    /**
     * Get the height of a tile.
     * @return The height of a tile.
     */
    float GetTileHeight() const;

    /**
     * Render the map (each tile it contains) to the screen.
     * @param game The game to render to as an SDLGraphicsProgram.
     * @see SDLGraphicsProgram
     */
    void Render(std::shared_ptr<SDLGraphicsProgram> game);

private:
    /**
     * The width of the map.
     */
    int mMapWidth{0};
    /**
     * The height of the map.
     */
    int mMapHeight{0};
    /**
     * The maximum row number of the map.
     */
    int maxRow{0};
    /**
     * The maximum column number of the map.
     */
    int maxColumn{0};
    /**
     * The width of a tile.
     */
    float mTileWidth{0};
    /**
     * The height of a tile.
     */
    float mTileHeight{0};
    /**
     * A map of tile names to TileRecords.
     * Key: tile name
     * Value: TileRecord which contains the texture filepath and collidable information of the tile.
     * @see TileRecord
     */
    std::unordered_map<std::string, TileRecord> mTiles;
    /**
     * A 2D vector of shared pointers to GameEntities.
     * Represents the layout of the map.
     * @see GameEntity
     */
    std::vector<std::vector<std::shared_ptr<GameEntity>>> mMapLayout;
};