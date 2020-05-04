#include "include\Level.h"

void Level::create() {

	#pragma region Create objects
	#pragma region Gimmicks
		// Platform
		entities.push_back(new GimGHZ_Platform(Vector2f(0x1220, 0x01E8), 1, true));
		entities.push_back(new GimGHZ_Platform(Vector2f(0x1260, 0x01A8), 0, true));
		entities.push_back(new GimGHZ_Platform(Vector2f(0x1DE8, 0x0204), 1, true));
		entities.push_back(new GimGHZ_Platform(Vector2f(0x1660, 0x01E8), 3, true));
		entities.push_back(new GimGHZ_Platform(Vector2f(0x1620, 0x0160), 2, true));
		entities.push_back(new GimGHZ_Platform(Vector2f(0x1690, 0x00E0), 3, true));
		entities.push_back(new GimGHZ_Platform(Vector2f(0x1740, 0x00A0), 0, true));
		entities.push_back(new GimGHZ_Platform(Vector2f(0x2378, 0x0408), 2, true));

		entities.push_back(new GimGHZ_Platform(Vector2f(0x1B60, 0x0088), 0, false));
		entities.push_back(new GimGHZ_Platform(Vector2f(0x1BA0, 0x00C8), 0, false));
		entities.push_back(new GimGHZ_Platform(Vector2f(0x1BE0, 0x0108), 0, false));
		entities.push_back(new GimGHZ_Platform(Vector2f(0x1C20, 0x0148), 0, false));
		entities.push_back(new GimGHZ_Platform(Vector2f(0x1C60, 0x0188), 0, false));
		entities.push_back(new GimGHZ_Platform(Vector2f(0x1CA0, 0x01C8), 0, false));
		entities.push_back(new GimGHZ_Platform(Vector2f(0x1CE0, 0x0208), 0, false));
		entities.push_back(new GimGHZ_Platform(Vector2f(0x1B70, 0x0288), 0, false));
		entities.push_back(new GimGHZ_Platform(Vector2f(0x13A0, 0x0188), 0, false));
		entities.push_back(new GimGHZ_Platform(Vector2f(0x1420, 0x01A8), 0, false));
		entities.push_back(new GimGHZ_Platform(Vector2f(0x14A0, 0x01CB), 0, false));
		entities.push_back(new GimGHZ_Platform(Vector2f(0x1D40, 0x0208), 0, false));

		// Slp Platform
		entities.push_back(new GimGHZ_SlpPlatform(Vector2f(0x0ED0, 0x0240)));
		entities.push_back(new GimGHZ_SlpPlatform(Vector2f(0x10A0, 0x02B0)));
		entities.push_back(new GimGHZ_SlpPlatform(Vector2f(0x1030, 0x02B0), true));
		// Bridges
		entities.push_back(new GimGHZ_BridgeController(Vector2f(0x04A8, 0x0388), 12, entities));
		entities.push_back(new GimGHZ_BridgeController(Vector2f(0x0AA8, 0x0318), 12, entities));
		entities.push_back(new GimGHZ_BridgeController(Vector2f(0x1FA8, 0x0318), 12, entities));
		// Stones
		entities.push_back(new GimGHZ_Stone(Vector2f(0x09CD, 0x02FD)));
		entities.push_back(new GimGHZ_Stone(Vector2f(0x0BA0, 0x02FE)));
		entities.push_back(new GimGHZ_Stone(Vector2f(0x0FA0, 0x0201)));
		entities.push_back(new GimGHZ_Stone(Vector2f(0x0FD8, 0x0272)));
		entities.push_back(new GimGHZ_Stone(Vector2f(0x1D78, 0x0476)));
		entities.push_back(new GimGHZ_Stone(Vector2f(0x1ED8, 0x02FF)));
		entities.push_back(new GimGHZ_Stone(Vector2f(0x20D0, 0x0370)));
		// Walls
		entities.push_back(new GimGHZ_Wall(Vector2f(0x0C08, 0x02F8), 0));
		entities.push_back(new GimGHZ_Wall(Vector2f(0x0D08, 0x03B0), 0));
		entities.push_back(new GimGHZ_Wall(Vector2f(0x0D08, 0x03E0), 1));
		entities.push_back(new GimGHZ_Wall(Vector2f(0x1808, 0x01C0), 1));
		entities.push_back(new GimGHZ_Wall(Vector2f(0x1808, 0x01F0), 1));
		entities.push_back(new GimGHZ_Wall(Vector2f(0x1E08, 0x0370), 0));
		entities.push_back(new GimGHZ_Wall(Vector2f(0x1E48, 0x0340), 0));
		entities.push_back(new GimGHZ_Wall(Vector2f(0x1DF8, 0x04B0), 2));
		//Stube Cntrl
		entities.push_back(new GimGHZ_STube(Vector2f(0x180D, 0x0270), 0));
		entities.push_back(new GimGHZ_STube(Vector2f(0x18F4, 0x036C), 1));
		entities.push_back(new GimGHZ_STube(Vector2f(0x1A0B, 0x036F), 0));
		entities.push_back(new GimGHZ_STube(Vector2f(0x1AF4, 0x046C), 1));
		entities.push_back(new GimGHZ_STube(Vector2f(0x1A0B, 0x016C), 0));
		entities.push_back(new GimGHZ_STube(Vector2f(0x1AF4, 0x0271), 1));
	#pragma endregion
	#pragma region Springs
		entities.push_back(new Spring(Vector2f(0x0334, 0x0328)));
		entities.push_back(new Spring(Vector2f(0x0E2C, 0x0278)));
		entities.push_back(new Spring(Vector2f(0x0DB0, 0x037B)));
		entities.push_back(new Spring(Vector2f(0x0F80, 0x03BF)));
	#pragma endregion
	#pragma region Rings
		entities.push_back(new Ring(Vector2f(0x0144, 0x0360), 3, Ring::DIR_RIGHT, entities));
		entities.push_back(new Ring(Vector2f(0x0334, 0x022C), 6, Ring::DIR_DOWN, entities));
		entities.push_back(new Ring(Vector2f(0x046C, 0x0320), 5, Ring::DIR_RIGHT, entities));
		entities.push_back(new Ring(Vector2f(0x0680, 0x0387)));
		entities.push_back(new Ring(Vector2f(0x06A0, 0x0397)));
		entities.push_back(new Ring(Vector2f(0x06C0, 0x03A5)));
		entities.push_back(new Ring(Vector2f(0x06E3, 0x03B0)));
		entities.push_back(new Ring(Vector2f(0x070B, 0x03B3)));
		entities.push_back(new Ring(Vector2f(0x0737, 0x03AF)));
		entities.push_back(new Ring(Vector2f(0x075B, 0x0392)));
		entities.push_back(new Ring(Vector2f(0x09C4, 0x02C0), 2, Ring::DIR_RIGHT, entities));
		entities.push_back(new Ring(Vector2f(0x0B94, 0x02D0), 2, Ring::DIR_RIGHT, entities));
		entities.push_back(new Ring(Vector2f(0x0D50, 0x02B6)));
		entities.push_back(new Ring(Vector2f(0x0D70, 0x02A9)));
		entities.push_back(new Ring(Vector2f(0x0D92, 0x0297)));
		entities.push_back(new Ring(Vector2f(0x0DB4, 0x0287)));
		entities.push_back(new Ring(Vector2f(0x0DDA, 0x0277)));
		entities.push_back(new Ring(Vector2f(0x0EB1, 0x0211)));
		entities.push_back(new Ring(Vector2f(0x0ED2, 0x020A)));
		entities.push_back(new Ring(Vector2f(0x0EF5, 0x0203)));
		entities.push_back(new Ring(Vector2f(0x0F1A, 0x0205)));
		entities.push_back(new Ring(Vector2f(0x0F3F, 0x0209)));
		entities.push_back(new Ring(Vector2f(0x0F66, 0x0208)));
		entities.push_back(new Ring(Vector2f(0x0F88, 0x02D8), 3, Ring::DIR_RIGHT, entities));
		entities.push_back(new Ring(Vector2f(0x1158, 0x032C), 3, Ring::DIR_RIGHT, entities));
		entities.push_back(new Ring(Vector2f(0x1220, 0x032C), 3, Ring::DIR_RIGHT, entities));
		entities.push_back(new Ring(Vector2f(0x125C, 0x023E)));
		entities.push_back(new Ring(Vector2f(0x1280, 0x0249)));
		entities.push_back(new Ring(Vector2f(0x12A2, 0x0259)));
		entities.push_back(new Ring(Vector2f(0x12C3, 0x0269)));
		entities.push_back(new Ring(Vector2f(0x12EA, 0x0271)));
		entities.push_back(new Ring(Vector2f(0x153C, 0x0260)));
		entities.push_back(new Ring(Vector2f(0x154E, 0x0230)));
		entities.push_back(new Ring(Vector2f(0x1580, 0x021D)));
		entities.push_back(new Ring(Vector2f(0x15AF, 0x0230)));
		entities.push_back(new Ring(Vector2f(0x15C3, 0x0260)));
		entities.push_back(new Ring(Vector2f(0x16E4, 0x01B5)));
		entities.push_back(new Ring(Vector2f(0x170C, 0x01B5)));
		entities.push_back(new Ring(Vector2f(0x1734, 0x01AB)));
		entities.push_back(new Ring(Vector2f(0x175B, 0x019C)));
		entities.push_back(new Ring(Vector2f(0x1784, 0x0189)));
		entities.push_back(new Ring(Vector2f(0x17A6, 0x0179)));
		entities.push_back(new Ring(Vector2f(0x17E0, 0x0174)));
		entities.push_back(new Ring(Vector2f(0x180C, 0x0174)));
		entities.push_back(new Ring(Vector2f(0x1820, 0x0074), 7, Ring::DIR_RIGHT, entities));
		entities.push_back(new Ring(Vector2f(0x183C, 0x0176)));
		entities.push_back(new Ring(Vector2f(0x186C, 0x0178)));
		entities.push_back(new Ring(Vector2f(0x189C, 0x017A)));
		entities.push_back(new Ring(Vector2f(0x18C8, 0x0074), 7, Ring::DIR_RIGHT, entities));
		entities.push_back(new Ring(Vector2f(0x18CC, 0x0174)));
		entities.push_back(new Ring(Vector2f(0x18FC, 0x0174)));
		entities.push_back(new Ring(Vector2f(0x192C, 0x0175)));
		entities.push_back(new Ring(Vector2f(0x1950, 0x0370), 5, Ring::DIR_RIGHT, entities));
		entities.push_back(new Ring(Vector2f(0x195C, 0x017A)));
		entities.push_back(new Ring(Vector2f(0x1970, 0x0074), 6, Ring::DIR_RIGHT, entities));
		entities.push_back(new Ring(Vector2f(0x198C, 0x017B)));
		entities.push_back(new Ring(Vector2f(0x19BC, 0x0176)));
		entities.push_back(new Ring(Vector2f(0x19EC, 0x0174)));
		entities.push_back(new Ring(Vector2f(0x1D58, 0x0268), 7, Ring::DIR_RIGHT, entities));
		entities.push_back(new Ring(Vector2f(0x1D64, 0x0258), 7, Ring::DIR_RIGHT, entities));
		entities.push_back(new Ring(Vector2f(0x1D70, 0x0248), 6, Ring::DIR_RIGHT, entities));
		entities.push_back(new Ring(Vector2f(0x1D7C, 0x0238), 5, Ring::DIR_RIGHT, entities));
		entities.push_back(new Ring(Vector2f(0x1D88, 0x0228), 4, Ring::DIR_RIGHT, entities));
		entities.push_back(new Ring(Vector2f(0x1E00, 0x0268)));
		entities.push_back(new Ring(Vector2f(0x1F64, 0x0480), 6, Ring::DIR_RIGHT, entities));
		entities.push_back(new Ring(Vector2f(0x1F70, 0x02B4), 5, Ring::DIR_RIGHT, entities));
		entities.push_back(new Ring(Vector2f(0x2135, 0x0374)));
		entities.push_back(new Ring(Vector2f(0x2158, 0x037D)));
		entities.push_back(new Ring(Vector2f(0x217A, 0x0388)));
		entities.push_back(new Ring(Vector2f(0x219C, 0x0397)));
		entities.push_back(new Ring(Vector2f(0x21BE, 0x03A8)));
		entities.push_back(new Ring(Vector2f(0x21E2, 0x03B1)));
		entities.push_back(new Ring(Vector2f(0x2342, 0x0475)));
		entities.push_back(new Ring(Vector2f(0x2367, 0x047E)));
		entities.push_back(new Ring(Vector2f(0x2386, 0x048D)));
		entities.push_back(new Ring(Vector2f(0x23A5, 0x049D)));
		entities.push_back(new Ring(Vector2f(0x23C6, 0x04AE)));
		entities.push_back(new Ring(Vector2f(0x23EC, 0x04B6)));
		entities.push_back(new Ring(Vector2f(0x2414, 0x04B6)));
		entities.push_back(new Ring(Vector2f(0x243A, 0x04B6)));
		entities.push_back(new Ring(Vector2f(0x2461, 0x04B6)));
		entities.push_back(new Ring(Vector2f(0x2486, 0x04B5)));
	#pragma endregion
	#pragma region Layering
		entities.push_back(new LayerSwitcher(Vector2f(0x157F, 0x0214), Vector2f(16, 64), 2));
		entities.push_back(new LayerSwitcher(Vector2f(0x1508, 0x0231), Vector2f(16, 128), 0));
		entities.push_back(new LayerSwitcher(Vector2f(0x15F4, 0x0231), Vector2f(16, 128), 1));
	#pragma endregion
	#pragma region Enemies
	entities.push_back(new EnBuzz(Vector2f(0x0420, 0x0330)));
	entities.push_back(new EnBuzz(Vector2f(0x0D40, 0x0268)));
	entities.push_back(new EnBuzz(Vector2f(0x0DD0, 0x0270)));
	entities.push_back(new EnBuzz(Vector2f(0x1100, 0x01D0)));
	entities.push_back(new EnBuzz(Vector2f(0x13A0, 0x0130)));
	entities.push_back(new EnBuzz(Vector2f(0x1510, 0x017C)));
	entities.push_back(new EnBuzz(Vector2f(0x1610, 0x0130)));
	entities.push_back(new EnBuzz(Vector2f(0x1DA0, 0x0320)));
	entities.push_back(new EnBuzz(Vector2f(0x1EA0, 0x02A0)));
	entities.push_back(new EnBuzz(Vector2f(0x23F0, 0x0380)));
	entities.push_back(new EnBuzz(Vector2f(0x1DA0, 0x0320)));

	entities.push_back(new EnMotobug(Vector2f(0x0340, 0x03AC)));
	entities.push_back(new EnMotobug(Vector2f(0x1448, 0x0304)));

	entities.push_back(new EnCrab(Vector2f(0x08B0, 0x0350), entities));
	entities.push_back(new EnCrab(Vector2f(0x0960, 0x02FA), entities));
	entities.push_back(new EnCrab(Vector2f(0x2180, 0x048C), entities));

	entities.push_back(new EnChopper(Vector2f(0x04A0, 0x0460)));
	entities.push_back(new EnChopper(Vector2f(0x0A78, 0x0400)));
	entities.push_back(new EnChopper(Vector2f(0x0AC8, 0x03C0)));
	entities.push_back(new EnChopper(Vector2f(0x1F80, 0x03C0)));
	entities.push_back(new EnChopper(Vector2f(0x1FC0, 0x03D0)));
#pragma endregion
	entities.push_back(new SignPost(Vector2f(0x2560, 0x04AA)));
#pragma endregion

	// Create player
	Player* pl = new Player(Vector2f(PL_START_POS_X, PL_START_POS_Y), trn);
	entities.push_back(pl);	
	rings = &(pl->rings);

	trn.create(ghzBlocks, ghz256BlockMap, ghz1Layout, Size(48, 5));
    cam.create(Vector2f(PL_START_POS_X - SCREEN_WIDTH / 2, PL_START_POS_Y - SCREEN_HEIGHT / 2), 
		trn.getSize());

	for (it = entities.begin(); it != entities.end(); it++)
		(*it)->create();

	// Level Variables
	ringFrame = 80.0; // Using for same animation to all rings
    time = 0;
    restartTimer = -1;
    restartFlag = false;
    waterAnim = 0;
    starting = true;
    fadeInCount = 0;
    fadeOutCount = 0;

}

