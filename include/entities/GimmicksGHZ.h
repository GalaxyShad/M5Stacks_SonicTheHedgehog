#pragma once

//#include "content\textures\texGimmicksGHZ.h"

#include "..\Settings.h"
#include "..\Entity.h"
#include "..\Terrain.h"

class GimGHZ_Stone : public Entity
{
    public: GimGHZ_Stone(Vector2f _pos) : Entity(_pos) {}
            void create();
};

class GimGHZ_Bridge : public Entity
{   
    public: GimGHZ_Bridge();
            GimGHZ_Bridge(Vector2f _pos) : Entity(_pos) {}
            bool isActive() { return active; }
            void setActive(bool _active) { active = _active;}
            void create();
            float getY();

            int maxDepression = 0;
            int number = 0;
            int count = 0;
    private:
            bool active = false;
};

class GimGHZ_BridgeController : public Entity
{
    public: GimGHZ_BridgeController(Vector2f _pos, uint8_t count, std::list<Entity*>& ent);
            void create();
            void update();
            void draw(Camera& cam) {}
    private:
            GimGHZ_Bridge** segments;
            int segmentsCount;
            int curSegment = 0;
            int angle = 0;
};

class GimGHZ_Platform : public Entity 
{
        public: GimGHZ_Platform(Vector2f _pos, int _dir, bool _mooving) : Entity(_pos) { dir = _dir; mooving = _mooving;}
                void create();
                void update();
                int getDir() {return dir;}
                float getSpd() { if (!mooving) return 0;
                                 return xsp;}
        private:int dir = 0; // 0 - right 1 - left 2 - up 3 - down
                float angle;
                float xsp = 0;
                float ysp = 0;
                bool mooving = false;
                const float spd = 1;
};

class GimGHZ_SlpPlatform : public Entity
{
    public: GimGHZ_SlpPlatform(Vector2f _pos, bool _left = false) : Entity(_pos) {left = _left;}
            void create();
            void draw(Camera& cam) { anim.draw(cam, pos, left, false, 0); }
            int getHeight(int x) 
            { 
                if (!left) {
                    if (x >= 0 && x < 96) 
                        return heights[x]; 
                    else  if (x < 0)
                        return 13; 
                    else 
                        return 29;
                } else {
                    if (x >= 0 && x < 96) 
                        return heights[95 - x]; 
                    else  if (x < 0)
                        return 29; 
                    else 
                        return 13;    
                }
            }
    private:
        bool left = false;
        int heights[96]={
                        13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
                        13, 13, 13, 13, 14, 14, 14, 14, 15, 15, 15, 15, 16, 16, 16, 16,
                        17, 17, 17, 17, 18, 18, 18, 18, 19, 19, 19, 19, 20, 20, 20, 20,
                        21, 21, 21, 21, 22, 22, 22, 22, 23, 23, 23, 23, 24, 24, 24, 24,
                        25, 25, 25, 25, 26, 26, 26, 26, 27, 27, 27, 27, 28, 28, 28, 28,
                        29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29  
                        };
};

class GimGHZ_Wall : public Entity
{
    public: GimGHZ_Wall(Vector2f _pos, int _ty) : Entity(_pos) {ty = _ty;}
            void create() {
                hitBoxSize = Vector2f(16, 64);
	            anim.create(TEX_GHZ_GIMM, (Frame*)framesGhzGim);
                anim.set(4 + ty, 4 + ty, 0);
                solid = true;
            };
    private: 
            int ty = 0;
};

class GimGHZ_STube : public Entity
{
   public:
        GimGHZ_STube(Vector2f _pos, uint8_t _mode) : Entity(_pos) { mode = _mode;}
        void create() {type = TYPE_STUBE_CNTRL; hitBoxSize = Vector2f(16, 64);}
        void update() {}
        void draw(Camera& cam) {}
        uint8_t getMode() {return mode; };
    private:
        uint8_t mode;
};

class SignPost : public Entity
{
   public:
        SignPost(Vector2f _pos) : Entity(_pos) {}
        void create() {
            type = TYPE_SIGN_POST; 
            hitBoxSize = Vector2f(48, 48); 
            anim.create(TEX_OBJECTS, (Frame*)framesObjects);
            animPost.create(TEX_OBJECTS, (Frame*)framesObjects);
            anim.set(105, 105, 0); 
            animPost.set(104, 104, 0); 
            }
        void draw(Camera& cam) {
            animPost.draw(cam, Vector2f(pos.x, pos.y + 16), false, false, 0);
            anim.draw(cam, Vector2f(pos.x, pos.y - 8), false, false, 0);
        }
        void setAnim(bool spin) {
            if (spin && animCount < 10) {
                if (anim.getCurFrame() >= 108)
                    animCount++;
                anim.set(105, 108, 0.5); 
            }
            else 
            {
                animCount = 50;
                anim.set(109, 109, 0); 
            }
        }
    private:
        AnimMgr animPost;
        int animCount = 0;
};
