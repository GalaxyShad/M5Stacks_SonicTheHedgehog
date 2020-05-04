#pragma once
 

struct Block {
    uint8_t height;
    uint8_t type;

    Block(uint8_t _height, uint8_t _type):
        height(_height), type(_type) {}
};