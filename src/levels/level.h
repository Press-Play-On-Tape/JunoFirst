#pragma once

#include "../utils/Enums.h"

class Level {

  public: 

    Level() {};

  
    // Properties ..

    int8_t getHorizon();

    void setHorizon(int8_t val);


    // Methods ..

    void incHorizon(int8_t val);


  private:

    int8_t _horizon;

};


//--------------------------------------------------------------------------------------------------------------------------
// Properties ..


int8_t Level::getHorizon() {
  return _horizon;
}


void Level::setHorizon(int8_t val) {
  _horizon = val;
}



//--------------------------------------------------------------------------------------------------------------------------
// Methods ..

void Level::incHorizon(int8_t val) {

  _horizon = (_horizon + val) % HORIZON_ROW_COUNT;
  if (_horizon < 0) _horizon = _horizon + HORIZON_ROW_COUNT;

}
