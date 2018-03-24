#pragma once

#include "Arduboy2Ext.h"


#define MAX_NUMBER_OF_ENEMIES     10

#define HORIZON_MIN_VALUE         42
#define HORIZON_INCREMENT         3
#define HORIZON_COL_COUNT         7
#define HORIZON_ROW_COUNT         5
#define ENEMY_FRAME_COUNT         30
#define ENEMY_FRAME_COUNT_HALF    15


// ----------------------------------------------------------------------------
//  A better absolute as it uses less memory than the standard one .. 
//
template<typename T> T absT(const T & v) {
  
  return (v < 0) ? -v : v;

}


// ----------------------------------------------------------------------------
//  GameState defines the modes of the game ..
//
enum class GameState : uint8_t {

  Intro,
  GamePlay,
  GameOver

};


enum class ImageSize : uint8_t {

  Far,
  Medium,
  Close

};


enum class EnemyType : uint8_t {

  EnemyType1,
  EnemyType2,

};