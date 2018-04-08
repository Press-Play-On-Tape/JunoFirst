#include "src/utils/Arduboy2Ext.h"
#include "src/entity/Player.h"
#include "src/entity/Enemy.h"
#include "src/entity/Bullet.h"
#include "src/entity/Slot.h"
#include "src/entity/HighScore.h"
#include "src/images/Images.h"
#include "src/images/Fonts.h"
#include "src/utils/Enums.h"
#include "src/utils/Utils.h"
#include "src/utils/EEPROM_Utils.h"
#include "src/levels/Level.h"
#include "src/levels/Formations.h"

Arduboy2Ext arduboy;
GameState gameState = GameState::Intro;

uint8_t introDelay = 0;
uint8_t alternate = 0;
uint8_t horizonIncrement = 0;
uint8_t bulletFrequency = 60;


Player player;
Bullet playerBullet;
Enemy enemies[MAX_NUMBER_OF_ENEMIES];
Bullet bullets[MAX_NUMBER_OF_BULLETS];
Level level;



HighScore highScore;




// --------------------------------------------------------------------------------------
//  Setup ..
//
void setup() {

  arduboy.boot();
  arduboy.flashlight();
  arduboy.systemButtons();
  arduboy.setFrameRate(60);
  arduboy.initRandomSeed();

  EEPROM_Utils::initEEPROM();

}


// --------------------------------------------------------------------------------------
//  Main Loop ..
//
void loop() {

  if (!(arduboy.nextFrame())) return;
  arduboy.pollButtons();

  switch (gameState) {

    case GameState::Intro:
      Intro();
      break;

    case GameState::ScoreTable:
      ScoreTable();
      player.reset();
      break;

    case GameState::GamePlay:
      Play();
      break;

    case GameState::GameOver:
      GameOver();
      break;

    case GameState::SaveScore:
      highScore.reset();
      highScore.setSlotNumber(EEPROM_Utils::saveScore(level.getScore(), level.getWave()));
      gameState = GameState::HighScore;
      // break; Fall-through intentional.

    case GameState::HighScore:
      HighScore();
      break;

    default: break;

  }
  
  arduboy.display(CLEAR_BUFFER);

}



// --------------------------------------------------------------------------------------
//  Show introduction screen ..
//
void Intro() {


  // Draw logo ..

  Sprites::drawOverwrite(18, 4, logo, 0);


  // Display 'Press A' button after a short period of time ..

  if (introDelay < INTRO_DELAY) {
    introDelay++;
  }
  else {    
    Sprites::drawOverwrite(51, 55, pressA, 0);
  }


  // If 'A' bUtton is pressed move to game play ..

  if (arduboy.justPressed(A_BUTTON)) { 

    player.reset();  
    gameState = GameState::ScoreTable; 
    introDelay = 0;
    
  }

}


