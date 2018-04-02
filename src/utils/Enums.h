#pragma once

#include "Arduboy2Ext.h"


#define MAX_NUMBER_OF_ENEMIES             20
#define MAX_NUMBER_OF_BULLETS             10

#define HORIZON_MIN_VALUE                 42
#define HORIZON_INCREMENT                 3
#define HORIZON_COL_COUNT                 7
#define HORIZON_ROW_COUNT                 5
#define ENEMY_FRAME_COUNT                 30
#define ENEMY_FRAME_COUNT_HALF            15

#define ENEMY_DISTANCE_HORIZON_START_1    24
#define ENEMY_DISTANCE_HORIZON_END_1      47
#define ENEMY_DISTANCE_HORIZON_START_2    48
#define ENEMY_DISTANCE_HORIZON_END_2      51
#define ENEMY_DISTANCE_FAR_START          52
#define ENEMY_DISTANCE_FAR_END            57
#define ENEMY_DISTANCE_MEDIUM_START       58
#define ENEMY_DISTANCE_MEDIUM_END         63
#define ENEMY_DISTANCE_CLOSE_START        64
#define ENEMY_DISTANCE_CLOSE_END          122

#define ENEMY_VISIBLE_HORIZON             24

#define WIDTH_HALF                        WIDTH / 2


// ----------------------------------------------------------------------------
//  A better absolute as it uses less memory than the standard one .. 
//
template<typename T> T absT(const T & v) {
  
  return (v < 0) ? -v : v;

}


// ----------------------------------------------------------------------------
//  Clamp the value within the range .. 
//
template <typename T> T clamp(const T& value, const T& low, const T& high) 
{
  return value < low ? low : (value > high ? high : value); 
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

  Horizon,
  Far,
  Medium,
  Close

};


enum class EnemyType : uint8_t {

  EnemyType1,
  EnemyType2,

};


enum class MovementSequence : uint8_t {

  Sequence_1,       // Move left to right by xDelta.  When at edge of screen move forward yDelta, change x direction.  When at bottom of screen, reverse yDelta.
  Sequence_2,       // Move both X and Y simultaneously.  When at an edge of the screen, reverse direction.

};