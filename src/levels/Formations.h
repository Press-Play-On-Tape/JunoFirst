#pragma once

#include "../utils/Enums.h"

#ifndef TEST_ASTRONAUT
// static const uint8_t NUMBER_OF_FORMATIONS_WITHOUT_ASTRONAUT  = 28;
// static const uint8_t NUMBER_OF_FORMATIONS_WITH_ASTRONAUT  = 31;
static const uint8_t NUMBER_OF_FORMATIONS_WITHOUT_ASTRONAUT  = 1;
static const uint8_t NUMBER_OF_FORMATIONS_WITH_ASTRONAUT  = 1;
#else
static const uint8_t NUMBER_OF_FORMATIONS_WITHOUT_ASTRONAUT  = 1;
static const uint8_t NUMBER_OF_FORMATIONS_WITH_ASTRONAUT  = 1;
#endif

static const uint8_t MAX_DELAY_BETWEEN_FORMATIONS = 100;
static const uint8_t MIN_DELAY_BETWEEN_FORMATIONS = MAX_DELAY_BETWEEN_FORMATIONS / 2;
static const uint8_t LEVEL_DELAY_BETWEEN_FORMATIONS = (MAX_DELAY_BETWEEN_FORMATIONS / 10);


// --------------------------------------------------------------------------------------------------------------------------------------------
// A block of four enemies, travelling in formation.

const int8_t PROGMEM formation_00[] = {
  4,  
  static_cast<uint8_t>(EnemyType::EnemyType1), ENEMY_MINIMUM_X, 14, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_1), static_cast<uint8_t>(EnemyStatus::Active), 
  static_cast<uint8_t>(EnemyType::EnemyType1), ENEMY_MINIMUM_X + 33, 14, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_1), static_cast<uint8_t>(EnemyStatus::Active), 
  static_cast<uint8_t>(EnemyType::EnemyType3), ENEMY_MINIMUM_X, 24, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_1), static_cast<uint8_t>(EnemyStatus::Active), 
  static_cast<uint8_t>(EnemyType::EnemyType3), ENEMY_MINIMUM_X + 33, 24, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_1), static_cast<uint8_t>(EnemyStatus::Active), 
};

const int8_t PROGMEM formation_01[] = {
  4,  
  static_cast<uint8_t>(EnemyType::EnemyType2), ENEMY_MINIMUM_X, 14, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_1), static_cast<uint8_t>(EnemyStatus::Active),  
  static_cast<uint8_t>(EnemyType::EnemyType2), ENEMY_MINIMUM_X + 33, 14, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_1), static_cast<uint8_t>(EnemyStatus::Active),  
  static_cast<uint8_t>(EnemyType::EnemyType4), ENEMY_MINIMUM_X, 24, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_1), static_cast<uint8_t>(EnemyStatus::Active), 
  static_cast<uint8_t>(EnemyType::EnemyType4), ENEMY_MINIMUM_X + 33, 24, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_1), static_cast<uint8_t>(EnemyStatus::Active), 
};

const int8_t PROGMEM formation_02[] = {
  4,  
  static_cast<uint8_t>(EnemyType::EnemyType3), ENEMY_MINIMUM_X, 14, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_1), static_cast<uint8_t>(EnemyStatus::Active), 
  static_cast<uint8_t>(EnemyType::EnemyType3), ENEMY_MINIMUM_X + 33, 14, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_1), static_cast<uint8_t>(EnemyStatus::Active), 
  static_cast<uint8_t>(EnemyType::EnemyType1), ENEMY_MAXIMUM_X, 24, -3, 2, static_cast<uint8_t>(MovementSequence::Sequence_1), static_cast<uint8_t>(EnemyStatus::Active), 
  static_cast<uint8_t>(EnemyType::EnemyType1), ENEMY_MAXIMUM_X + 33, 24, -3, 2, static_cast<uint8_t>(MovementSequence::Sequence_1), static_cast<uint8_t>(EnemyStatus::Active), 
};

const int8_t PROGMEM formation_03[] = {
  4,  
  static_cast<uint8_t>(EnemyType::EnemyType2), ENEMY_MINIMUM_X, 14, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_1), static_cast<uint8_t>(EnemyStatus::Active), 
  static_cast<uint8_t>(EnemyType::EnemyType2), ENEMY_MINIMUM_X + 33, 14, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_1), static_cast<uint8_t>(EnemyStatus::Active), 
  static_cast<uint8_t>(EnemyType::EnemyType4), ENEMY_MAXIMUM_X, 24, -3, 2, static_cast<uint8_t>(MovementSequence::Sequence_1), static_cast<uint8_t>(EnemyStatus::Active), 
  static_cast<uint8_t>(EnemyType::EnemyType4), ENEMY_MAXIMUM_X + 33, 24, -3, 2, static_cast<uint8_t>(MovementSequence::Sequence_1), static_cast<uint8_t>(EnemyStatus::Active), 
};


