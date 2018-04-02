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
    Serial.println("Load enemeies");
    launchFormation(1);
    gameState = GameState::GamePlay; 
    
  }

}


// --------------------------------------------------------------------------------------
//  Let's play!
//
void Play() {
arduboy.setCursor(0,0);

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

      if (enemy->getActive()) {
        enemy->move(&player);
      }    

    }
    
  }
  
  horizonIncrement++;

// Enemy *enemy = &enemies[0];
// arduboy.setCursor(0,0);
// arduboy.print(enemy->getX());
// arduboy.print(",");
// arduboy.print(enemy->getY());
// arduboy.print("  ");
// arduboy.print(enemy->getXDelta());
// arduboy.print(",");
// arduboy.print(enemy->getYDelta());
// arduboy.print(" ");
// arduboy.print(enemy->isVisible());
// arduboy.print(" ");

// Serial.print("enemies >");

//     for (uint8_t y = 0; y < MAX_NUMBER_OF_ENEMIES; y++) {

//       Enemy *enemy = &enemies[y];

//       if (enemy->getActive()) {

//         Serial.print(", (");
//         Serial.print(enemy->getX());
//         Serial.print(",");
//         Serial.print(enemy->getY());
//         Serial.print(")");

//       }
//     }
// Serial.println("");

if (arduboy.everyXFrames(4)) {

  for (uint8_t x = 0; x < MAX_NUMBER_OF_ENEMIES; x++) {

    Enemy *enemy = &enemies[x];

    if (enemy->getActive()) {
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

  if (!arduboy.pressed(DOWN_BUTTON) && !arduboy.pressed(UP_BUTTON) && arduboy.everyXFrames(32)) { player.decelerate(); }

}

void launchFormation(uint8_t formationNumber) {

  uint16_t dataOffset = 0;
  const uint8_t *formationToLoad = formations[formationNumber];

  uint8_t numberOfEnemies = pgm_read_byte(&formationToLoad[dataOffset++]);

  for (uint8_t x = 0; x < numberOfEnemies; x++) {

    for (uint8_t y = 0; y < MAX_NUMBER_OF_ENEMIES; y++) {

      Enemy *enemy = &enemies[y];

      if (!enemy->getActive()) {

        enemy->setEnemyType(static_cast<EnemyType>(pgm_read_byte(&formationToLoad[dataOffset++])));
        enemy->setX(pgm_read_byte(&formationToLoad[dataOffset++]));
        enemy->setY(pgm_read_byte(&formationToLoad[dataOffset++]));
        enemy->setXDelta(pgm_read_byte(&formationToLoad[dataOffset++]));
        enemy->setYDelta(pgm_read_byte(&formationToLoad[dataOffset++]));
        enemy->setMovementSequence(static_cast<MovementSequence>(pgm_read_byte(&formationToLoad[dataOffset++])));
        enemy->setActive(true);

        break;

      }    

    }

  }

}