// --------------------------------------------------------------------------------------
//  Let's play!
//
void Play() {


  // Update the ground's position ..

  const uint8_t speedLookup[] = {0, 16, 8, 0, 4};
  uint8_t speed = speedLookup[absT(player.getYDelta())];

  player.incHealth();

  if (horizonIncrement == speed) {

    level.incHorizon( player.getYDelta() > 0 ? 1 : -1);
    horizonIncrement = 0;
 

    // Update the enemies and bullets relative to the player position ..

    for (uint8_t x = 0; x < MAX_NUMBER_OF_ENEMIES; x++) {

      Enemy *enemy = &enemies[x];

      if (enemy->getStatus() == EnemyStatus::Active) {
        enemy->move(&player);
      }    

    }

    for (uint8_t x = 0; x < MAX_NUMBER_OF_BULLETS; x++) {

      Bullet *bullet = &bullets[x];

      if (bullet->getY() > 0) {

        bullet->move(&player);

      }

    }
    
  }
  
  horizonIncrement++;


  if (arduboy.everyXFrames(4)) {

    for (uint8_t x = 0; x < MAX_NUMBER_OF_ENEMIES; x++) {

      Enemy *enemy = &enemies[x];

      if (enemy->getStatus() == EnemyStatus::Active) {
        enemy->move();
      }    

    }

  }


  RenderScreen(&player, enemies);


  // Handle players actions ..

  if (arduboy.pressed(DOWN_BUTTON))     { if (player.decYDelta()) horizonIncrement = 0; }
  if (arduboy.pressed(UP_BUTTON))       { if (player.incYDelta()) horizonIncrement = 0; }
  if (arduboy.pressed(LEFT_BUTTON))     { player.decX(); }
  if (arduboy.pressed(RIGHT_BUTTON))    { player.incX(); }

  if (arduboy.justPressed(A_BUTTON))        { 

    if (playerBullet.getY() == 0) {

      playerBullet.setY(45);
      playerBullet.setX(player.getX() + 7);

    }

  }

  if (!arduboy.pressed(DOWN_BUTTON) && !arduboy.pressed(UP_BUTTON) && arduboy.everyXFrames(32)) { player.decelerate(); }


  // Update player bullet position ..

  if (arduboy.everyXFrames(2)) {

      uint8_t bulletY = playerBullet.getY();
      playerBullet.setY(bulletY > 10 ? bulletY - 5 : 0);

  }

  if (arduboy.everyXFrames(2)) {

    for (uint8_t x = 0; x < MAX_NUMBER_OF_BULLETS; x++) {

      Bullet *bullet = &bullets[x];

      if (bullet->getY() > 0) {

        bullet->move();

      }

    }

  }


  // Did our bullet hit an enemy or bullet?

  if (playerBullet.getY() > 0) {

    Rect bulletRect = { playerBullet.getX() - 1, playerBullet.getY() - 5, 3, 5 };

    for (uint8_t x = 0; x < MAX_NUMBER_OF_ENEMIES; x++) {

      Enemy *enemy = &enemies[x];

      if (enemy->getStatus() == EnemyStatus::Active) {

        Rect enemyRect = { enemy->getXDisplay(), enemy->getYDisplay(), enemy->getWidth(), enemy->getHeight() };

        if (arduboy.collide(bulletRect, enemyRect)) {

          enemy->setStatus(EnemyStatus::Explosion4);
          uint16_t scoreInc = 0;

          switch (enemy->getType()) {

            case EnemyType::EnemyType1:
              scoreInc = 150;
              break;

            case EnemyType::EnemyType2:
              scoreInc = 300;
              break;

            case EnemyType::EnemyType3:
              scoreInc = 450;
              break;

            case EnemyType::EnemyType4:
              scoreInc = 600;
              break;

          }

          level.setScore(level.getScore() + scoreInc);

        }

      }    

    }

    for (uint8_t x = 0; x < MAX_NUMBER_OF_BULLETS; x++) {

      Bullet *bullet = &bullets[x];

      if (bullet->getY() > 0) {

        Rect eneymBulletRect = { bullet->getX(), bullet->getY(), 2, 2 };

        if (arduboy.collide(bulletRect, eneymBulletRect)) {

          bullet->setY(0);
          Sprites::drawSelfMasked(bullet->getX() - 2, bullet->getY() - 2, alien_far, 0);
          //TODO: Sound when two bullets hit

        }

      }

    }

  }


  // Did any enemy bullet hit us ..

  for (uint8_t x = 0; x < MAX_NUMBER_OF_BULLETS; x++) {

    Bullet *bullet = &bullets[x];

    if (bullet->getY() > 0) {

      Rect bulletRect = { bullet->getX(), bullet->getY(), 2, 2 };
      Rect playerRect = { player.getX() + 1, player.getY() + 1, 13, 14 };

      if (arduboy.collide(bulletRect, playerRect)) {

        uint8_t health = player.getHealth();
        bullet->setY(0);

        if (health > 0) {

          player.setHealth(--health);

        }
        else {

          player.setStatus(PlayerStatus::Explosion4);

        }

      }

    }

  }


  // Update dying enemy images ..

  if (arduboy.everyXFrames(8)) {

    for (uint8_t x = 0; x < MAX_NUMBER_OF_ENEMIES; x++) {

      Enemy *enemy = &enemies[x];
      EnemyStatus enemyStatus = enemy->getStatus();

      if (enemyStatus > EnemyStatus::Dead && enemyStatus < EnemyStatus::Active) {

        enemy->setStatus(--enemyStatus);

      }    

    }

  }


  // Update dying player image ..

  if (arduboy.everyXFrames(8)) {

    PlayerStatus status = player.getStatus();

    if (status > PlayerStatus::Dead && status < PlayerStatus::Active) {

      player.setStatus(--status);

      if (status == PlayerStatus::Dead) {

        gameState = GameState::GameOver;

      }

    }

  }


  // Enemy takes a shot? 

  if (random(0, bulletFrequency) == 0) {

    bool bulletLaunched = false;

    for (uint8_t x = 0; x < MAX_NUMBER_OF_BULLETS; x++) {

      Bullet *bullet = &bullets[x];

      if (bullet->getY() == 0) { 
        
        uint8_t y = random(0, MAX_NUMBER_OF_ENEMIES);

        for (uint8_t x = 0; x < MAX_NUMBER_OF_ENEMIES; x++) {
          
          uint8_t x2 = (x + y) % MAX_NUMBER_OF_ENEMIES;

          Enemy *enemy = &enemies[x2];
          EnemyStatus enemyStatus = enemy->getStatus();

          if (enemyStatus == EnemyStatus::Active && enemy->inShootingRange()) {

            uint8_t enemyMiddle = enemy->getXDisplay() + (enemy->getWidth() / 2);

            bullet->setX(enemyMiddle);
            bullet->setY(enemy->getYDisplay() + enemy->getHeight());
            bullet->setYDelta(enemy->getYDelta() + 1);

            switch ((player.getX() + 7 - enemyMiddle) / (player.getY() - enemy->getYDisplay())) {

              case -999 ... -1:
                bullet->setXDelta(-1);
                break;

              case 0:
                bullet->setXDelta(0);
                break;

              case 1 ... 999:
                bullet->setXDelta(1);
                break;

            }

            bulletLaunched = true;
            break;

          }

        }

      }

      if (bulletLaunched) break;

    }

  }

}