// --------------------------------------------------------------------------------------------------------------------------------------------
// Two enemies - travelling diagonally from top left to bottom right.  

const int8_t PROGMEM formation_04[] = {
  2,  
  static_cast<uint8_t>(EnemyType::EnemyType1), ENEMY_MINIMUM_X, 14, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_2), static_cast<uint8_t>(EnemyStatus::Active), 
  static_cast<uint8_t>(EnemyType::EnemyType1), ENEMY_MINIMUM_X + 23, 14, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_2), static_cast<uint8_t>(EnemyStatus::Active), 
};

const int8_t PROGMEM formation_05[] = {
  2,  
  static_cast<uint8_t>(EnemyType::EnemyType2), ENEMY_MINIMUM_X, 14, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_2), static_cast<uint8_t>(EnemyStatus::Active), 
  static_cast<uint8_t>(EnemyType::EnemyType2), ENEMY_MINIMUM_X + 23, 14, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_2), static_cast<uint8_t>(EnemyStatus::Active), 
};

const int8_t PROGMEM formation_06[] = {
  2,  
  static_cast<uint8_t>(EnemyType::EnemyType3), ENEMY_MINIMUM_X, 14, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_2), static_cast<uint8_t>(EnemyStatus::Active), 
  static_cast<uint8_t>(EnemyType::EnemyType3), ENEMY_MINIMUM_X + 23, 14, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_2), static_cast<uint8_t>(EnemyStatus::Active), 
};

const int8_t PROGMEM formation_07[] = {
  2,  
  static_cast<uint8_t>(EnemyType::EnemyType4), ENEMY_MINIMUM_X, 14, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_2), static_cast<uint8_t>(EnemyStatus::Active), 
  static_cast<uint8_t>(EnemyType::EnemyType4), ENEMY_MINIMUM_X + 23, 14, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_2), static_cast<uint8_t>(EnemyStatus::Active), 
};


// --------------------------------------------------------------------------------------------------------------------------------------------
// Two enemies - travelling diagonally from top right to bottom left.  

const int8_t PROGMEM formation_08[] = {
  2,  
  static_cast<uint8_t>(EnemyType::EnemyType1), ENEMY_MAXIMUM_X - 23, 14, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_2), static_cast<uint8_t>(EnemyStatus::Active), 
  static_cast<uint8_t>(EnemyType::EnemyType1), ENEMY_MINIMUM_X, 14, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_2), static_cast<uint8_t>(EnemyStatus::Active), 
};

const int8_t PROGMEM formation_09[] = {
  2,  
  static_cast<uint8_t>(EnemyType::EnemyType2), ENEMY_MAXIMUM_X - 23, 14, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_2), static_cast<uint8_t>(EnemyStatus::Active), 
  static_cast<uint8_t>(EnemyType::EnemyType2), ENEMY_MINIMUM_X, 14, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_2), static_cast<uint8_t>(EnemyStatus::Active), 
};

const int8_t PROGMEM formation_10[] = {
  2,  
  static_cast<uint8_t>(EnemyType::EnemyType3), ENEMY_MAXIMUM_X - 23, 14, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_2), static_cast<uint8_t>(EnemyStatus::Active), 
  static_cast<uint8_t>(EnemyType::EnemyType3), ENEMY_MINIMUM_X, 14, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_2), static_cast<uint8_t>(EnemyStatus::Active), 
};

const int8_t PROGMEM formation_11[] = {
  2,  
  static_cast<uint8_t>(EnemyType::EnemyType4), ENEMY_MAXIMUM_X - 23, 14, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_2), static_cast<uint8_t>(EnemyStatus::Active), 
  static_cast<uint8_t>(EnemyType::EnemyType4), ENEMY_MINIMUM_X, 14, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_2), static_cast<uint8_t>(EnemyStatus::Active), 
};


// --------------------------------------------------------------------------------------------------------------------------------------------
// Four enemy - X pattern

