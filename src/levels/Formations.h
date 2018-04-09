#pragma once

#include "../utils/Enums.h"

static const uint8_t NUMBER_OF_FORMATIONS_WITHOUT_ASTRONAUT  = 6;
static const uint8_t MAX_DELAY_BETWEEN_FORMATIONS = 140;
static const uint8_t MIN_DELAY_BETWEEN_FORMATIONS = MAX_DELAY_BETWEEN_FORMATIONS / 2;
static const uint8_t LEVEL_DELAY_BETWEEN_FORMATIONS = (MAX_DELAY_BETWEEN_FORMATIONS / 10);


// A block of four enemies, travelling in formation.
const int8_t PROGMEM formation_00[] = {
  4,  
  static_cast<uint8_t>(EnemyType::EnemyType1), ENEMY_MINIMUM_X, 14, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_1), 
  static_cast<uint8_t>(EnemyType::EnemyType1), ENEMY_MINIMUM_X + 23, 14, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_1), 
  static_cast<uint8_t>(EnemyType::EnemyType3), ENEMY_MINIMUM_X, 24, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_1), 
  static_cast<uint8_t>(EnemyType::EnemyType3), ENEMY_MINIMUM_X + 23, 24, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_1), 
};

// A block of four enemies, travelling in formation.
const int8_t PROGMEM formation_01[] = {
  4,  
  static_cast<uint8_t>(EnemyType::EnemyType2), ENEMY_MINIMUM_X, 14, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_1), 
  static_cast<uint8_t>(EnemyType::EnemyType2), ENEMY_MINIMUM_X + 23, 14, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_1), 
  static_cast<uint8_t>(EnemyType::EnemyType4), ENEMY_MINIMUM_X, 24, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_1), 
  static_cast<uint8_t>(EnemyType::EnemyType4), ENEMY_MINIMUM_X + 23, 24, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_1), 
};

// Four enemies - two travelling left, two right.  
const int8_t PROGMEM formation_02[] = {
  4,  
  static_cast<uint8_t>(EnemyType::EnemyType3), ENEMY_MINIMUM_X, 14, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_1), 
  static_cast<uint8_t>(EnemyType::EnemyType3), ENEMY_MINIMUM_X + 23, 14, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_1), 
  static_cast<uint8_t>(EnemyType::EnemyType1), ENEMY_MAXIMUM_X, 24, -3, 2, static_cast<uint8_t>(MovementSequence::Sequence_1), 
  static_cast<uint8_t>(EnemyType::EnemyType1), ENEMY_MAXIMUM_X + 23, 24, -3, 2, static_cast<uint8_t>(MovementSequence::Sequence_1), 
};


// Two enemies - travelling diagonally from top left to bottom right.  
const int8_t PROGMEM formation_03[] = {
  2,  
  static_cast<uint8_t>(EnemyType::EnemyType1), ENEMY_MINIMUM_X, 14, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_2), 
  static_cast<uint8_t>(EnemyType::EnemyType1), ENEMY_MINIMUM_X + 23, 14, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_2), 
};


// Two enemies - travelling diagonally from top right to bottom left.  
const int8_t PROGMEM formation_04[] = {
  2,  
  static_cast<uint8_t>(EnemyType::EnemyType1), ENEMY_MAXIMUM_X - 23, 14, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_2), 
  static_cast<uint8_t>(EnemyType::EnemyType1), ENEMY_MINIMUM_X, 14, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_2), 
};

// Four enemy - X pattern
const int8_t PROGMEM formation_05[] = {
  4,  
  static_cast<uint8_t>(EnemyType::EnemyType1), ENEMY_MINIMUM_X + 5, 4, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_2), 
  static_cast<uint8_t>(EnemyType::EnemyType1), ENEMY_MINIMUM_X + 5, 24, 2, 2, static_cast<uint8_t>(MovementSequence::Sequence_2), 
  static_cast<uint8_t>(EnemyType::EnemyType1), ENEMY_MAXIMUM_X - 5, 4, -2, 2, static_cast<uint8_t>(MovementSequence::Sequence_2), 
  static_cast<uint8_t>(EnemyType::EnemyType1), ENEMY_MAXIMUM_X - 5, 24, -2, 2, static_cast<uint8_t>(MovementSequence::Sequence_2), 
};

const int8_t *formations[] = { formation_00, formation_01, formation_02, formation_03, formation_04, formation_05 };