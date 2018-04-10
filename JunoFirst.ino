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
#include "src/utils/FadeEffects.h"

Arduboy2Ext arduboy;
GameState gameState = GameState::Intro_Init;

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
FadeInEffect fadeInEffect;



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

    case GameState::Intro_Init:
      fadeInEffect.reset();
      gameState = GameState::Intro;
      // break; Fall-through intentional.

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

    case GameState::GameOver_Init:
      gameState = GameState::GameOver;
      fadeInEffect.reset();
      // break; Fall-through intentional.

    case GameState::GameOver:
      GameOver();
      break;

    case GameState::SaveScore:
      highScore.reset();
      highScore.setSlotNumber(EEPROM_Utils::saveScore(level.getScore(), level.getWave()));
      gameState = GameState::HighScore;
      fadeInEffect.reset();
      // break; Fall-through intentional.

    case GameState::HighScore:
      HighScore();
      break;

    case GameState::Credits:
      Credits();
      break;

    default: break;

  }
  
  arduboy.display(CLEAR_BUFFER);

}


// --------------------------------------------------------------------------------------
//  Let's play!
//
void Play() {


  // Update the ground's position ..

//  const uint8_t speedLookup[] = {0, 16, 8, 0, 4};
//  const uint8_t speedLookup[] = {0, 8, 4, 0, 2};
  const uint8_t speedLookup[] = {0, 12, 6, 0, 3};
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


  if (arduboy.everyXFrames(FRAME_RATE_2)) {

    for (uint8_t x = 0; x < MAX_NUMBER_OF_ENEMIES; x++) {

      Enemy *enemy = &enemies[x];

      if (enemy->getStatus() == EnemyStatus::Active) {
        enemy->move();
      }    

    }

  }

  RenderScreen(&player, enemies);
 

  // Handle players actions ..

  if (player.getStatus() == PlayerStatus::Active) {

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

    if (!arduboy.pressed(DOWN_BUTTON) && !arduboy.pressed(UP_BUTTON) && arduboy.everyXFrames(FRAME_RATE_16)) { player.decelerate(); }

  }


  // Update player bullet position ..

  uint8_t bulletY = playerBullet.getY();
  playerBullet.setY(bulletY > 10 ? bulletY - 5 : 0);

  for (uint8_t x = 0; x < MAX_NUMBER_OF_BULLETS; x++) {

    Bullet *bullet = &bullets[x];

    if (bullet->getY() > 0) {

      bullet->move();

    }

  }


  // Did our bullet hit an enemy or enemy bullet?

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
          level.decInPlay();

          //TDOD sound when enemy shot.

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


  // Did any enemy hit us ..

  if (player.getStatus() == PlayerStatus::Active) {

    Rect playerRect = { player.getX() + 1, player.getY() + 1, 13, 14 };

    for (uint8_t x = 0; x < MAX_NUMBER_OF_ENEMIES; x++) {

      Enemy *enemy = &enemies[x];

      if (enemy->getStatus() == EnemyStatus::Active) {

        Rect enemyRect = { enemy->getXDisplay(), enemy->getYDisplay(), enemy->getWidth(), enemy->getHeight() };

        if (arduboy.collide(enemyRect, playerRect)) {

          if (!enemy->getPlayerOverlap()) {

            enemy->setPlayerOverlap(true);
            uint8_t health = player.getHealth();

            if (health > 0) {

              player.setHealth(--health);

            }
            else {

              player.setStatus(PlayerStatus::Explosion4);

            }

          }

        }
        else {

          enemy->setPlayerOverlap(false);

        }

      }

    }

  }



  // Did any enemy bullet hit us ..

  if (player.getStatus() == PlayerStatus::Active) {

    Rect playerRect = { player.getX() + 1, player.getY() + 1, 13, 14 };

    for (uint8_t x = 0; x < MAX_NUMBER_OF_BULLETS; x++) {

      Bullet *bullet = &bullets[x];

      if (bullet->getY() > 0) {

        Rect bulletRect = { bullet->getX(), bullet->getY(), 2, 2 };

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

  }


  // Update dying enemy images ..

  if (arduboy.everyXFrames(FRAME_RATE_4)) {

    for (uint8_t x = 0; x < MAX_NUMBER_OF_ENEMIES; x++) {

      Enemy *enemy = &enemies[x];
      EnemyStatus enemyStatus = enemy->getStatus();

      if (enemyStatus > EnemyStatus::Dead && enemyStatus < EnemyStatus::Active) {

        enemy->setStatus(--enemyStatus);

      }    

    }


    // Update dying player image ..

    PlayerStatus status = player.getStatus();

    if (status > PlayerStatus::Dead && status < PlayerStatus::Active) {

      player.setStatus(--status);

      if (status == PlayerStatus::Dead) {

        gameState = GameState::GameOver_Init;

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
            bullet->setY(absT(enemy->getYDisplay() + enemy->getHeight()));
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


  // Launch a new formation ?

  level.decCountDown();

  if (level.getCountDown() == 0 && level.getInPlay() < MAX_NUMBER_OF_ENEMIES - MAX_NUMBER_OF_ENEMIES_PER_FORMATION) {
    level.launchFormation(enemies, random(0, NUMBER_OF_FORMATIONS_WITHOUT_ASTRONAUT));

    //TODO : sound formation launch
  }

}
