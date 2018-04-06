#include "src/utils/Arduboy2Ext.h"
#include "src/characters/Player.h"
#include "src/characters/Enemy.h"
#include "src/characters/Bullet.h"
#include "src/images/Images.h"
#include "src/utils/Enums.h"
#include "src/utils/Utils.h"
#include "src/levels/Level.h"
#include "src/levels/Formations.h"

Arduboy2Ext arduboy;
GameState gameState = GameState::Intro;

uint8_t introDelay = 0;
uint8_t alternate = 0;
uint8_t yPos = 0;
uint8_t xPos = 60;
uint8_t horizonIncrement = 0;
uint16_t score = 0;

uint8_t bulletFrequency = 60;

Player player;
Bullet playerBullet;
Enemy enemies[MAX_NUMBER_OF_ENEMIES];
Bullet bullets[MAX_NUMBER_OF_BULLETS];
Level level;


// --------------------------------------------------------------------------------------
//  Setup ..
//
void setup() {

  arduboy.boot();
  arduboy.flashlight();
  arduboy.systemButtons();
  arduboy.setFrameRate(90);
  arduboy.initRandomSeed();

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


      player.setStatus(PlayerStatus::Active);

      break;

    case GameState::GamePlay:
      Play();
      break;

    case GameState::GameOver:
      GameOver();
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
//  Render a score table ..
//
void ScoreTable() {

  alternate++;
  if (alternate > 108) alternate = 0;
  bool first = alternate % 36 < 18;


  // Render score table ..

  Sprites::drawOverwrite(32, 1, scoreTable, 0);

  Sprites::drawOverwrite(36, 12, (first ? alien_close_1 : alien_close_2), 0);
  Sprites::drawOverwrite(55, 11, ellipsis, 0);
  Sprites::drawOverwrite(75, 14, numbers, 1);  
  Sprites::drawOverwrite(80, 14, numbers, 5);  
  Sprites::drawOverwrite(85, 14, numbers, 0);  

  Sprites::drawOverwrite(36, 22, (first ? alien_close_2 : alien_close_1), 1);
  Sprites::drawOverwrite(55, 21, ellipsis, 0);
  Sprites::drawOverwrite(75, 24, numbers, 3);  
  Sprites::drawOverwrite(80, 24, numbers, 0);  
  Sprites::drawOverwrite(85, 24, numbers, 0);  

  Sprites::drawOverwrite(36, 32, (first ? alien_close_1 : alien_close_2), 2);
  Sprites::drawOverwrite(55, 31, ellipsis, 0);
  Sprites::drawOverwrite(75, 34, numbers, 4);  
  Sprites::drawOverwrite(80, 34, numbers, 5);  
  Sprites::drawOverwrite(85, 34, numbers, 0);  

  Sprites::drawOverwrite(36, 42, (first ? alien_close_2 : alien_close_1), 3);
  Sprites::drawOverwrite(55, 41, ellipsis, 0);
  Sprites::drawOverwrite(75, 44, numbers, 6);  
  Sprites::drawOverwrite(80, 44, numbers, 0);  
  Sprites::drawOverwrite(85, 44, numbers, 0);  



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
    launchFormation(0);//random(0, 6));
    gameState = GameState::GamePlay; 
    
  }

}


// --------------------------------------------------------------------------------------
//  Game Over !
//
void GameOver() {

  Sprites::drawOverwrite(41, 29, gameOver, 0);

}


// --------------------------------------------------------------------------------------
//  Let's play!
//
void Play() {


  // Update the ground's position ..

  const uint8_t speedLookup[] = {0, 16, 8, 0, 4};
  uint8_t speed = speedLookup[absT(player.getYDelta())];

  if (horizonIncrement == speed) {

    level.incHorizon( player.getYDelta() > 0 ? 1 : -1);
    horizonIncrement = 0;
 

    // Update the enemies / bullets relative to the player position ..

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

          score = score + ((static_cast<uint8_t>(enemy->getType()) + 1) * 150);

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

        player.setStatus(PlayerStatus::Explosion4);

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
      gameState = GameState::GameOver;

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
