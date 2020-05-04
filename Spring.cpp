#include "include\entities\Spring.h"

void Spring::create()
{
	type = TYPE_SPRING;
    solid = true;
	hitBoxSize = Vector2f(28, 16);
	anim.create(TEX_OBJECTS, (Frame*)framesObjects);
	if (red)
		anim.set(65, 65, 0.0);
	else
		anim.set(67, 67, 0.0);
}

void Spring::doAnim()
{
	if (red)
		anim.set(66, 66, 0);
	else
		anim.set(68, 68, 0);
	animTimer = SPRING_ANIM_TIMER;
}

void Spring::update()
{
	if (animTimer > 0) {
		animTimer--;
	} else {
		if (red)
			anim.set(65, 65, 0);
		else
			anim.set(67, 67, 0);
	}
}

bool Spring::isRed() 
{
	return red;
}
