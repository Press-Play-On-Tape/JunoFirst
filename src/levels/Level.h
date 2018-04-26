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
    uint32_t getScore();
    uint16_t getCountDown();
    uint8_t getInPlay();      // Enemies in play.
    bool getAstronautBeenLaunched();    

    void setHorizon(int8_t val);
    void setWave(uint8_t val);
    void setScore(uint32_t val);
    void setCountDown(uint16_t val);
    void setInPlay(uint8_t val);
    void setDoubleUpPoints(uint16_t val);
    void setAstronautBeenLaunched(bool val);


    // Methods ..

    void incHorizon(int8_t val);
    void decCountDown();
    void incInPlay();
    void decInPlay();
    void incWave();
    void incEnemiesLaunched();
    void resetGame(Enemy *enemies, Bullet *bullets, Bullet *playerBullet);
    void resetWave(Enemy *enemies, Bullet *bullets, Bullet *playerBullet);

    uint8_t launchFormation(Enemy *enemies, uint8_t formationNumber);
    uint8_t getFrameRate();
    uint8_t getEnemiesInWave();
    uint8_t getEnemiesLaunchedThisWave();
    uint8_t getBulletFrequency();

    void decDoubleUpPoints();
    bool inDoubleUpPhase();
    bool hasAstronautBeenLaunched();

  private:

    int8_t _horizon;
    uint8_t _wave;
    uint32_t _score;
    uint8_t _inPlay;
    uint16_t _countDown;
    uint8_t _frameRate;
    uint8_t _enemiesInWave;
    uint8_t _enemiesLaunchedThisWave;
    uint16_t _doubleUpPoints = 0;
    bool _hasAstronautBeenLaunched;

};


//--------------------------------------------------------------------------------------------------------------------------
// Properties ..


int8_t Level::getHorizon() {
  return _horizon;
}

uint8_t Level::getWave() {
  return _wave;
}

uint32_t Level::getScore() {
  return _score;
}

uint16_t Level::getCountDown() {
  return _countDown;
}

uint8_t Level::getInPlay() {
  return _inPlay;
}

bool Level::getAstronautBeenLaunched() {
  return _hasAstronautBeenLaunched;
}

void Level::setHorizon(int8_t val) {
  _horizon = val;
}

void Level::setWave(uint8_t val) {
  _wave = val;
}

void Level::setScore(uint32_t val) {
  _score = val;
}

void Level::setCountDown(uint16_t val) {
  _countDown = val;
}

void Level::setInPlay(uint8_t val) {
  _inPlay = val;
}

void Level::setDoubleUpPoints(uint16_t val) {
  _doubleUpPoints = val;
}

void Level::setAstronautBeenLaunched(bool val) {
  _hasAstronautBeenLaunched = val;
}


//--------------------------------------------------------------------------------------------------------------------------
// Methods ..

void Level::incHorizon(int8_t val) {

  _horizon = (_horizon + val) % HORIZON_ROW_COUNT;
  if (_horizon < 0) _horizon = _horizon + HORIZON_ROW_COUNT;

}

void Level::resetGame(Enemy *enemies, Bullet *bullets, Bullet *playerBullet) {

  resetWave(enemies, bullets, playerBullet);

  _wave = 01;
  _score = 0;

}

void Level::resetWave(Enemy *enemies, Bullet *bullets, Bullet *playerBullet) {

  for (uint8_t x = 0; x < MAX_NUMBER_OF_ENEMIES; x++) {

    Enemy *enemy = &enemies[x];
    enemy->setStatus(EnemyStatus::Dead);
    enemy->setProtection(0);

  }

  for (uint8_t x = 0; x < MAX_NUMBER_OF_BULLETS; x++) {

    Bullet *bullet = &bullets[x];
    bullet->setY(0);

  }

  playerBullet->setY(0);
  _inPlay = 0;
  _horizon = 2;
  _enemiesLaunchedThisWave = 0;
  _doubleUpPoints = 0;
  _hasAstronautBeenLaunched = false;

}

void Level::decCountDown() {

  if (_countDown > 0) _countDown--;
 
}

void Level::decInPlay() {

  _inPlay--;

}

void Level::incInPlay() {

  _inPlay++;

}

void Level::incWave() {

  _wave++;

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

        enemy->setType(static_cast<EnemyType>(pgm_read_byte(&formationToLoad[dataOffset++])));
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

  _countDown = clamp<uint8_t>((MAX_DELAY_BETWEEN_FORMATIONS - (_wave * LEVEL_DELAY_BETWEEN_FORMATIONS)), MIN_DELAY_BETWEEN_FORMATIONS, MAX_DELAY_BETWEEN_FORMATIONS);
  _enemiesLaunchedThisWave = _enemiesLaunchedThisWave + numberOfEnemies;

  return numberOfEnemies;

}

uint8_t Level::getFrameRate() {

  return DEFAULT_FRAME_RATE + ((_wave - 1) * NEW_WAVE_FRAME_RATE_INC);

}

uint8_t Level::getEnemiesInWave() {

  return ENEMIES_IN_FIRST_WAVE + ((_wave - 1) * ADDITIONAL_ENEMIES_PER_WAVE);

}

uint8_t Level::getEnemiesLaunchedThisWave() {

  return _enemiesLaunchedThisWave;

}

uint8_t Level::getBulletFrequency() {

  return INITIAL_BULLET_FREQUENCY + ((_wave - 1) * BULLETS_DECREASE_PER_WAVE);

}

void Level::incEnemiesLaunched() {

  _enemiesLaunchedThisWave++;

}

bool Level::inDoubleUpPhase() {

  return _doubleUpPoints > 0;

}

void Level::decDoubleUpPoints() {
 
  if (_doubleUpPoints > 0) _doubleUpPoints--;

}

bool Level::hasAstronautBeenLaunched() {

  return _hasAstronautBeenLaunched;

}
