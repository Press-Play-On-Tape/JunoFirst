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

    EnemyType _enemyType;
    uint8_t _x;
    uint8_t _y;
    int8_t _xDelta;
    int8_t _yDelta;
    bool _active;

};


//--------------------------------------------------------------------------------------------------------------------------
// Properties ..

EnemyType Enemy::getType() {
  return _enemyType;
}

uint8_t Enemy::getX() {
  return _x;
}

uint8_t Enemy::getY() {
  return _y;
}

int8_t Enemy::getXDelta() {
  return _xDelta;
}

int8_t Enemy::getYDelta() {
  return _yDelta;
}

bool Enemy::getActive() {
  return _active;
}

void Enemy::setEnemyType(EnemyType val) {
  _enemyType = val;
}

void Enemy::setX(uint8_t val) {
  _x = val;
}

void Enemy::setY(uint8_t val) {
  _y = val;
}

void Enemy::setXDelta(int8_t val) {
  _xDelta = val;
}

void Enemy::setYDelta(int8_t val) {
  _yDelta = val;
}

void Enemy::setActive(bool val) {
  _active = val;
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
