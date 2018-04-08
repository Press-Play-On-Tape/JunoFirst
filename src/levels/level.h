#pragma once

#include "../utils/Enums.h"

class Level {

  public: 

    Level() {};

  
    // Properties ..

    int8_t getHorizon();
    uint8_t getWave();
    uint16_t getScore();

    void setHorizon(int8_t val);
    void setWave(uint8_t val);
    void setScore(uint16_t val);


    // Methods ..

    void incHorizon(int8_t val);


  private:

    int8_t _horizon;
    uint8_t _wave;
    uint16_t _score;

};


//--------------------------------------------------------------------------------------------------------------------------
// Properties ..


int8_t Level::getHorizon() {
  return _horizon;
}

uint8_t Level::getWave() {
  return _wave;
}

uint16_t Level::getScore() {
  return _score;
}

void Level::setHorizon(int8_t val) {
  _horizon = val;
}

void Level::setWave(uint8_t val) {
  _wave = val;
}

void Level::setScore(uint16_t val) {
  _score = val;
}



//--------------------------------------------------------------------------------------------------------------------------
// Methods ..

void Level::incHorizon(int8_t val) {

  _horizon = (_horizon + val) % HORIZON_ROW_COUNT;
  if (_horizon < 0) _horizon = _horizon + HORIZON_ROW_COUNT;

}
