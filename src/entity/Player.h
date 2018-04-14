#pragma once

#include "../utils/Enums.h"

class Player {

  public: 

    Player() {};
  
    // Properties ..

    uint8_t getLives();
    uint8_t getX();
    uint8_t getY();
    uint8_t getFuel();
    uint8_t getHealth();
    int8_t getXDelta();
    int8_t getYDelta();
    PlayerStatus getStatus();

    void setLives(uint8_t val);
    void setX(uint8_t val);
    void setFuel(uint8_t val);
    void setHealth(uint8_t val);
    void setXDelta(int8_t val);
    void setYDelta(int8_t val);
    void setStatus(PlayerStatus val);

    // Methods ..

    void resetGame();
    void resetWave();
    void incX();
    void decX();
    void incHealth();
    void decFuel();
    void decLives();

    boolean incYDelta();
    boolean decYDelta();
    boolean decelerate();

  private:

    uint8_t _lives;
    uint8_t _x;
    uint8_t _health;
    uint8_t _fuel;
    int8_t _xDelta;
    int8_t _yDelta;
    uint16_t _incHealth;
    PlayerStatus _status; 

};


//--------------------------------------------------------------------------------------------------------------------------
// Properties ..

uint8_t Player::getLives() {
  return _lives;
}

uint8_t Player::getX() {
  return _x;
}

uint8_t Player::getY() {

  #ifdef SHOW_OUT_OF_SIGHT
  return 49;
  #else
  return 48;
  #endif

}

uint8_t Player::getFuel() {
  return _fuel;
}

int8_t Player::getXDelta() {
  return _xDelta;
}

int8_t Player::getYDelta() {
  return _yDelta;
}

PlayerStatus Player::getStatus() {
  return _status;
}

uint8_t Player::getHealth() {
  return _health;
}

void Player::setLives(uint8_t val) {
  _lives = val;
}

void Player::setX(uint8_t val) {
  _x = val;
}

void Player::setFuel(uint8_t val) {
  _fuel = val;
}

void Player::setXDelta(int8_t val) {
  _xDelta = val;
}

void Player::setYDelta(int8_t val) {
  _yDelta = val;
}

void Player::setStatus(PlayerStatus val) {
  _status = val; 
}

void Player::setHealth(uint8_t val) {
  _health = val;
  _incHealth = 0;
}


//--------------------------------------------------------------------------------------------------------------------------
// Methods ..


void Player::resetGame() {

  resetWave();
  _lives = 4;

}

void Player::resetWave() {

  _x = 56;
  _xDelta = 0;
  _yDelta = 0;
  _fuel = 48;
  _health = 7;
  _status = PlayerStatus::Active;

}

void Player::incX() {

  if (_x < 108) _x++;

}

void Player::decX() {

  if (_x > 0) _x--;

}

void Player::decLives() {

  if (_lives > 0) _lives--;

}

// Returns true if the value has changed ..

boolean Player::incYDelta() {

  switch(_yDelta) {

    case -4:      
      _yDelta = -2;
      return true;

    case -2:      
      _yDelta = -1;
      return true;

    case -1:      
      _yDelta = 0;
      return true;
      
    case 0:
      _yDelta = 1;
      return true;

    case 1:
      _yDelta = 2;
      return true;

    case 2:
      _yDelta = 4;
      return true;

  }

  return false;

}

// Returns true if hte value has changed ..

boolean Player::decYDelta() {

  switch(_yDelta) {

    case -2:      
      _yDelta = -4;
      return true;

    case -1:      
      _yDelta = -2;
      return true;
      
    case 0:
      _yDelta = -1;
      return true;

    case 1:
      _yDelta = 0;
      return true;

    case 2:
      _yDelta = 1;
      return true;

    case 4:
      _yDelta = 2;
      return true;

  }

  return false;

}

boolean Player::decelerate() {

  if (_yDelta > 0) return decYDelta();
  if (_yDelta < 0) return incYDelta();

  return false;

}

void Player::incHealth() {

  _incHealth++;

  if (_incHealth == INCREMENT_HEALTH) {

    _incHealth = 0;
    if (_health < 7) _health++;

  }

}

void Player::decFuel() {

  if (_fuel > 0) _fuel--;

}
