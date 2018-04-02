#pragma once

#include "../utils/Enums.h"

class Enemy {

  public: 

    Enemy() {};
  
    // Properties ..

    int8_t getX();
    int8_t getY();
    int8_t getXDelta();
    int8_t getYDelta();
    bool getActive();
    EnemyType getType();
    MovementSequence getMovementSequence();
        
    void setX(int8_t val);
    void setY(int8_t val);
    void setXDelta(int8_t val);
    void setYDelta(int8_t val);
    void setActive(bool val);
    void setEnemyType(EnemyType val);
    void setMovementSequence(MovementSequence val);

    // Methods ..

    bool isVisible();
    ImageSize getSize();
    int8_t getXDisplay();
    uint8_t getYDisplay();

    void move(Player *player);
    void move();

  private:

    uint8_t _flags;           // bits 0 - 3 enemy type, bit 4 enabled, bits 5 - 7 movement type
    int8_t _x;
    int8_t _y;
    uint8_t _delta;           // bits 0 - 3 x, bts 4 - 7 y

};


//--------------------------------------------------------------------------------------------------------------------------
// Properties ..

EnemyType Enemy::getType() {
  return static_cast<EnemyType>(_flags & 0x0f);
}

int8_t Enemy::getX() {
  return _x;
}

int8_t Enemy::getY() {
  return _y;
}

int8_t Enemy::getXDelta() {
  return ((_delta & 0x80) == 0x80 ? 0xF0 | ((_delta & 0xF0) >> 4) : (_delta & 0xF0) >> 4);
}

int8_t Enemy::getYDelta() {
  return ((_delta & 0x08) == 0x08 ? 0xF0 | (_delta & 0x0F) : _delta & 0x0F);
}

bool Enemy::getActive() {
  return (_flags & 0x10) > 0;
}

MovementSequence Enemy::getMovementSequence() {
  return static_cast<MovementSequence>(_flags >> 5);
}

void Enemy::setEnemyType(EnemyType val) {
  _flags = (_flags & 0xf0) | static_cast<uint8_t>(val);
}

void Enemy::setX(int8_t val) {
  _x = val;
}

void Enemy::setY(int8_t val) {
  _y = val;
}

void Enemy::setXDelta(int8_t val) {
  _delta = (val >= 0 ? (_delta & 0x0f) | ((val & 0x0f) << 4) : (_delta & 0x0f) | 0x80 | ((val & 0x07) << 4));
}

void Enemy::setYDelta(int8_t val) {
  _delta = (val >= 0 ? (_delta & 0xF0) | (val & 0x0f) : (_delta & 0x0f) | 0x08 | (val & 0x07));
}

void Enemy::setActive(bool val) {
  _flags = (_flags & 0xEF) | (val ? 0x10 : 0x00);
}

void Enemy::setMovementSequence(MovementSequence val) {
  _flags = (_flags & 0x1F) | (static_cast<uint8_t>(val) << 5);
}


//--------------------------------------------------------------------------------------------------------------------------
// Methods ..


bool Enemy::isVisible() {
  return (_flags & 0xf0) > 0 && (_y >= ENEMY_VISIBLE_HORIZON);
}

ImageSize Enemy::getSize() {

  // Return the size of the image to render ..

  switch (_y) {

    case ENEMY_DISTANCE_HORIZON_START_1 ... ENEMY_DISTANCE_HORIZON_END_2:
      return ImageSize::Horizon;

    case ENEMY_DISTANCE_FAR_START ... ENEMY_DISTANCE_FAR_END:
      return ImageSize::Far;

    case ENEMY_DISTANCE_MEDIUM_START ... ENEMY_DISTANCE_MEDIUM_END:
      return ImageSize::Medium;

    default:
      return ImageSize::Close;

  }

}

int8_t Enemy::getXDisplay() {
/*  
  switch (_y) {

    case ENEMY_DISTANCE_HORIZON_START_1 ... ENEMY_DISTANCE_HORIZON_END_2:
      return _x + WIDTH_HALF;           

    case ENEMY_DISTANCE_FAR_START ... ENEMY_DISTANCE_FAR_END:
      return _x + WIDTH_HALF - 2;

    case ENEMY_DISTANCE_MEDIUM_START ... ENEMY_DISTANCE_MEDIUM_END:
      return _x + WIDTH_HALF - 3;

    case ENEMY_DISTANCE_CLOSE_START ... ENEMY_DISTANCE_CLOSE_END:
      return _x + WIDTH_HALF - 6;

    default:
      return _x + WIDTH_HALF;

  }*/

  return (static_cast<int16_t>(_x) * static_cast<int16_t>(_y) / static_cast<int16_t>(96)) + WIDTH_HALF;

}

uint8_t Enemy::getYDisplay() {
  
  switch (_y) {

    // case ENEMY_DISTANCE_HORIZON_START_1 ... ENEMY_DISTANCE_HORIZON_END_1:
    //   return 0;           

    case 0 ... ENEMY_DISTANCE_HORIZON_END_1:
      return 0;           

    default:
      return _y - 48;

  }

}

static const int8_t ENEMY_MINIMUM_X = -96;
static const int8_t ENEMY_MAXIMUM_X = 96;
static const int8_t ENEMY_MINIMUM_Y = 0;
static const int8_t ENEMY_MAXIMUM_Y = 120;

void Enemy::move(Player *player) {

//  _x = clamp(static_cast<int8_t>(_x + (player->getXDelta() / 2)), ENEMY_MINIMUM_X, ENEMY_MAXIMUM_X);


  _y = clamp(static_cast<int8_t>(_y + (player->getYDelta() / 4)), ENEMY_MINIMUM_Y, ENEMY_MAXIMUM_Y);
  
}

void Enemy::move() {

  switch (this->getMovementSequence()) {

    case MovementSequence::Sequence_1:

      if ((this->getXDelta() < 0 && _x > ENEMY_MINIMUM_X) || (this->getXDelta() > 0  && _x < ENEMY_MAXIMUM_X)) {
        _x = _x + this->getXDelta();
      }
      else {
        _y = _y + this->getYDelta();
        this->setXDelta(this->getXDelta() * -1);
      }
      break;

    default:
      _x = _x + this->getXDelta();
      _y = _y + this->getYDelta();
    
  }

}