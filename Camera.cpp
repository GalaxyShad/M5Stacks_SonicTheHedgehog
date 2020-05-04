#include "include\Camera.h"

Camera::Camera() {
    
}

void Camera::create(Vector2f _pos, Size _levelSize) {
    levelSize = _levelSize;
	bottomBorder = levelSize.height * 256;
	rightBorder = levelSize.width * 256;
	pos = _pos;
}

void Camera::update() {
    if (pos.x < 0.0) 
        pos.x = 0.0;
    if (pos.y < 0.0) 
        pos.y = 0.0;
    if (pos.x + SCREEN_WIDTH > levelSize.width  * 256)
        pos.x = levelSize.width * 256 - SCREEN_WIDTH;
    if (pos.y + SCREEN_HEIGHT > levelSize.height * 256)
        pos.y = levelSize.height * 256 - SCREEN_HEIGHT;

	if (pos.x + SCREEN_WIDTH > rightBorder)
        pos.x = rightBorder - SCREEN_WIDTH;
	if (pos.y + SCREEN_HEIGHT > bottomBorder)
        pos.y = bottomBorder - SCREEN_HEIGHT;
}


void Camera::drawRect(uint8_t tex, IntRect texRect, Vector2f texPos, Vector2i offset,
	bool horFlip, bool verFlip, float angle)
{
	scr.drawRect(tex, texRect, Vector2i(texPos.x - pos.x, texPos.y - pos.y), offset, horFlip, verFlip, angle);
}

void Camera::drawChunk(uint8_t tex, const uint16_t* chunks, int chunkIndex, Vector2f chunkPos)
{
	for (int i = 0; i < 16; i++) {
		if (chunkPos.y + i * 16.0 - pos.y > SCREEN_HEIGHT) break;
		if (chunkPos.y + i * 16.0 - pos.y + 16 < 0) continue;
		for (int j = 0; j < 16; j++) {
			if (chunkPos.x + j * 16.0 - pos.x > SCREEN_WIDTH) break;
			if (chunkPos.x + j * 16.0 - pos.x + 16 < 0) continue;

			uint16_t block = chunks[(chunkIndex * 16 + i) * 16 + j];

			uint16_t yFlip = (block << 3);
			uint16_t xFlip = (block << 4);
			uint16_t blockID = (block << 5);

			yFlip = yFlip >> 15;
			xFlip = xFlip >> 15;
			blockID = blockID >> 5;

			bool b_xFlip = false;
			bool b_yFlip = false;

			if (xFlip == 1)
				b_xFlip = true;
			if (yFlip == 1)
				b_yFlip = true;


			scr.drawRect(tex, IntRect(0, blockID * 16, 16, 16), 
				Vector2i(chunkPos.x + j * 16.0 - pos.x, chunkPos.y + i * 16.0 - pos.y), 
				Vector2i(0, 0), b_xFlip, b_yFlip, 0);
		}
	}
}

Vector2f Camera::getPos() {
    return pos;
}

void Camera::setPos(Vector2f _pos) {
	pos = _pos;
}
