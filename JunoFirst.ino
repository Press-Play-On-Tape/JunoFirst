#include "src/utils/Arduboy2Ext.h"
#include "src/characters/Player.h"
#include "src/characters/Enemy.h"
#include "src/characters/Bullet.h"
#include "src/images/Images.h"
#include "src/utils/Enums.h"
#include "src/levels/Level.h"
#include "src/levels/Formations.h"

Arduboy2Ext arduboy;
GameState gameState = GameState::Intro;

uint8_t introDelay = 0;
uint8_t yPos = 0;
uint8_t xPos = 60;
uint8_t horizonIncrement = 0;

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


  bullets[0].setX(3);

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

    case GameState::GamePlay:
      Play();
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

  arduboy.drawCompressed(18, 4, logo, WHITE);


  // Display 'Press A' button after a short period of time ..

  if (introDelay < 32) {
    introDelay++;
  }
  else {    
    arduboy.drawCompressed(51, 55, pressA, WHITE);
  }


  // If 'A' bUtton is pressed move to game play ..

  if (arduboy.pressed(A_BUTTON)) { 

    player.reset();  
    launchFormation(0);
    gameState = GameState::GamePlay; 
    
  }

}


// --------------------------------------------------------------------------------------
//  Let's play!
//
void Play() {

  // Update the ground's position ..

//  const uint8_t speedLookup[] = {0, 4, 2, 0, 1};
  const uint8_t speedLookup[] = {0, 16, 8, 0, 4};
  uint8_t speed = speedLookup[absT(player.getYDelta())];

  if (horizonIncrement == speed) {

    level.incHorizon( player.getYDelta() > 0 ? 1 : -1);
    horizonIncrement = 0;
  



    // Update the enemies relative to the player position ..

    for (uint8_t x = 0; x < MAX_NUMBER_OF_ENEMIES; x++) {

      Enemy *enemy = &enemies[x];

      if (enemy->getStatus() == EnemyStatus::Active) {
        enemy->move(&player);
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

  if (arduboy.pressed(A_BUTTON))        { 

    if (playerBullet.getY() == 0) {

      playerBullet.setY(45);
      playerBullet.setX(player.getX() + 7);

    }

  }

  if (!arduboy.pressed(DOWN_BUTTON) && !arduboy.pressed(UP_BUTTON) && arduboy.everyXFrames(32)) { player.decelerate(); }


  // Update player bullet position ..
  //if (arduboy.everyXFrames(2)) {

    uint8_t bulletY = playerBullet.getY();

    playerBullet.setY(bulletY > 20 ? bulletY - 5 : 0);

  //}



  // Did our bullet hit an enemy?

  if (playerBullet.getY() > 0) {

    Rect bulletRect = { playerBullet.getX() - 1, playerBullet.getY() - 5, 3, 5 };

    for (uint8_t x = 0; x < MAX_NUMBER_OF_ENEMIES; x++) {

      Enemy *enemy = &enemies[x];

      if (enemy->getStatus() == EnemyStatus::Active) {

        Rect enemyRect = { enemy->getXDisplay(), enemy->getYDisplay(), enemy->getWidth(), enemy->getHeight() };

        if (arduboy.collide(bulletRect, enemyRect)) {

          enemy->setStatus(EnemyStatus::Explosion4);

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

// arduboy.setCursor(0,0);
// arduboy.print((uint8_t)enemyStatus);
// arduboy.print((uint8_t)enemyStatus);
      enemy->setStatus(--enemyStatus);
// arduboy.print(" ");
// arduboy.print((uint8_t)enemy->getStatus());

    }    

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