const int8_t PROGMEM formation_12[] = {
  4,  
  static_cast<uint8_t>(EnemyType::EnemyType1), ENEMY_MINIMUM_X + 5, 4, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_2), static_cast<uint8_t>(EnemyStatus::Active), 
  static_cast<uint8_t>(EnemyType::EnemyType1), ENEMY_MINIMUM_X + 5, 24, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_2), static_cast<uint8_t>(EnemyStatus::Active), 
  static_cast<uint8_t>(EnemyType::EnemyType2), ENEMY_MAXIMUM_X - 5, 4, -2, 2, static_cast<uint8_t>(MovementSequence::Sequence_2), static_cast<uint8_t>(EnemyStatus::Active), 
  static_cast<uint8_t>(EnemyType::EnemyType2), ENEMY_MAXIMUM_X - 5, 24, -2, 2, static_cast<uint8_t>(MovementSequence::Sequence_2), static_cast<uint8_t>(EnemyStatus::Active), 
};

const int8_t PROGMEM formation_13[] = {
  4,  
  static_cast<uint8_t>(EnemyType::EnemyType2), ENEMY_MINIMUM_X + 5, 4, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_2), static_cast<uint8_t>(EnemyStatus::Active), 
  static_cast<uint8_t>(EnemyType::EnemyType2), ENEMY_MINIMUM_X + 5, 24, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_2), static_cast<uint8_t>(EnemyStatus::Active), 
  static_cast<uint8_t>(EnemyType::EnemyType3), ENEMY_MAXIMUM_X - 5, 4, -2, 2, static_cast<uint8_t>(MovementSequence::Sequence_2), static_cast<uint8_t>(EnemyStatus::Active), 
  static_cast<uint8_t>(EnemyType::EnemyType3), ENEMY_MAXIMUM_X - 5, 24, -2, 2, static_cast<uint8_t>(MovementSequence::Sequence_2), static_cast<uint8_t>(EnemyStatus::Active), 
};

const int8_t PROGMEM formation_14[] = {
  4,  
  static_cast<uint8_t>(EnemyType::EnemyType3), ENEMY_MINIMUM_X + 5, 4, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_2), static_cast<uint8_t>(EnemyStatus::Active), 
  static_cast<uint8_t>(EnemyType::EnemyType3), ENEMY_MINIMUM_X + 5, 24, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_2), static_cast<uint8_t>(EnemyStatus::Active), 
  static_cast<uint8_t>(EnemyType::EnemyType4), ENEMY_MAXIMUM_X - 5, 4, -2, 2, static_cast<uint8_t>(MovementSequence::Sequence_2), static_cast<uint8_t>(EnemyStatus::Active), 
  static_cast<uint8_t>(EnemyType::EnemyType4), ENEMY_MAXIMUM_X - 5, 24, -2, 2, static_cast<uint8_t>(MovementSequence::Sequence_2), static_cast<uint8_t>(EnemyStatus::Active), 
};

const int8_t PROGMEM formation_15[] = {
  4,  
  static_cast<uint8_t>(EnemyType::EnemyType4), ENEMY_MINIMUM_X + 5, 4, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_2), static_cast<uint8_t>(EnemyStatus::Active), 
  static_cast<uint8_t>(EnemyType::EnemyType4), ENEMY_MINIMUM_X + 5, 24, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_2), static_cast<uint8_t>(EnemyStatus::Active), 
  static_cast<uint8_t>(EnemyType::EnemyType1), ENEMY_MAXIMUM_X - 5, 4, -2, 2, static_cast<uint8_t>(MovementSequence::Sequence_2), static_cast<uint8_t>(EnemyStatus::Active), 
  static_cast<uint8_t>(EnemyType::EnemyType1), ENEMY_MAXIMUM_X - 5, 24, -2, 2, static_cast<uint8_t>(MovementSequence::Sequence_2), static_cast<uint8_t>(EnemyStatus::Active), 
};


// --------------------------------------------------------------------------------------------------------------------------------------------
// Two enemies - travelling diagonally from top left to bottom right.  

const int8_t PROGMEM formation_16[] = {
  2,  
  static_cast<uint8_t>(EnemyType::EnemyType1), ENEMY_MINIMUM_X, 14, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_3), static_cast<uint8_t>(EnemyStatus::Active), 
  static_cast<uint8_t>(EnemyType::EnemyType1), ENEMY_MINIMUM_X + 23, 14, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_3), static_cast<uint8_t>(EnemyStatus::Active), 
};

