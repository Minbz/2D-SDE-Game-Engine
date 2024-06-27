#include "TileMap.hpp"
#include "GameEntity.hpp"
#include <iostream>

TileMap::TileMap(int mapWidth, int mapHeight, int numOfTileRow, int numOfTileColumn)
{
    mMapWidth = mapWidth;
    mMapHeight = mapHeight;
    maxRow = numOfTileRow;
    maxColumn = numOfTileColumn;

    mTileWidth = mapWidth / numOfTileColumn;
    mTileHeight = mapHeight / numOfTileRow;

    // Initialize the map layout
    mMapLayout.resize(maxRow);
    for (auto &row : mMapLayout)
    {
        row.resize(maxColumn);
    }
}

TileMap::~TileMap()
{
}

void TileMap::AddTileType(std::string tileName, std::string filepath, bool collidable)
{
    TileRecord tr;
    tr.filepath = filepath;
    tr.collidable = collidable;
    mTiles.insert({tileName, tr});
}

void TileMap::PlaceTileAt(std::string tileName, int rowNum, int columnNum)
{
    // 0-based index
    if (columnNum < 0 || columnNum >= maxColumn || rowNum < 0 || rowNum >= maxRow)
    {
        std::cout << "Invalid tile position" << std::endl;
        return;
    }

    if (mTiles.find(tileName) == mTiles.end())
    {
        std::cout << "Tile type not found" << std::endl;
        return;
    }

    TileRecord tr = mTiles[tileName];
    std::shared_ptr<GameEntity> tile = std::make_shared<GameEntity>();

    tile->AddTransform(columnNum * mTileWidth, rowNum * mTileHeight, mTileWidth, mTileHeight);
    tile->SetName(tr.filepath);
    if (tr.collidable)
    {
        tile->AddCollision2D(columnNum * mTileWidth, rowNum * mTileHeight, mTileWidth, mTileHeight);
    }
    mMapLayout[rowNum][columnNum] = tile;
}

void TileMap::EraseTileAt(int rowNum, int columnNum)
{
    if (columnNum < 0 || columnNum >= maxColumn || rowNum < 0 || rowNum >= maxRow)
    {
        std::cout << "Invalid tile position" << std::endl;
        return;
    }

    mMapLayout[rowNum][columnNum] = nullptr;
}

void TileMap::LoadToGame(std::shared_ptr<SDLGraphicsProgram> game)
{
    for (auto &row : mMapLayout)
    {
        for (auto &tile : row)
        {
            if (tile != nullptr && tile->GetTexture() == nullptr)
            {
                tile->AddTexture(game, tile->GetName());
            }
        }
    }
}

bool TileMap::HasCollisionWith(std::shared_ptr<GameEntity> target)
{
    for (auto &row : mMapLayout)
    {
        for (auto &tile : row)
        {
            if (tile != nullptr)
            {
                if (tile != nullptr && tile->isCollidable() && target->isCollidingWith(tile))
                {
                    return true;
                }
            }
        }
    }
    return false;
}

int TileMap::GetMapWidth() const
{
    return mMapWidth;
}

int TileMap::GetMapHeight() const
{
    return mMapHeight;
}

float TileMap::GetTileWidth() const
{
    return mTileWidth;
}

float TileMap::GetTileHeight() const
{
    return mTileHeight;
}

void TileMap::Render(std::shared_ptr<SDLGraphicsProgram> game)
{
    for (auto &row : mMapLayout)
    {
        for (auto &tile : row)
        {
            if (tile != nullptr)
            {
                tile->Render(game);
            }
        }
    }
}