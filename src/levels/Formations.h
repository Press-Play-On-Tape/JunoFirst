#pragma once

#include "../utils/Enums.h"


// A block of four enemies, travelling in formation.
const int8_t PROGMEM formation_00[] = {
  4,                                                        // Number of enemies

  static_cast<uint8_t>(EnemyType::EnemyType1),              // Enemy type
  0, 54,                                      // starting position
  2, 2,                                                   // starting deltas (-10)
  static_cast<uint8_t>(MovementSequence::Sequence_1),       

  static_cast<uint8_t>(EnemyType::EnemyType1), 
  ENEMY_MINIMUM_X + 23, 14,  
  2, 2,                                      
  static_cast<uint8_t>(MovementSequence::Sequence_1),       

  static_cast<uint8_t>(EnemyType::EnemyType1), 
  ENEMY_MINIMUM_X, 24,                         
  2, 2,                                      
  static_cast<uint8_t>(MovementSequence::Sequence_1),       

  static_cast<uint8_t>(EnemyType::EnemyType1),             
  ENEMY_MINIMUM_X + 23, 24,                              
  2, 2,                                                   
  static_cast<uint8_t>(MovementSequence::Sequence_1),       

};

// Four enemies - two travelling left, two right.  
const int8_t PROGMEM formation_01[] = {
  4,                                                        

  static_cast<uint8_t>(EnemyType::EnemyType1),              
  ENEMY_MINIMUM_X, 14,                                                    
  2, 2,                                                   
  static_cast<uint8_t>(MovementSequence::Sequence_1),       

  static_cast<uint8_t>(EnemyType::EnemyType1),              
  ENEMY_MINIMUM_X + 23, 14,                                                   
  2, 2,                                                   
  static_cast<uint8_t>(MovementSequence::Sequence_1),       

  static_cast<uint8_t>(EnemyType::EnemyType1),              
  ENEMY_MAXIMUM_X, 24,                                                    
  -3, 2,                                                    
  static_cast<uint8_t>(MovementSequence::Sequence_1),       

  static_cast<uint8_t>(EnemyType::EnemyType1),              
  ENEMY_MAXIMUM_X + 23, 24,                                                   
  -3, 2,                                                    
  static_cast<uint8_t>(MovementSequence::Sequence_1),       

};


// Two enemies - travelling diagonally from top left to bottom right.  
const int8_t PROGMEM formation_02[] = {
  2,                                                        

  static_cast<uint8_t>(EnemyType::EnemyType1),              
  ENEMY_MINIMUM_X, 14,                                                    
  2, 2,                                                   
  static_cast<uint8_t>(MovementSequence::Sequence_2),       

  static_cast<uint8_t>(EnemyType::EnemyType1),              
  ENEMY_MINIMUM_X + 23, 14,                                                   
  2, 2,                                                   
  static_cast<uint8_t>(MovementSequence::Sequence_2),       

};


// Two enemies - travelling diagonally from top right to bottom left.  
const int8_t PROGMEM formation_03[] = {
  2,                                                        

  static_cast<uint8_t>(EnemyType::EnemyType1),              
  ENEMY_MINIMUM_X, 14,                                                    
  2, 2,                                                   
  static_cast<uint8_t>(MovementSequence::Sequence_2),       

  static_cast<uint8_t>(EnemyType::EnemyType1),              
  ENEMY_MINIMUM_X + 23, 14,                                                   
  2, 2,                                                   
  static_cast<uint8_t>(MovementSequence::Sequence_2),       

};



// One enemy - travelling diagonally from top left to bottom right.  
const int8_t PROGMEM formation_04[] = {
  1,                                                        

  static_cast<uint8_t>(EnemyType::EnemyType1),              
  ENEMY_MINIMUM_X, 14,                                                    
  2, 2,                                                   
  static_cast<uint8_t>(MovementSequence::Sequence_2),       
     

};

const int8_t *formations[] =    { formation_00, formation_01, formation_02, formation_03, formation_04 };