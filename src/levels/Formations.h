#pragma once

#include "../utils/Enums.h"


// A block of four enemies, travelling in formation.
const uint8_t PROGMEM formation_00[] = {
  4,                                                        // Number of enemies

  static_cast<uint8_t>(EnemyType::EnemyType1),              // Enemy type
  1, 14,                                                    // starting position
  2, 2,                                                     // starting deltas
  static_cast<uint8_t>(MovementSequence::Sequence_1),       

  static_cast<uint8_t>(EnemyType::EnemyType1),              // Enemy type
  24, 14,                                                   // starting position
  2, 2,                                                     // starting deltas
  static_cast<uint8_t>(MovementSequence::Sequence_1),       

  static_cast<uint8_t>(EnemyType::EnemyType1),              // Enemy type
  1, 24,                                                    // starting position
  2, 2,                                                     // starting deltas
  static_cast<uint8_t>(MovementSequence::Sequence_1),       

  static_cast<uint8_t>(EnemyType::EnemyType1),              // Enemy type
  24, 24,                                                   // starting position
  2, 2,                                                     // starting deltas
  static_cast<uint8_t>(MovementSequence::Sequence_1),       

};

// Four enemies - two travelling left, two right.  
const uint8_t PROGMEM formation_01[] = {
  4,                                                        // Number of enemies

  static_cast<uint8_t>(EnemyType::EnemyType1),              // Enemy type
  1, 14,                                                    // starting position
  2, 2,                                                     // starting deltas
  static_cast<uint8_t>(MovementSequence::Sequence_1),       

  static_cast<uint8_t>(EnemyType::EnemyType1),              // Enemy type
  24, 14,                                                   // starting position
  2, 2,                                                     // starting deltas
  static_cast<uint8_t>(MovementSequence::Sequence_1),       

  static_cast<uint8_t>(EnemyType::EnemyType1),              // Enemy type
  0, 24,                                                    // starting position
  -3, 2,                                                     // starting deltas
  static_cast<uint8_t>(MovementSequence::Sequence_1),       

  static_cast<uint8_t>(EnemyType::EnemyType1),              // Enemy type
  23, 24,                                                   // starting position
  -3, 2,                                                     // starting deltas
  static_cast<uint8_t>(MovementSequence::Sequence_1),       



};


const uint8_t *formations[] =    { formation_00, formation_01 };