void Level::update() {
	for (it = entities.begin(); it != entities.end();) {
		Entity* ent = *it;
		if (!ent->isLiving()) {
			it = entities.erase(it);
			delete ent;
		} else {
			it++;
		}
	}

	for (it = entities.begin(); it != entities.end(); it++) {
		if ((*it)->isInCamera(cam)) {
			(*it)->update();
			(*it)->reactingToOthers(entities);
			if ((*it)->getType() == TYPE_PLAYER) {
				((Player*)(*it))->terrainCollision(cam);
				((Player*)(*it))->entitiesCollision(entities, cam);
				((Player*)(*it))->moveCam(cam);	
				if (((Player*)(*it))->isEndLv() && restartTimer == -1)
					restartTimer = 160;

				if ((*it)->getPos().x < 0x16B0)
					cam.setBottomBorder(1024);
				else 
					cam.setBottomBorder(1280);
			} else if ((*it)->getType() == TYPE_ENEMY) {
				Enemy* en = (Enemy*)(*it);
				en->trnCollision(trn);
			} else if ((*it)->getType() == TYPE_RING) {
				// Ring animation
				Ring* ring = (Ring*)(*it);
				ring->animate(float(ringFrame));
			} 
			
		} else {
			(*it)->goToStartPos();
			if ((*it)->getType() == TYPE_PLATFORM)
				(*it)->create();
			if ((*it)->getType() == TYPE_RING) {
				Ring* ring = (Ring*)*it;
				if (ring->isBounce())
					ring->destroy();
			}
			if ((*it)->getType() == TYPE_BULLET) {
				(*it)->destroy();
			}
		}
	}

	// Ring animation
	ringFrame += 0.125;
	if (ringFrame >= 84)
		ringFrame = 80;

	// Time count
	time++;
	
}

