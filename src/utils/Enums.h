#pragma once

#include "Arduboy2Ext.h"

#define USE_DOTTED_LINES


static const uint8_t WIDTH_HALF                           = 60;

static const uint8_t MAX_NUMBER_OF_ENEMIES                = 12;
static const uint8_t MAX_NUMBER_OF_ENEMIES_PER_FORMATION  = 4;
static const uint8_t MAX_NUMBER_OF_BULLETS                = 10;
static const uint16_t INCREMENT_HEALTH                    = 800;

static const uint8_t MAX_NUMBER_OF_SCORES                 = 5;
static const uint8_t DO_NOT_EDIT_SLOT                     = 255;

static const uint8_t HORIZON_MIN_VALUE                    = 42;
static const uint8_t HORIZON_INCREMENT                    = 3;
static const uint8_t HORIZON_COL_COUNT                    = 7;
static const uint8_t HORIZON_ROW_COUNT                    = 5;
static const uint8_t ENEMY_FRAME_COUNT                    = 30;
static const uint8_t ENEMY_FRAME_COUNT_HALF               = 15;

static const uint8_t ENEMY_DISTANCE_HORIZON_START_1       = 24;
static const uint8_t ENEMY_DISTANCE_HORIZON_END_1         = 47;
static const uint8_t ENEMY_DISTANCE_HORIZON_START_2       = 48;
static const uint8_t ENEMY_DISTANCE_HORIZON_END_2         = 51;
static const uint8_t ENEMY_DISTANCE_FAR_START             = 52;
static const uint8_t ENEMY_DISTANCE_FAR_END               = 57;
static const uint8_t ENEMY_DISTANCE_MEDIUM_START          = 58;
static const uint8_t ENEMY_DISTANCE_MEDIUM_END            = 63;
static const uint8_t ENEMY_DISTANCE_CLOSE_START           = 64;
static const uint8_t ENEMY_DISTANCE_CLOSE_END             = 122;

static const uint8_t ENEMY_VISIBLE_HORIZON                = 24;
static const uint8_t INTRO_DELAY                          = 60;

static const int8_t ENEMY_MINIMUM_X                       = -80;
static const int8_t ENEMY_MAXIMUM_X                       = 80;
static const int8_t ENEMY_MINIMUM_Y                       = 0;
static const int8_t ENEMY_MAXIMUM_Y                       = 120;

static const uint8_t ENEMY_DISTANCE_FAR_WIDTH             = 5;
static const uint8_t ENEMY_DISTANCE_MEDIUM_WIDTH          = 8;
static const uint8_t ENEMY_DISTANCE_CLOSE_WIDTH           = 9;

static const uint8_t ENEMY_DISTANCE_FAR_HEIGHT            = 5;
static const uint8_t ENEMY_DISTANCE_MEDIUM_HEIGHT         = 7;
static const uint8_t ENEMY_DISTANCE_CLOSE_HEIGHT          = 13;

static const uint8_t ENEMY_DISTANCE_FAR_WIDTH_HALF        = 2;
static const uint8_t ENEMY_DISTANCE_MEDIUM_WIDTH_HALF     = 3;
static const uint8_t ENEMY_DISTANCE_CLOSE_WIDTH_HALF      = 6;

static const uint8_t FRAME_RATE_1                         = 1;
static const uint8_t FRAME_RATE_2                         = 2;
static const uint8_t FRAME_RATE_4                         = 4;
static const uint8_t FRAME_RATE_16                        = 16;


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

  Intro_Init,
  Intro,
  ScoreTable,
  WaveInit,
  GamePlay,
  GameOver_Init,
  GameOver,
  SaveScore,
  HighScore,
  Credits

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
  EnemyType3,
  EnemyType4,

};


enum class MovementSequence : uint8_t {

  Sequence_1,       // Move left to right by xDelta.  When at edge of screen move forward yDelta, change x direction.  When at bottom of screen, reverse yDelta.
  Sequence_2,       // Move both X and Y simultaneously.  When at an edge of the screen, reverse direction.

};


enum class EnemyStatus : uint8_t {

  Dead,
  Explosion1,
  Explosion2,
  Explosion3,
  Explosion4,
  Active

};


enum class PlayerStatus : uint8_t {

  Dead,
  Dead_Delay_01,
  Dead_Delay_02,
  Dead_Delay_03,
  Dead_Delay_04,
  Dead_Delay_05,
  Dead_Delay_06,
  Dead_Delay_07,
  Dead_Delay_08,
  Dead_Delay_09,
  Dead_Delay_10,
  Explosion1,
  Explosion2,
  Explosion3,
  Explosion4,
  Active

};


// EnemyStatus ..

inline EnemyStatus operator++( EnemyStatus & c ) {

  c = static_cast<EnemyStatus>( static_cast<uint8_t>(c) + 1 );
  return c;

}

inline EnemyStatus operator++( EnemyStatus & c, int ) {

  EnemyStatus result = c;
  ++c;
  return result;

}

inline EnemyStatus operator--( EnemyStatus & c ) {
 
  c = static_cast<EnemyStatus>( static_cast<uint8_t>(c) - 1 );
  return c;

}

inline EnemyStatus operator--( EnemyStatus & c, int ) {

  EnemyStatus result = c;
  --c;
  return result;

}


// PlayerStatus ..

inline PlayerStatus operator++( PlayerStatus & c ) {

  c = static_cast<PlayerStatus>( static_cast<uint8_t>(c) + 1 );
  return c;

}

inline PlayerStatus operator++( PlayerStatus & c, int ) {

  PlayerStatus result = c;
  ++c;
  return result;

}

inline PlayerStatus operator--( PlayerStatus & c ) {
 
  c = static_cast<PlayerStatus>( static_cast<uint8_t>(c) - 1 );
  return c;

}

inline PlayerStatus operator--( PlayerStatus & c, int ) {

  PlayerStatus result = c;
  --c;
  return result;

}