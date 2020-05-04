#pragma once
#include "Settings.h"
#include "content\textures\texObjects.h"
#include "content\textures\texGhzBlocks.h"
#include "content\textures\texGhzGim.h"
#include "structs\Geometry.h"

#define PART_BUFF_SIZE 20

struct Texture {
    Texture() {}
    Texture(const uint8_t* _indexes, Size _texSize) {
        indexes = _indexes;
        texSize = _texSize;
    }
    const uint8_t* indexes;
    Size texSize;
};

class Screen {
    public:
        Screen();
        void create(Size _size);
        void beginDraw();
        void endDraw();
        void drawRect(uint8_t tex, IntRect texRect, Vector2i pos, Vector2i offset, bool horFlip, bool verFlip, float angle);
        void setPalColor(int index, int col) {pal[index] = col;}
        int getPalColor(int index) {return pal[index]; }
        Size getSize();
        int backColor = 0;
    private:
        Size size;
        Texture texList[TEXTURES_COUNT];
        int pal[60];
        uint8_t scrBuff[SCREEN_HEIGHT][SCREEN_WIDTH];
        uint16_t drawBuff[SCREEN_WIDTH * PART_BUFF_SIZE];
        uint16_t getM5Color(int col);
};

extern Screen scr;