void Level::draw() {
	//Change GHZ water pallete
	uint32_t pal[4] = {0x6080a0, 0x6080e0, 0x80a0e0, 0xa0c0e0}; 
	if (time % 6 == 0)
		waterAnim++;

	if (waterAnim >= 4)
		waterAnim = 0;

	if (!fadeIn() && !fadeOut()) {
		scr.setPalColor(40, pal[waterAnim % 4]);
		scr.setPalColor(39, pal[(waterAnim+1) % 4]);
		scr.setPalColor(38, pal[(waterAnim+2) % 4]);
		scr.setPalColor(37, pal[(waterAnim+3) % 4]);
	}

	

	cam.update();

	cam.drawChunk(TEX_GHZ_TILES, ghz256BlockMap, 0x3D, Vector2f(cam.getPos().x, cam.getPos().y));
	if (SCREEN_WIDTH > 256)
		cam.drawChunk(TEX_GHZ_TILES, ghz256BlockMap, 0x3E, Vector2f(cam.getPos().x + 256, cam.getPos().y));

     for(int i = 0; i < trn.getSize().height; i++) {
		 if (i * 256 + 256 < cam.getPos().y)
				continue;
			if (i * 256 > cam.getPos().y + SCREEN_HEIGHT)
				break;

        for (int j = 0; j < trn.getSize().width; j++) {

			if (j * 256 + 256 < cam.getPos().x)
				continue;
			if (j * 256 > cam.getPos().x + SCREEN_WIDTH)
				break;

			if (trn.getChunk(Vector2i(j * 256, i * 256)) != 0) {
					cam.drawChunk(TEX_GHZ_TILES, ghz256BlockMap,
						trn.getChunk(Vector2i(j * 256, i * 256)) - 1, Vector2f(j * 256, i * 256));
			}
		}
    }

	for (it = entities.begin(); it != entities.end(); it++) {
		if ((*it)->isInCamera(cam))
			(*it)->draw(cam);
	}
	
}

