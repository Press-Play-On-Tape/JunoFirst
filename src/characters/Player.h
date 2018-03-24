#pragma once

class Player {

  public: 

    Player() {};
  
    // Properties ..

    uint8_t getX();
    uint8_t getY();
    int8_t getXDelta();
    int8_t getYDelta();
    
    void setX(uint8_t val);
    void setXDelta(int8_t val);
    void setYDelta(int8_t val);


    // Methods ..

    void reset();
    void incX();
    void decX();

    boolean incYDelta();
    boolean decYDelta();
    boolean decelerate();

  private:

    uint8_t _x;
    int8_t _xDelta;
    int8_t _yDelta;

};


//--------------------------------------------------------------------------------------------------------------------------
// Properties ..

uint8_t Player::getX() {
  return _x;
}

uint8_t Player::getY() {
  return 43;
}

int8_t Player::getXDelta() {
  return _xDelta;
}

int8_t Player::getYDelta() {
  return _yDelta;
}

void Player::setX(uint8_t val) {
  _x = val;
}

void Player::setXDelta(int8_t val) {
  _xDelta = val;
}

void Player::setYDelta(int8_t val) {
  _yDelta = val;
}


//--------------------------------------------------------------------------------------------------------------------------
// Methods ..

void Player::reset() {
  _x = 60;
  _xDelta = 0;
  _yDelta = 0;
}

void Player::incX() {

  if (_x < 122) _x = _x + 2;

}

void Player::decX() {

  if (_x > 2) _x = _x - 2;

}

// Returns true if hte value has changed ..

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