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
    EnemyStatus getStatus();
    EnemyType getType();
    MovementSequence getMovementSequence();
        
    void setX(int8_t val);
    void setY(int8_t val);
    void setXDelta(int8_t val);
    void setYDelta(int8_t val);
    void setStatus(EnemyStatus val);
    void setEnemyType(EnemyType val);
    void setMovementSequence(MovementSequence val);

    // Methods ..

    bool isVisible();
    ImageSize getSize();
    int8_t getXDisplay();
    uint8_t getYDisplay();
    uint8_t getWidth();
    uint8_t getHeight();

    void move(Player *player);
    void move();

  private:

    uint8_t _flags;           // bits 0 - 3 enemy type, bits 4 - 7 movement type
    int8_t _x;
    int8_t _y;
    uint8_t _delta;           // bits 0 - 3 x, bits 4 - 7 _y
    EnemyStatus _status; 

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

EnemyStatus Enemy::getStatus() {
  return _status;
}

MovementSequence Enemy::getMovementSequence() {
  return static_cast<MovementSequence>(_flags >> 4);
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

void Enemy::setStatus(EnemyStatus val) {
  _status = val; 
}

void Enemy::setMovementSequence(MovementSequence val) {
  _flags = (_flags & 0x0F) | (static_cast<uint8_t>(val) << 4);
}


//--------------------------------------------------------------------------------------------------------------------------
// Methods ..


bool Enemy::isVisible() {
  return _status > EnemyStatus::Dead && (_y >= ENEMY_VISIBLE_HORIZON);
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

  uint8_t x = (static_cast<int16_t>(_x) * static_cast<int16_t>(_y) / static_cast<int16_t>(96)) + WIDTH_HALF;

  switch (_y) {

    case ENEMY_DISTANCE_HORIZON_START_1 ... ENEMY_DISTANCE_HORIZON_END_2:
      return x;           

    case ENEMY_DISTANCE_FAR_START ... ENEMY_DISTANCE_FAR_END:
      return x - ENEMY_DISTANCE_FAR_WIDTH_HALF;

    case ENEMY_DISTANCE_MEDIUM_START ... ENEMY_DISTANCE_MEDIUM_END:
      return x - ENEMY_DISTANCE_MEDIUM_WIDTH_HALF;

    case ENEMY_DISTANCE_CLOSE_START ... ENEMY_DISTANCE_CLOSE_END:
      return x - ENEMY_DISTANCE_CLOSE_WIDTH_HALF;

    default:
      return x;

  }  

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


uint8_t Enemy::getWidth() {

  switch (_y) {

    case ENEMY_DISTANCE_HORIZON_START_1 ... ENEMY_DISTANCE_HORIZON_END_2:
      return 1;           

    case ENEMY_DISTANCE_FAR_START ... ENEMY_DISTANCE_FAR_END:
      return ENEMY_DISTANCE_FAR_WIDTH;

    case ENEMY_DISTANCE_MEDIUM_START ... ENEMY_DISTANCE_MEDIUM_END:
      return ENEMY_DISTANCE_MEDIUM_WIDTH;

    case ENEMY_DISTANCE_CLOSE_START ... ENEMY_DISTANCE_CLOSE_END:
      return ENEMY_DISTANCE_CLOSE_WIDTH;

    default: return 0;

  }  

}


uint8_t Enemy::getHeight() {

  switch (_y) {

    case ENEMY_DISTANCE_HORIZON_START_1 ... ENEMY_DISTANCE_HORIZON_END_2:
      return 1;           

    case ENEMY_DISTANCE_FAR_START ... ENEMY_DISTANCE_FAR_END:
      return ENEMY_DISTANCE_FAR_HEIGHT;

    case ENEMY_DISTANCE_MEDIUM_START ... ENEMY_DISTANCE_MEDIUM_END:
      return ENEMY_DISTANCE_MEDIUM_HEIGHT;

    case ENEMY_DISTANCE_CLOSE_START ... ENEMY_DISTANCE_CLOSE_END:
      return ENEMY_DISTANCE_CLOSE_HEIGHT;

    default: return 0;

  }  

}

void Enemy::move(Player *player) {

  _y = clamp(static_cast<int8_t>(_y + (player->getYDelta() / 4)), ENEMY_MINIMUM_Y, ENEMY_MAXIMUM_Y);
  
}

void Enemy::move() {

  switch (this->getMovementSequence()) {

    case MovementSequence::Sequence_1:

      if ((this->getXDelta() < 0 && _x > ENEMY_MINIMUM_X) || (this->getXDelta() > 0  && _x < ENEMY_MAXIMUM_X)) {

        _x = _x + this->getXDelta();

      }
      else {

        this->setXDelta(static_cast<int8_t>(this->getXDelta()) * -1);

        if ((this->getYDelta() < 0 && _y > ENEMY_MINIMUM_Y) || (this->getYDelta() > 0  && _y < ENEMY_MAXIMUM_Y)) {

          _y = _y + this->getYDelta();

        }
        else {

          this->setYDelta(static_cast<int8_t>(this->getYDelta()) * -1);

        }

      }
      break;

    case MovementSequence::Sequence_2:

      if ((this->getXDelta() < 0 && _x > ENEMY_MINIMUM_X) || (this->getXDelta() > 0  && _x < ENEMY_MAXIMUM_X)) {

        _x = _x + this->getXDelta();

      }
      else {

        this->setXDelta(static_cast<int8_t>(this->getXDelta()) * -1);

      }

      if ((this->getYDelta() < 0 && _y > ENEMY_MINIMUM_Y) || (this->getYDelta() > 0  && _y < ENEMY_MAXIMUM_Y)) {

        _y = _y + this->getYDelta();

      }
      else {

        this->setYDelta(static_cast<int8_t>(this->getYDelta()) * -1);

      }

      break;

    default:
      _x = _x + this->getXDelta();
      _y = _y + this->getYDelta();
    
  }

}