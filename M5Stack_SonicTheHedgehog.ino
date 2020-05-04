/*
  === M5Stacks Sonic The Hedgehog port ===

  !!! WARNING !!!
  This is an unofficial port of the game, this product was created exclusively for educational purposes and
  it should NOT be sold. As for code, it can be used as you like, but in that case, please give me a credit.

  All characters and graphics are copyright of SEGA.

  You can configure the game in a file "GameSettings.h"
  
  --- Controls ---
  Left   button - left
  Right  button - right
  Middle button - jump
  Left and Right button when moving   - roll
  Left and Right button when standing - spindash

  Special thanks to:
  Sonic Physics Guide - http://info.sonicretro.org/Sonic_Physics_Guide
  Sprite Resource     - https://www.spriters-resource.com/

  Author: GalaxyShad, 2020
  GitHub: https://github.com/GalaxyShad
*/

// ========================== //
#include "gameLogo.h"

#include "include\Settings.h"
#include "include\Screen.h"

#include "include\structs\Geometry.h"
#include "include\Level.h"

Screen scr;
Level lv;
int startFrame = 0;
int fps = 0;
float frameFrame = 0;

void setup() {
	M5.begin();
	M5.Lcd.fillScreen(TFT_BLACK);
  M5.Lcd.pushImage(49, 196, 223, 39, (uint16_t*)imgGameLogo);
  scr.create(Size(SCREEN_WIDTH, SCREEN_HEIGHT));
}

void loop() {
  lv = Level();
  lv.create();
  while(lv.isLevelPlaying()) {
    startFrame = millis();
    lv.update();
    if (1.0 / frameFrame <= 36)
      lv.update();
    scr.beginDraw();
    lv.draw();
    scr.endDraw();

    
    M5.Lcd.fillRect(8, 14, 72, 48, TFT_DARKGREY);
    frameFrame = (millis() - startFrame) / 1000.0;
    fps = 1.0 / frameFrame;
    M5.Lcd.setTextColor(TFT_WHITE);
    M5.Lcd.drawString("Fps", 12, 20, 2);
    M5.Lcd.drawString("Rings", 12, 40, 2);
    M5.Lcd.drawNumber(fps, 54, 20, 2);
    M5.Lcd.drawNumber((long int)(*lv.rings), 54, 40, 2);
    
    M5.update();
  }
  
}

