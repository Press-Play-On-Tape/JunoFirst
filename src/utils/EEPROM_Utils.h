#pragma once

#include "Arduboy2Ext.h"
#include "Enums.h"
#include "Slot.h"

#define EEPROM_START                  EEPROM_STORAGE_SPACE_START + 300
#define EEPROM_START_C1               EEPROM_START
#define EEPROM_START_C2               EEPROM_START + 1
#define EEPROM_TOP_START              EEPROM_START + 2
#define EEPROM_ENTRY_SIZE             6

class EEPROM_Utils {

  public: 

    EEPROM_Utils(){};
        
    static void initEEPROM();
    static void getSlot(uint8_t x, Slot *slot);
    static uint8_t saveScore(uint16_t score, uint8_t wave);
    static void writeChar(uint8_t slotIndex, uint8_t charIndex, uint8_t letterIndex);

};


/* ----------------------------------------------------------------------------
 *   Is the EEPROM initialised?
 *
 *   Looks for the characters 'J' and 'F' in the first two bytes of the EEPROM
 *   memory range starting from byte EEPROM_STORAGE_SPACE_START.  If not found,
 *   it resets the settings ..
 */

const uint8_t letter1 = 74; // 74
const uint8_t letter2 = 70; // 70

void EEPROM_Utils::initEEPROM() {

  byte c1 = EEPROM.read(EEPROM_START_C1);
  byte c2 = EEPROM.read(EEPROM_START_C2);

  if (c1 != letter1 || c2 != letter2) { // JF 74 70

    uint16_t score = 0;
    EEPROM.update(EEPROM_START_C1, letter1);
    EEPROM.update(EEPROM_START_C2, letter2);

    for (uint8_t x = 0; x < MAX_NUMBER_OF_SCORES; x++) {

      EEPROM.update(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * x), 0);
      EEPROM.update(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * x) + 1, 0);
      EEPROM.update(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * x) + 2, 0);
      EEPROM.update(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * x) + 3, 0);

      score = (MAX_NUMBER_OF_SCORES - x) * 1000;
      EEPROM.put(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * x) + 4, score);

    }

  }

}


/* -----------------------------------------------------------------------------
 *   Get slot details. 
 */
void EEPROM_Utils::getSlot(uint8_t x, Slot *slot) {

  slot->char0 = EEPROM.read(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * x));
  slot->char1 = EEPROM.read(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * x) + 1);
  slot->char2 = EEPROM.read(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * x) + 2);
  slot->wave = EEPROM.read(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * x) + 3);

  uint16_t score = 0;
  EEPROM.get(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * x) + 4, score);
  slot->score = score;

}


/* -----------------------------------------------------------------------------
 *   Save score and return index.  255 not good enough! 
 */
uint8_t EEPROM_Utils::saveScore(uint16_t score, uint8_t wave) {

  uint8_t idx = DO_NOT_EDIT_SLOT;

  for (uint8_t x = 0; x < MAX_NUMBER_OF_SCORES; x++) {

    uint16_t slotScore = 0;
    EEPROM.get(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * x) + 4, slotScore);

    if (slotScore < score) {

      idx = x;
      break;

    }

  }

  if (idx < 255) {

    for (uint8_t x = MAX_NUMBER_OF_SCORES - 1; x > idx; x--) {

      Slot slot;
      getSlot(x - 1, &slot);

      EEPROM.update(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * x), slot.char0);
      EEPROM.update(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * x) + 1, slot.char1);
      EEPROM.update(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * x) + 2, slot.char2);
      EEPROM.update(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * x) + 3, slot.wave);
      EEPROM.put(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * x) + 4, slot.score);

    }

    EEPROM.update(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * idx), 0);
    EEPROM.update(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * idx) + 1, 0);
    EEPROM.update(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * idx) + 2, 0);
    EEPROM.update(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * idx) + 3, wave);
    EEPROM.put(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * idx) + 4, score);
    

  }

  return idx;

}


/* -----------------------------------------------------------------------------
 *   Save score and return index.  255 not good enough! 
 */
static void EEPROM_Utils::writeChar(uint8_t slotIndex, uint8_t charIndex, uint8_t letterIndex) {

    EEPROM.update(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * slotIndex) + charIndex, letterIndex);

}
