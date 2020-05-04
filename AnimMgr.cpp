#include "include\AnimMgr.h"


void AnimMgr::create(uint8_t _tex, Frame* _frames) {
	tex = _tex;
	frames = _frames;
}

void AnimMgr::set(int _firstFrame, int _lastFrame, float _spd, bool _isReversive) {
	isReversive = _isReversive;
    spd = _spd;

	if (!isReversive)
		flip = false;

	if (fFrameIndex != _firstFrame)
		curFrame = _firstFrame;

    fFrameIndex = _firstFrame;
    lFrameIndex = _lastFrame;

    if (curFrame < fFrameIndex)
        curFrame = fFrameIndex;
	if (curFrame >= lFrameIndex+1)
		curFrame = fFrameIndex;
}

void AnimMgr::tick() {
	
	if (!flip)
		curFrame += spd;
	else
		curFrame -= spd;

	if (!isReversive) {
		if (curFrame >= lFrameIndex+1)
			curFrame = fFrameIndex;
		if (curFrame < fFrameIndex)
			curFrame = lFrameIndex;
	} else {
		if (curFrame >= lFrameIndex+1) {
			flip = true;
			curFrame = lFrameIndex;
		}
		if (curFrame < fFrameIndex) {
			flip = false;
			curFrame = fFrameIndex;
		}
	}
}

void AnimMgr::draw(Camera& cam, Vector2f pos, bool horFlip, bool verFlip, float angle) {    
    Vector2i offset;

	if (isReversive)
		horFlip = flip;

    if (!horFlip)
        offset.x = frames[int(curFrame)].offset.x;
    else
        offset.x = frames[int(curFrame)].rect.width - frames[int(curFrame)].offset.x;

    if (!verFlip)
        offset.y = frames[int(curFrame)].offset.y;
    else
        offset.y = frames[int(curFrame)].rect.height - frames[int(curFrame)].offset.y;
	cam.drawRect(tex, frames[int(curFrame)].rect, pos, offset, horFlip, verFlip, angle);
}

float AnimMgr::getCurFrame()
{
	return curFrame;
}

int AnimMgr::getLastFrame()
{
	return lFrameIndex;
}
