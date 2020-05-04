#include "include\Terrain.h"

void Terrain::create(const uint8_t* blocks, const uint16_t* blockMapping, 
                     const uint8_t* lvLayout, Size _lvSize) 
{
    blocksPtr = blocks;
    blockMappingPtr = blockMapping;
    lvLayoutPtr = lvLayout;
    lvSize = _lvSize;
}

uint8_t Terrain::getChunk(Vector2i pos) {
    if (pos.x  < 0 || pos.x  > lvSize.width  * 256 || 
        pos.y  < 0 || pos.y  > lvSize.height * 256)
            return 0;
    
    uint8_t chunk = lvLayoutPtr[(pos.y / 256) * lvSize.width + pos.x / 256];

    // Loop in ghz
    if (chunk == 0xB5) {
        if (layer == 0) 
            return 0x35;
        else
            return 0x36;       
    } else {
        return chunk;
    }
}

uint16_t Terrain::getBlock(Vector2i pos) {
    int chunk  = int(getChunk(pos));
    int chunkX = (pos.x / 256) * 256;
    int chunkY = (pos.y / 256) * 256;
    
    if (chunk != 0)
        return blockMappingPtr[((chunk - 1) * 16 + (pos.y - chunkY) / 16) * 16 + (pos.x - chunkX) / 16];
    else
        return 0;
    
}


Tile Terrain::getTile(Vector2i pos)
{
    uint16_t block = getBlock(pos);

    uint8_t  xFlip    = ((block & 0x800)  >> 11);
    uint8_t  yFlip    = ((block & 0x1000) >> 12);
    uint8_t  type     = block >> 13;
	uint16_t blockID  = (block & 0x7FF);

    Tile tile;

    tile.type = TileType(type);
    tile.pos  = Vector2i((pos.x / 16) * 16, (pos.y / 16) * 16);

    // Set Heights
    for (int i = 0; i < 16; i++) {
        if (xFlip == 0)
            tile.verHeight[i] = verHeights[blocksPtr[int(blockID)] * 16 + i];
        else 
            tile.verHeight[i] = verHeights[blocksPtr[int(blockID)] * 16 + (15 - i)];

        if (yFlip == 0)
            tile.horHeight[i] = horHeights[blocksPtr[int(blockID)] * 16 + i];
        else 
            tile.horHeight[i] = horHeights[blocksPtr[int(blockID)] * 16 + (15 - i)];
    }

    // Set Angle
    uint8_t hexAngle = angles[blocksPtr[int(blockID)]];

    if (hexAngle == 0xFF || hexAngle == 0 || tile.type == TileType::TILE_EMPTY) {
        tile.angle = 0.0;
    } else {
        if (xFlip == 1 && yFlip == 0)
            hexAngle = 256 - hexAngle;
        else if (xFlip == 0 && yFlip == 1)
            hexAngle = 128 - hexAngle;
        else if (xFlip == 1 && yFlip == 1)
            hexAngle = 128 + hexAngle;

        tile.angle = float(256.0 - int(hexAngle)) * 1.40625f;
    }

    return tile;
}

int Terrain::getTileVerHeight(Vector2i pos) {
    uint16_t block = getBlock(pos);

	uint16_t xFlip = ((block & 0x800) >> 11);
	uint16_t blockID = (block & 0x7FF);
 
    int xx;
    int height;
    
    if (int(xFlip) == 1)
        xx = 15 - int(pos.x - ((pos.x / 16) * 16));
    else
        xx = int(pos.x - ((pos.x / 16) * 16));

    height = int(verHeights[ blocksPtr[int(blockID)] * 16 + xx]);

    if (height <= 16)
        return height;
    else
        return 256 - height;
}

int Terrain::getTileHorHeight(Vector2i pos) {
    uint16_t block = getBlock(pos);

	uint16_t yFlip = (block << 3);
	uint16_t blockID = (block << 5);
	yFlip = yFlip >> 15;
	blockID = blockID >> 5;
 
    int yy;
    int height;
    
    if (int(yFlip) == 1)
        yy = 15 - int(pos.y - ((pos.y / 16) * 16));
    else
        yy = int(pos.y - ((pos.y / 16) * 16));

    height = int(horHeights[ blocksPtr[int(blockID)] * 16 + yy]);

    if (height <= 16)
        return height;
    else
        return 256 - height;
}

TileType Terrain::getTileType(Vector2i pos) {
    uint16_t block = getBlock(pos);
    uint8_t solidity = block >> 13;
    return (TileType)solidity;
}

float Terrain::getTileAngle(Vector2i pos) {
    uint8_t hexAngle;
    float decAngle;

    uint16_t block = getBlock(pos);
    uint16_t yFlip = (block << 3);
    uint16_t xFlip = (block << 4);
	xFlip = xFlip >> 15;
    yFlip = yFlip >> 15;

	uint16_t blockID = (block & 0x7FF);

    hexAngle = angles[blocksPtr[int(blockID)]];

    if (hexAngle == 0xFF)
        return 0;

    if (xFlip == 1 && yFlip == 0)
        hexAngle = 256 - hexAngle;
    else if (xFlip == 0 && yFlip == 1)
        hexAngle = 128 - hexAngle;
    else if (xFlip == 1 && yFlip == 1)
        hexAngle = 128 + hexAngle;

    return float(256.0 - hexAngle) * 1.40625f;
}

Size Terrain::getSize() {
    return lvSize;
}

void Terrain::setLayer(uint8_t _layer)
{
    layer = _layer;
}
