#include "include\entities\LayerSwitcher.h"

void LayerSwitcher::create()
{
    type = TYPE_LAYER_SWITCH;
}

uint8_t LayerSwitcher::getMode()
{
    return mode;
}
