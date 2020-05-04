#pragma once

#include "..\Settings.h"
#include "..\Entity.h"
#include "..\Terrain.h"

class Enemy : public Entity
{
    public:
        Enemy(Vector2f _pos) : Entity(_pos) {}
        void setAbilityToDying(bool _canDie);
        virtual void trnCollision(Terrain& trn) {}
    private:
        bool canDie = true;
};