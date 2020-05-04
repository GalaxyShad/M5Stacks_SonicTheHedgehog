#pragma once

#include "Settings.h"

#include "content\collide\GHZ Blocks.h"
#include "content\collide\256_block_mappings\GHZ.h"
#include "content\levels\ghz1.h"
#include "content\levels\ghz2.h"
#include "content\levels\ghz3.h"

#include "Player.h"
#include "Camera.h"
#include "Terrain.h"

#include "entities\Spring.h"
#include "entities\Ring.h"
#include "entities\LayerSwitcher.h"
#include "entities\EnemiesGHZ.h"
#include "entities\GimmicksGHZ.h"

#define LV_WIDTH 47
#define LV_HEIGHT 4

#define PL_START_POS_X 80
#define PL_START_POS_Y 944

const int ghzPal[60] PROGMEM = { 
    0x000000, 0x202080, 0x4040a0, 0x6060c0, 0x8080e0, 0xe0e0e0, 0xa0a0a0, 0x808080, 0x404040, 0xe0a080, 0xa06040, 0xe00000, 0x800000, 0x400000, 0xe0e000,
    0x000000, 0x204020, 0x406040, 0x608060, 0x80c080, 0xe0e0e0, 0xa0a0a0, 0x808080, 0x404040, 0xa0e080, 0xa06040, 0xe0e000, 0x808000, 0x404000, 0xe00000,
    0x200000, 0xe0e0e0, 0x602000, 0x804000, 0xc06000, 0xe08000, 0xe0c000, 0x6080a0, 0x6080e0, 0x80a0e0, 0xa0c0e0, 0x004000, 0x006000, 0x40a000, 0x80e000,
    0x2000a0, 0x2040c0, 0x6080e0, 0xa0c0e0, 0xc0e0e0, 0xe0e0e0, 0xc0a0e0, 0xa080e0, 0x8060e0, 0x80e000, 0x40a000, 0x200000, 0x602000, 0xc06000, 0xe0c000,
    };

const int ghzBackColor = 0x2492db;

class Level {
    public:
        void create();
        void update();
        bool fadeIn();
        bool fadeOut();
        bool isLevelPlaying() {return !restartFlag;}
        void setLevelRestartTimer(int value) {restartTimer = value;}
        void draw();
        static int foo();
        int* rings = nullptr;
    private:
        Terrain trn;
        Camera cam;
		std::list<Entity*> entities;
		std::list<Entity*>::iterator it;
        float ringFrame = 80.0; // Using for same animation to all rings
        int time = 0;
        int restartTimer = -1;
        bool restartFlag = false;
        int waterAnim = 0;
        bool starting = true;
        int fadeInCount = 0;
        int fadeOutCount = 0;

};