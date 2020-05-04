#include "include\Screen.h"
// === ESP Drawing === //

Screen::Screen() {
    
}

void Screen::create(Size _size) {
    size = _size;
    texList[TEX_OBJECTS]   = Texture(sprObjects, Size(1447, 100));
    texList[TEX_GHZ_TILES] = Texture(sprGhzBlocks, Size(16, 7024));
    texList[TEX_GHZ_GIMM]  = Texture(texGhzGim, Size(176, 128));

    for (int i = 0; i < 60; i++)
        pal[i] = 0;

    for (int i = 0; i < SCREEN_HEIGHT; i++) 
        for (int j = 0; j < SCREEN_WIDTH; j++) 
            scrBuff[i][j] = 0;  
}

void Screen::beginDraw() {
    for (int i = 0; i < SCREEN_HEIGHT; i++) 
        for (int j = 0; j < SCREEN_WIDTH; j++) 
            scrBuff[i][j] = 0;  
}

void Screen::endDraw() {
        M5.Lcd.startWrite();
        int _scrX = 160 - SCREEN_WIDTH / 2;
        int _scrY = 120 - SCREEN_HEIGHT / 2;
        M5.Lcd.setWindow(_scrX, _scrY, _scrX + SCREEN_WIDTH -1 , _scrY + SCREEN_HEIGHT - 1);
        for (int t = 0; t < SCREEN_HEIGHT / PART_BUFF_SIZE; t++) {
            for (int i = 0; i < PART_BUFF_SIZE; i++) {
                for (int j = 0; j < SCREEN_WIDTH; j++) {           
                    uint8_t px = scrBuff[t*PART_BUFF_SIZE + i][j];
                    if (px != 0) 
                        drawBuff[(i * SCREEN_WIDTH) + j] = getM5Color(pal[px - 1]);
                    else 
                        drawBuff[(i * SCREEN_WIDTH) + j] = getM5Color(backColor);
                }
            }
            M5.Lcd.pushColors(drawBuff, SCREEN_WIDTH * PART_BUFF_SIZE);
        }
        M5.Lcd.endWrite();
}

uint16_t Screen::getM5Color(int col) {
    uint8_t r = (0xFF0000 & col) >> 16;
    uint8_t g = (0x00FF00 & col) >> 8;
    uint8_t b = (0x0000FF & col);
    return M5.Lcd.color565(r, g, b); 
}

void Screen::drawRect(uint8_t tex, IntRect texRect, Vector2i pos, Vector2i offset, 
                        bool horFlip = false, bool verFlip = false, float angle = 0.0)
{
    if (pos.x + texRect.width - offset.x < 0 || pos.x - (texRect.width - offset.x) > size.width || 
        pos.y + texRect.height - offset.y < 0 || pos.y - (texRect.height - offset.y) > size.height)
        return;

    int pxPos;
    int drawX, drawY;
    int px, py;
    float cosA = cos(radians(angle));
    float sinA = sin(radians(angle)); 

    for (int i = texRect.top; i < texRect.top + texRect.height; i++) {
        for (int j = texRect.left; j < texRect.left + texRect.width; j++) {

            pxPos = texList[tex].indexes[(i * texList[tex].texSize.width) + j];
            
            if (pxPos != 0) {
                if (!horFlip) drawX = j - texRect.left - offset.x;
                else          drawX = texRect.left + texRect.width - j - 1 - offset.x;

                if (!verFlip) drawY = i - texRect.top - offset.y;
                else          drawY = texRect.top + texRect.height - i - 1 - offset.y;

                px = pos.x + int(drawX * float(cosA) - drawY * float(sinA));
                py = pos.y + int(drawX * float(sinA) + drawY * float(cosA));


                if (px >= 0 && py >= 0 && px < size.width && py < size.height) {
                    scrBuff[py][px] = pxPos;
                }
            }  
        }


    }          
}


Size Screen::getSize() {
    return size;
}
