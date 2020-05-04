#pragma once
#include "..\Entity.h"

class LayerSwitcher : public Entity 
{
    public:
        LayerSwitcher(Vector2f _pos, Vector2f _hBox, uint8_t _mode) : Entity(_pos) { mode = _mode; hitBoxSize = _hBox;}
        void create();
        void update() {}
        void draw(Camera& cam) {}
        uint8_t getMode();
    private:
        uint8_t mode;
        
};