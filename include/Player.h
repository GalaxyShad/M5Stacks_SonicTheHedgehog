#pragma once
#include "GameMath.h"
#include "Settings.h"

#include "structs\Geometry.h"
#include "Terrain.h"
#include "Keyboard.h"
#include "AnimMgr.h"
#include "Camera.h"
#include "Entity.h"
#include "Sfx.h"

#include "entities\Spring.h"
#include "entities\Ring.h"
#include "entities\Enemy.h"
#include "entities\LayerSwitcher.h"
#include "entities\GimmicksGHZ.h"

#include "content\textures\texObjects.h"


// === Constants === //

// = physics =
// normal
#define PL_ACC              0.046875 
#define PL_DEC              0.5 
#define PL_FRC              0.046875
#define PL_TOP              6
#define PL_JMP              6.5
#define PL_GRAV             0.21875
#define PL_AIR              0.09375 

#define PL_SLP              0.125 
#define PL_SLP_ROLL_UP      0.078125 
#define PL_SLP_ROLL_DOWN    0.3125 

#define PL_FRC_ROLL         0.0234375 
#define PL_DEC_ROLL         0.125 

#define PL_FOOT_LEVEL       20

using namespace gmath;

class Player : public Entity
{
    public:
		Player(Vector2f _pos, Terrain& _trn) : Entity(_pos) { trn = &_trn; };
        void create();
        void terrainCollision(Camera& cam);
		void entitiesCollision(std::list<Entity*>& entities, Camera& cam);
        void update();
        void draw(Camera& cam);
		void moveCam(Camera& cam);
        bool isEndLv() {return endLv;}
        int rings = 0;
    private:
        Vector2f spd;
        Terrain* trn;

        // enums
        enum FlrMode { 
            FLOOR, 
            RIGHT_WALL, 
            BOTTOM, 
            LEFT_WALL
        };
        enum Action { 
            ACT_NORMAL, 
            ACT_JUMP, 
            ACT_ROLL, 
            ACT_SKID, 
            ACT_SPINDASH,
			ACT_SPRING,
            ACT_HURT,
            ACT_DIE,
        };
        // controlls
        bool canHorMove = true;

        // movement
        float xsp = 0.0;
        float ysp = 0.0;
        float gsp = 0.0;
        float angle = 0;
        float shiftX = 0;
        float shiftY = 0;
        bool ground = false;
        int gndHeight = 20; // Ground sensor height
        int gndWidth = 7;   // Ground sensors width
        FlrMode flrMode = FLOOR;

        // gameplay
        Action action = ACT_NORMAL;
		bool isSpindashDirRight = false;
        bool standOnObj = false;
        bool sTube = false;
        bool endLv = false;
        std::list<Entity*>::iterator standOnID;

        // timers
        int spindashTimer = 0;
        int ringTimer = 0;
        int horizontalLockTimer = 0;
        int camLagTimer = 0;
        int invicTimer = 0;

        // animation
        bool animFlip = false;
		float anim8Angle = 0.0;
        float animAngle = 0.0;
        int animIdleTimer = 288;
        bool diaAnim = false;

        int layer = 0;

		// debug
		IntRect lSenRect, rSenRect;

        // === functions === //
        void gameplay();
        void movement();
        void animation();
        void switchFlrModes();
        void getHit(std::list<Entity*>& entities);

        Tile getGround(Vector2i& _senPos, int rW, int rH, float _ang);
        Vector2i getRotatedPoint(Vector2f _center, int rW, int rH, float angle);


};