bool Level::fadeIn() {
	#define COL_STEP 4
	fadeInCount += COL_STEP;
	if (fadeInCount >= 260) {
		fadeInCount = 260;
		return false;
	}

	uint8_t r = (0xFF0000 & scr.backColor) >> 16;
	uint8_t g = (0x00FF00 & scr.backColor) >> 8;
	uint8_t b = (0x0000FF & scr.backColor);

	uint8_t _r = (0xFF0000 & ghzBackColor) >> 16;
	uint8_t _g = (0x00FF00 & ghzBackColor) >> 8;
	uint8_t _b = (0x0000FF & ghzBackColor);
	
	if (r < _r) r += COL_STEP; else {r = _r;};
	if (g < _g) g += COL_STEP; else {g = _g;};
	if (b < _b) b += COL_STEP; else {b = _b;};

	int col = (r << 16) | (g << 8) | b;

	scr.backColor = col;

	for (int i = 0; i < 60; i ++) {
		r = (0xFF0000 & scr.getPalColor(i)) >> 16;
		g = (0x00FF00 & scr.getPalColor(i)) >> 8;
		b = (0x0000FF & scr.getPalColor(i));

		_r = (0xFF0000 & ghzPal[i]) >> 16;
		_g = (0x00FF00 & ghzPal[i]) >> 8;
		_b = (0x0000FF & ghzPal[i]);

		if (r < _r) r += COL_STEP; else {r = _r;};
		if (g < _g) g += COL_STEP; else {g = _g;};
		if (b < _b) b += COL_STEP; else {b = _b;};

		int col = (r << 16) | (g << 8) | b;

		scr.setPalColor(i, col);
	}

	return true;

}

