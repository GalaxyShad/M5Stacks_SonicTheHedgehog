#pragma once

#include "Settings.h"
 
#include "content\collide\Angle Map.h"
#include "content\collide\Collision Array (Normal).h"
#include "content\collide\Collision Array (Rotated).h"

#include "structs\Geometry.h"

enum TileType { TILE_EMPTY, TILE_TOP, TILE_LBR, TILE_FULL };

struct Tile {
    uint8_t verHeight[16], horHeight[16];
    Vector2i pos;
    TileType type;
    float angle = 0;
    uint8_t height = 0;

    uint8_t getHeight(Vector2i _pos, float ang) {
        if (round(ang / 90) == 0 || round(ang / 90) == 2) {
            if ((type == TileType::TILE_FULL) || 
                (type == TileType::TILE_TOP && round(ang / 90) == 0) ||
                (type == TileType::TILE_LBR && round(ang / 90) == 2))
                    height = verHeight[int(_pos.x - ((_pos.x / 16) * 16))];
        } else {
            if (type == TileType::TILE_FULL || type == TileType::TILE_LBR)
                height = horHeight[int(_pos.y - ((_pos.y / 16) * 16))];
        }
        
        if (height <= 16)
            return height;
        else
            return 256 - height;

        return 0;
    };

};

class Terrain {
    public:
        void create(const uint8_t* blocks, const uint16_t* blockMapping, const uint8_t* lvLayout, Size _lvSize);
        uint8_t getChunk(Vector2i pos);
        uint16_t getBlock(Vector2i pos);
        int getTileVerHeight(Vector2i pos);
        int getTileHorHeight(Vector2i pos);
        float getTileAngle(Vector2i pos);
        TileType getTileType(Vector2i pos);  
        Size getSize();
        Tile getTile(Vector2i pos);
        void setLayer(uint8_t _layer);
    private:
        const uint8_t* blocksPtr;
        const uint8_t* lvLayoutPtr;
        const uint16_t* blockMappingPtr;
        uint8_t layer = 0;
        Size lvSize;
};
