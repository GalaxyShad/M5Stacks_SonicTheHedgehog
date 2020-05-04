#pragma once
#include "Settings.h"
#include "structs\Geometry.h"
#include "Screen.h"


class Camera {
    public:
        Camera();
        void create(Vector2f _pos, Size _levelSize);
        void update();
		void drawRect(uint8_t tex, IntRect texRect, Vector2f texPos, Vector2i offset,
			bool horFlip, bool verFlip, float angle);
		void drawChunk(uint8_t tex, const uint16_t* chunks, int chunkIndex, Vector2f chunkPos);
		Vector2f getPos();
		void setPos(Vector2f _pos);
        void setBottomBorder(int _value) {bottomBorder = _value;} 
        void setRightBorder(int _value)  {rightBorder = _value;} 

    private:
        Vector2f pos;
        Size levelSize;   
        int bottomBorder = 0;
        int rightBorder = 0;
};
