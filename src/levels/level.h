#pragma once

#include "../utils/Enums.h"
#include "Formations.h"
#include "../entity/Enemy.h"
#include "../entity/Bullet.h"

class Level {

  public: 

    Level() {};

  
    // Properties ..

    int8_t getHorizon();
    uint8_t getWave();
    uint16_t getScore();
    uint16_t getCountDown();
    uint8_t getInPlay();      // Enemies in play.

    void setHorizon(int8_t val);
    void setWave(uint8_t val);
    void setScore(uint16_t val);
    void setCountDown(uint16_t val);
    void setInPlay(uint8_t val);


    // Methods ..

    void incHorizon(int8_t val);
    void decCountDown();
    void decInPlay();
    void reset(Enemy *enemies, Bullet *bullets, Bullet *playerBullet);
    uint8_t launchFormation(Enemy *enemies, uint8_t formationNumber);

  private:

    int8_t _horizon;
    uint8_t _wave;
    uint16_t _score;
    uint8_t _inPlay;
    uint16_t _countDown;

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

uint16_t Level::getCountDown() {
  return _countDown;
}

uint8_t Level::getInPlay() {
  return _inPlay;
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

void Level::setCountDown(uint16_t val) {
  _countDown = val;
}

void Level::setInPlay(uint8_t val) {
  _inPlay = val;
}



//--------------------------------------------------------------------------------------------------------------------------
// Methods ..

void Level::incHorizon(int8_t val) {

  _horizon = (_horizon + val) % HORIZON_ROW_COUNT;
  if (_horizon < 0) _horizon = _horizon + HORIZON_ROW_COUNT;

}

void Level::reset(Enemy *enemies, Bullet *bullets, Bullet *playerBullet) {

  for (uint8_t x = 0; x < MAX_NUMBER_OF_ENEMIES; x++) {

    Enemy *enemy = &enemies[x];
    enemy->setStatus(EnemyStatus::Dead);

  }

  for (uint8_t x = 0; x < MAX_NUMBER_OF_BULLETS; x++) {

    Bullet *bullet = &bullets[x];
    bullet->setY(0);

  }

  playerBullet->setY(0);

  _wave = 01;
  _score = 0;

}

void Level::decCountDown() {

  if (_countDown > 0) _countDown--;
 
}

void Level::decInPlay() {

  _inPlay--;

}


// Returns number launched ..

uint8_t Level::launchFormation(Enemy *enemies, uint8_t formationNumber) {

  uint16_t dataOffset = 0;
  const int8_t *formationToLoad = formations[formationNumber];

  uint8_t numberOfEnemies = pgm_read_byte(&formationToLoad[dataOffset++]);
  _inPlay = _inPlay + numberOfEnemies;

  for (uint8_t x = 0; x < numberOfEnemies; x++) {

    for (uint8_t y = 0; y < MAX_NUMBER_OF_ENEMIES; y++) {

      Enemy *enemy = &enemies[y];

      if (enemy->getStatus() == EnemyStatus::Dead) {

        enemy->setEnemyType(static_cast<EnemyType>(pgm_read_byte(&formationToLoad[dataOffset++])));
        enemy->setX(static_cast<int8_t>(pgm_read_byte(&formationToLoad[dataOffset++])));
        enemy->setY(pgm_read_byte(&formationToLoad[dataOffset++]));
        enemy->setXDelta(static_cast<int8_t>(pgm_read_byte(&formationToLoad[dataOffset++])));
        enemy->setYDelta(static_cast<int8_t>(pgm_read_byte(&formationToLoad[dataOffset++])));
        enemy->setMovementSequence(static_cast<MovementSequence>(pgm_read_byte(&formationToLoad[dataOffset++])));
        enemy->setStatus(EnemyStatus::Active);
        break;

      }    

    }

  }

  _countDown =  clamp<uint8_t>((MAX_DELAY_BETWEEN_FORMATIONS - (_wave * LEVEL_DELAY_BETWEEN_FORMATIONS)), MIN_DELAY_BETWEEN_FORMATIONS, MAX_DELAY_BETWEEN_FORMATIONS);
  
  return numberOfEnemies;

}