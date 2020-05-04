#pragma once
#include "Settings.h"
#include "structs\Geometry.h"
#include "structs\Frame.h"
#include "Camera.h"

class AnimMgr {
    public:

		void create(uint8_t _tex, Frame* _frames);
		void set(int _firstFrame, int _lastFrame, float _spd, bool _isReversive = false);
        void tick();
        void draw(Camera& cam, Vector2f pos, bool horFlip, bool verFlip, float angle);
		float getCurFrame();
        int getLastFrame();
    private:
		uint8_t tex;
        Frame* frames;
        int fFrameIndex = 0;
        int lFrameIndex = 0;
        float curFrame = 0.0;
        float spd = 0.0;
		bool flip = false;
		bool isReversive = false;
};