const int8_t PROGMEM formation_17[] = {
  2,  
  static_cast<uint8_t>(EnemyType::EnemyType2), ENEMY_MINIMUM_X, 14, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_3), static_cast<uint8_t>(EnemyStatus::Active), 
  static_cast<uint8_t>(EnemyType::EnemyType2), ENEMY_MINIMUM_X + 23, 14, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_3), static_cast<uint8_t>(EnemyStatus::Active), 
};

const int8_t PROGMEM formation_18[] = {
  2,  
  static_cast<uint8_t>(EnemyType::EnemyType3), ENEMY_MINIMUM_X, 14, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_3), static_cast<uint8_t>(EnemyStatus::Active), 
  static_cast<uint8_t>(EnemyType::EnemyType3), ENEMY_MINIMUM_X + 23, 14, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_3), static_cast<uint8_t>(EnemyStatus::Active), 
};

const int8_t PROGMEM formation_19[] = {
  2,  
  static_cast<uint8_t>(EnemyType::EnemyType4), ENEMY_MINIMUM_X, 14, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_3), static_cast<uint8_t>(EnemyStatus::Active), 
  static_cast<uint8_t>(EnemyType::EnemyType4), ENEMY_MINIMUM_X + 23, 14, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_3), static_cast<uint8_t>(EnemyStatus::Active), 
};


// --------------------------------------------------------------------------------------------------------------------------------------------
// Two enemies - travelling diagonally from top right to bottom left.  

const int8_t PROGMEM formation_20[] = {
  2,  
  static_cast<uint8_t>(EnemyType::EnemyType1), ENEMY_MAXIMUM_X - 23, 14, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_3), static_cast<uint8_t>(EnemyStatus::Active), 
  static_cast<uint8_t>(EnemyType::EnemyType1), ENEMY_MINIMUM_X, 14, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_3), static_cast<uint8_t>(EnemyStatus::Active), 
};

const int8_t PROGMEM formation_21[] = {
  2,  
  static_cast<uint8_t>(EnemyType::EnemyType2), ENEMY_MAXIMUM_X - 23, 14, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_3), static_cast<uint8_t>(EnemyStatus::Active), 
  static_cast<uint8_t>(EnemyType::EnemyType2), ENEMY_MINIMUM_X, 14, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_3), static_cast<uint8_t>(EnemyStatus::Active), 
};

const int8_t PROGMEM formation_22[] = {
  2,  
  static_cast<uint8_t>(EnemyType::EnemyType3), ENEMY_MAXIMUM_X - 23, 14, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_3), static_cast<uint8_t>(EnemyStatus::Active), 
  static_cast<uint8_t>(EnemyType::EnemyType3), ENEMY_MINIMUM_X, 14, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_3), static_cast<uint8_t>(EnemyStatus::Active), 
};

const int8_t PROGMEM formation_23[] = {
  2,  
  static_cast<uint8_t>(EnemyType::EnemyType4), ENEMY_MAXIMUM_X - 23, 14, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_3), static_cast<uint8_t>(EnemyStatus::Active), 
  static_cast<uint8_t>(EnemyType::EnemyType4), ENEMY_MINIMUM_X, 14, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_3), static_cast<uint8_t>(EnemyStatus::Active), 
};


// --------------------------------------------------------------------------------------------------------------------------------------------
// Four enemy - X pattern

const int8_t PROGMEM formation_24[] = {
  4,  
  static_cast<uint8_t>(EnemyType::EnemyType1), ENEMY_MINIMUM_X + 5, 4, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_3), static_cast<uint8_t>(EnemyStatus::Active), 
  static_cast<uint8_t>(EnemyType::EnemyType1), ENEMY_MINIMUM_X + 5, 24, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_3), static_cast<uint8_t>(EnemyStatus::Active), 
  static_cast<uint8_t>(EnemyType::EnemyType2), ENEMY_MAXIMUM_X - 5, 4, -2, 2, static_cast<uint8_t>(MovementSequence::Sequence_3), static_cast<uint8_t>(EnemyStatus::Active), 
  static_cast<uint8_t>(EnemyType::EnemyType2), ENEMY_MAXIMUM_X - 5, 24, -2, 2, static_cast<uint8_t>(MovementSequence::Sequence_3), static_cast<uint8_t>(EnemyStatus::Active), 
};

