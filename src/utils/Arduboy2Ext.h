#pragma once

#include <Arduboy2.h>

class Arduboy2Ext : public Arduboy2 {

  public:

    Arduboy2Ext();

    uint8_t justPressedButtons() const;
    uint8_t pressedButtons() const;
    uint16_t getFrameCount() const;
    uint8_t getFrameCount(uint8_t mod) const;

    void clearButtonState();
    
};