bool Level::fadeOut() {
	if (restartTimer == -1)
		return false;
	if (restartTimer > 0) {
		restartTimer--;
		return false;
	}
	#define COL_STEP 4
	fadeOutCount += COL_STEP;
	if (fadeOutCount >= 260) {
		fadeOutCount = 260;
		restartFlag = true;
	}

	uint8_t r = (0xFF0000 & scr.backColor) >> 16;
	uint8_t g = (0x00FF00 & scr.backColor) >> 8;
	uint8_t b = (0x0000FF & scr.backColor);
	
	if (r > 0) r -= COL_STEP; else {r = 0;};
	if (g > 0) g -= COL_STEP; else {g = 0;};
	if (b > 0) b -= COL_STEP; else {b = 0;};

	int col = (r << 16) | (g << 8) | b;

	scr.backColor = col;

	for (int i = 0; i < 60; i ++) {
		r = (0xFF0000 & scr.getPalColor(i)) >> 16;
		g = (0x00FF00 & scr.getPalColor(i)) >> 8;
		b = (0x0000FF & scr.getPalColor(i));

		if (r > 0) r -= COL_STEP; else {r = 0;};
		if (g > 0) g -= COL_STEP; else {g = 0;};
		if (b > 0) b -= COL_STEP; else {b = 0;};

		col = (r << 16) | (g << 8) | b;

		scr.setPalColor(i, col);
	}

	return true;

}