void launchFormation(uint8_t formationNumber) {

  uint16_t dataOffset = 0;
  const int8_t *formationToLoad = formations[formationNumber];

  uint8_t numberOfEnemies = pgm_read_byte(&formationToLoad[dataOffset++]);

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

}




void HighScore() {

  uint8_t xOffset = 28;
  uint8_t yOffset = 20;

  for (uint8_t x =0; x < MAX_NUMBER_OF_SCORES; x++) {


    Slot slot;
    EEPROM_Utils::getSlot(x, &slot);

    Sprites::drawOverwrite(xOffset, yOffset, font, slot.getChar0());
    Sprites::drawOverwrite(xOffset + 5, yOffset, font, slot.getChar1());
    Sprites::drawOverwrite(xOffset + 10, yOffset, font, slot.getChar2());


    // Score ..
    {
      uint8_t digits[6] = {};
      extractDigits(digits, slot.getScore());
      
      for (uint8_t i = 0, x2 = xOffset + 49; i < 6; ++i, x2 -= 5) {
        Sprites::drawOverwrite(x2, yOffset, numbers, digits[i]);
      }
      
    }


    // Wave ..
    
    Sprites::drawOverwrite(xOffset + 65, yOffset, numbers, slot.getWave() / 10);
    Sprites::drawOverwrite(xOffset + 70, yOffset, numbers, slot.getWave() % 10);

    yOffset = yOffset + 8;

  }


  if (highScore.getSlotNumber() != DO_NOT_EDIT_SLOT) {

    yOffset = 20;
    alternate++;
  
    if (alternate < 40) {

      Sprites::drawOverwrite(xOffset - 6, yOffset + (highScore.getSlotNumber() * 8), arrowLeft, 0);
      Sprites::drawOverwrite(xOffset + 77, yOffset + (highScore.getSlotNumber() * 8), arrowRight, 0);
    
    }
    else if (alternate > 80) {

      alternate = 0;

    }

    if (highScore.getCharIndex() == 0) {
      arduboy.fillRect(xOffset - 1, yOffset + (highScore.getSlotNumber() * 8) - 1, 5, 7, WHITE);
      Sprites::drawErase(xOffset, yOffset + (highScore.getSlotNumber() * 8), font, highScore.getChar(0));
    }
    else {
      Sprites::drawOverwrite(xOffset, yOffset + (highScore.getSlotNumber() * 8), font, highScore.getChar(0));
    }

    if (highScore.getCharIndex() == 1) {
      arduboy.fillRect(xOffset + 4, yOffset + (highScore.getSlotNumber() * 8) - 1, 5, 7, WHITE);
      Sprites::drawErase(xOffset + 5, yOffset + (highScore.getSlotNumber() * 8), font, highScore.getChar(1));
    }
    else {
      Sprites::drawOverwrite(xOffset + 5, yOffset + (highScore.getSlotNumber() * 8), font, highScore.getChar(1));
    }

    if (highScore.getCharIndex() == 2) {
      arduboy.fillRect(xOffset + 9, yOffset + (highScore.getSlotNumber() * 8) - 1, 5, 7, WHITE);
      Sprites::drawErase(xOffset + 10, yOffset + (highScore.getSlotNumber() * 8), font, highScore.getChar(2));
    }
    else {
      Sprites::drawOverwrite(xOffset + 10, yOffset + (highScore.getSlotNumber() * 8), font, highScore.getChar(2));
    }


    // Handle buttons ..

    uint8_t charIndex = highScore.getCharIndex();

    if (arduboy.justPressed(UP_BUTTON))       { highScore.incChar(charIndex); }
    if (arduboy.justPressed(DOWN_BUTTON))     { highScore.decChar(charIndex); }
    if (arduboy.justPressed(LEFT_BUTTON))     { highScore.decCharIndex(); } 
    if (arduboy.justPressed(RIGHT_BUTTON))    { highScore.incCharIndex(); } 

    if (arduboy.justPressed(A_BUTTON)) { 
      
      EEPROM_Utils::writeChars(highScore.getSlotNumber(), &highScore);
      highScore.disableEditting(); 
      
    }

  }

}