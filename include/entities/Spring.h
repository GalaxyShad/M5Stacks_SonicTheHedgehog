#pragma once
#include "..\Entity.h"

#define SPRING_ANIM_TIMER 15

class Spring : public Entity 
{
    public:
		Spring(Vector2f _pos, bool _red = false) : Entity(_pos) { red = _red; };
        void create();
		void update();
		void doAnim();
		bool isRed();
	private:
		int animTimer = SPRING_ANIM_TIMER;
		bool red = false;

        
};