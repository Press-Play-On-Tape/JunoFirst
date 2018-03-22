#pragma once

#include "../utils/Enums.h"

class Enemy {

  public: 

    Enemy() {};
  
    // Properties ..

    uint8_t getX();
    uint8_t getY();
    int8_t getXDelta();
    int8_t getYDelta();
    bool getActive();
    EnemyType getType();
        
    void setX(uint8_t val);
    void setY(uint8_t val);
    void setXDelta(int8_t val);
    void setYDelta(int8_t val);
    void setActive(bool val);
    void setEnemyType(EnemyType val);

    ImageSize getSize();

  private:

    uint8_t _flags;           // bits 0 - 3 enemy type, bits 4 - 7 enabled
    uint8_t _x;
    uint8_t _y;
    uint8_t _delta;           // bits 0 - 3 x, bts 4 - 7 y

};


//--------------------------------------------------------------------------------------------------------------------------
// Properties ..

EnemyType Enemy::getType() {
  return static_cast<EnemyType>(_flags & 0x0f);
}

uint8_t Enemy::getX() {
  return _x;
}

uint8_t Enemy::getY() {
  return _y;
}

int8_t Enemy::getXDelta() {
  return ((_delta & 0x80) == 0x80 ? 0xF0 | ((_delta & 0xF0) >> 4) : (_delta & 0xF0) >> 4);
}

int8_t Enemy::getYDelta() {

  return ((_delta & 0x08) == 0x08 ? 0xF0 | (_delta & 0x0F) : _delta & 0xF0);
}

bool Enemy::getActive() {
  return (_flags & 0xf0) > 0;

}

void Enemy::setEnemyType(EnemyType val) {
  _flags = (_flags & 0xf0) | static_cast<uint8_t>(val);
}

void Enemy::setX(uint8_t val) {
  _x = val;
}

void Enemy::setY(uint8_t val) {
  _y = val;
}

void Enemy::setXDelta(int8_t val) {
  _delta = (val >= 0 ? (_delta & 0x0f) | ((val & 0x0f) << 4) : (_delta & 0x0f) | 0x80 | ((val & 0x07) << 4));
}

void Enemy::setYDelta(int8_t val) {
  _delta = (val >= 0 ? (_delta & 0xF0) | (val & 0x0f) : (_delta & 0x0f) | 0x08 | (val & 0x07));
}

void Enemy::setActive(bool val) {
  _flags = (_flags & 0x0f) | (val ? 0x10 : 0x00);
}


//--------------------------------------------------------------------------------------------------------------------------
// Methods ..

ImageSize Enemy::getSize() {

  // Return the size of the iamge to render ..

  switch (_y) {

    case 0 ... 10:
      return ImageSize::Far;

    case 11 ... 20:
      return ImageSize::Medium;

    default:
      return ImageSize::Close;

  }

}