const int8_t PROGMEM formation_25[] = {
  4,  
  static_cast<uint8_t>(EnemyType::EnemyType2), ENEMY_MINIMUM_X + 5, 4, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_3), static_cast<uint8_t>(EnemyStatus::Active), 
  static_cast<uint8_t>(EnemyType::EnemyType2), ENEMY_MINIMUM_X + 5, 24, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_3), static_cast<uint8_t>(EnemyStatus::Active), 
  static_cast<uint8_t>(EnemyType::EnemyType3), ENEMY_MAXIMUM_X - 5, 4, -2, 2, static_cast<uint8_t>(MovementSequence::Sequence_3), static_cast<uint8_t>(EnemyStatus::Active), 
  static_cast<uint8_t>(EnemyType::EnemyType3), ENEMY_MAXIMUM_X - 5, 24, -2, 2, static_cast<uint8_t>(MovementSequence::Sequence_3), static_cast<uint8_t>(EnemyStatus::Active), 
};

const int8_t PROGMEM formation_26[] = {
  4,  
  static_cast<uint8_t>(EnemyType::EnemyType3), ENEMY_MINIMUM_X + 5, 4, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_3), static_cast<uint8_t>(EnemyStatus::Active), 
  static_cast<uint8_t>(EnemyType::EnemyType3), ENEMY_MINIMUM_X + 5, 24, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_3), static_cast<uint8_t>(EnemyStatus::Active), 
  static_cast<uint8_t>(EnemyType::EnemyType4), ENEMY_MAXIMUM_X - 5, 4, -2, 2, static_cast<uint8_t>(MovementSequence::Sequence_3), static_cast<uint8_t>(EnemyStatus::Active), 
  static_cast<uint8_t>(EnemyType::EnemyType4), ENEMY_MAXIMUM_X - 5, 24, -2, 2, static_cast<uint8_t>(MovementSequence::Sequence_3), static_cast<uint8_t>(EnemyStatus::Active), 
};

const int8_t PROGMEM formation_27[] = {
  4,  
  static_cast<uint8_t>(EnemyType::EnemyType4), ENEMY_MINIMUM_X + 5, 4, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_3), static_cast<uint8_t>(EnemyStatus::Active), 
  static_cast<uint8_t>(EnemyType::EnemyType4), ENEMY_MINIMUM_X + 5, 24, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_3), static_cast<uint8_t>(EnemyStatus::Active), 
  static_cast<uint8_t>(EnemyType::EnemyType1), ENEMY_MAXIMUM_X - 5, 4, -2, 2, static_cast<uint8_t>(MovementSequence::Sequence_3), static_cast<uint8_t>(EnemyStatus::Active), 
  static_cast<uint8_t>(EnemyType::EnemyType1), ENEMY_MAXIMUM_X - 5, 24, -2, 2, static_cast<uint8_t>(MovementSequence::Sequence_3), static_cast<uint8_t>(EnemyStatus::Active), 
};


// --------------------------------------------------------------------------------------------------------------------------------------------
// Astronuat patterns

const int8_t PROGMEM formation_28[] = {
  1,  
  static_cast<uint8_t>(EnemyType::AstronautCaptured), ENEMY_MINIMUM_X + 23, 14, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_3), static_cast<uint8_t>(EnemyStatus::Active), 
};

const int8_t PROGMEM formation_29[] = {
  1,  
  static_cast<uint8_t>(EnemyType::AstronautCaptured), ENEMY_MINIMUM_X, 14, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_3), static_cast<uint8_t>(EnemyStatus::Active), 
};

const int8_t PROGMEM formation_30[] = {
  1,  
  static_cast<uint8_t>(EnemyType::AstronautCaptured), ENEMY_MINIMUM_X + 5, 4, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_3), static_cast<uint8_t>(EnemyStatus::Active), 
};






const int8_t PROGMEM formation_31[] = {
  2,  
  static_cast<uint8_t>(EnemyType::EnemyType2), ENEMY_MINIMUM_X + 5, 60, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_3), static_cast<uint8_t>(EnemyStatus::Spawn8), 
  static_cast<uint8_t>(EnemyType::EnemyType2), ENEMY_MINIMUM_X + 25, 80, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_3), static_cast<uint8_t>(EnemyStatus::Spawn8), 
};

#ifndef TEST_ASTRONAUT
// const int8_t *formations[] = { formation_00, formation_01, formation_02, formation_03, formation_04, formation_05, formation_06, formation_07, 
//                                formation_08, formation_09, formation_10, formation_11, formation_12, formation_13, formation_14, formation_15, 
//                                formation_16, formation_17, formation_18, formation_19, formation_20, formation_21, formation_22, formation_23, 
//                                formation_24, formation_25, formation_26, formation_27, formation_28, formation_29, formation_30 };
const int8_t *formations[] = { formation_31 };
#else
const int8_t *formations[] = { formation_29 };
#endif