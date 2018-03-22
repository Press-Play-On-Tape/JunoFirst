#include "src/utils/Arduboy2Ext.h"
#include "src/characters/Player.h"
#include "src/images/Images.h"
#include "src/utils/Enums.h"
#include "src/characters/Enemy.h"
#include "src/levels/Level.h"

Arduboy2Ext arduboy;
GameState gameState = GameState::Intro;

uint8_t introDelay = 0;
uint8_t yPos = 0;
uint8_t xPos = 60;
uint8_t hoizonIncrement = 0;

Player player;
Enemy enemies[MAX_NUMBER_OF_ENEMIES];
Level level;


// --------------------------------------------------------------------------------------
//  Setup ..
//
void setup() {

  arduboy.boot();
  arduboy.flashlight();
  arduboy.systemButtons();
  arduboy.setFrameRate(60);
  arduboy.initRandomSeed();


  // Initialise a couple of the enemies ..

  enemies[0].setEnemyType(EnemyType::EnemyType1);
  enemies[0].setActive(true);
  enemies[0].setX(20);
  enemies[0].setY(22);

  enemies[1].setEnemyType(EnemyType::EnemyType1);
  enemies[1].setActive(true);
  enemies[1].setX(50);
  enemies[1].setY(13);

  enemies[2].setEnemyType(EnemyType::EnemyType1);
  enemies[2].setActive(true);
  enemies[2].setX(90);
  enemies[2].setY(8);

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

  if (arduboy.justPressed(A_BUTTON)) { 

    player.reset();  
    gameState = GameState::GamePlay; 
    
  }

}


// --------------------------------------------------------------------------------------
//  Let's play!
//
void Play() {


  // Update the ground's position ..

  const uint8_t speedLookup[] = {0, 4, 2, 0, 1};
  uint8_t speed = speedLookup[absT(player.getYDelta())];

  if (hoizonIncrement == speed) {
    level.incHorizon( player.getYDelta() > 0 ? 1 : -1);
    hoizonIncrement = 0;
  }
  
  hoizonIncrement++;



  // Update the enemies ..

  for (uint8_t x = 0; x < MAX_NUMBER_OF_ENEMIES; x++) {

    Enemy *enemy = &enemies[x];

    if (enemy->getActive()) {

//      enemy.set

    }    

  }


  RenderScreen(&player, enemies);


  // Handle players actions ..

  if (arduboy.pressed(DOWN_BUTTON))     { if (player.decYDelta()) hoizonIncrement = 0; }
  if (arduboy.pressed(UP_BUTTON))       { if (player.incYDelta()) hoizonIncrement = 0; }
  if (arduboy.pressed(LEFT_BUTTON))     { player.decX(); }
  if (arduboy.pressed(RIGHT_BUTTON))    { player.incX(); }

  if (!arduboy.pressed(DOWN_BUTTON) && !arduboy.pressed(UP_BUTTON) && arduboy.everyXFrames(8)) { player.decelerate(); }

}


// --------------------------------------------------------------------------------------
//  Render the screen
//
void RenderScreen(Player *player, Enemy *enemies) {


  // Render the horizon ;

  const uint8_t horizon[5][7] = {
                                  { 0, 2,  6, 12, 20, 30, 42 },
                                  { 0, 2,  7, 13, 22, 32, 45 },
                                  { 0, 3,  8, 15, 24, 35, 48 },
                                  { 0, 3,  9, 16, 26, 37, 51 },
                                  { 0, 4, 10, 18, 28, 40, 54 }
                                };                        




  uint8_t row = level.getHorizon();

  for (uint8_t col = 0; col < HORIZON_COL_COUNT; col++) {

// Stephane uncomment this line and comment the line below out ..
//    arduboy.drawLine(0, horizon[row][col] + 8, WIDTH, horizon[row][col] + 8, WHITE);
    arduboy.drawHorizontalDottedLine((col + 2) / 2, WIDTH, horizon[row][col] + 8, col + 2);

  }



  // Render the enemies ..

  for (uint8_t x = 0; x < MAX_NUMBER_OF_ENEMIES; x++) {

    Enemy *enemy = &enemies[x];

    uint8_t const *imageName = nullptr;
    uint8_t const *maskName = nullptr;

    if (enemy->getActive()) {

      switch (enemy->getType()) {

        case EnemyType::EnemyType1:

          switch (enemy->getSize()) {

            case ImageSize::Far:

              imageName = alien_1_far;
              maskName = alien_1_far_mask;
              break;

            case ImageSize::Medium:

              if (arduboy.getFrameCount(4) < 2) {
                imageName = alien_1_medium_1;
                maskName = alien_1_medium_1_mask;
              }
              else {
                imageName = alien_1_medium_2;
                maskName = alien_1_medium_2_mask;
              }
              break;

            case ImageSize::Close:

              if (arduboy.getFrameCount(4) < 2) {
                imageName = alien_1_close_1;
                maskName = alien_1_close_1_mask;
              }
              else {
                imageName = alien_1_close_2;
                maskName = alien_1_close_2_mask;
              }
              break;

          }

          break;

        case EnemyType::EnemyType2:
          // enemy 2 images;
          break;

      }

      // Render image ..

      arduboy.drawCompressed(enemy->getX(), enemy->getY(), maskName, BLACK);
      arduboy.drawCompressed(enemy->getX(), enemy->getY(), imageName, WHITE);
 
    }

  }


  // Render the space ship ..  Depending on the YDelta value, we flip between the image frames 
  // at different rates.  The frame rates are stored in an array called 'frames' and we use 
  // the absolut value of yDelta to look up the frame rate.  If the spaceship is statinary,
  // the rate is 0, slowly moving forward or backwards (yDelta = 1 or -1) results in a value
  // of 4.  The fastest spaceship speed (YDelta = 4 or -4) results in a fast frame rate of 2.

  const uint8_t frames[] = {0, 4, 3, 3, 2};
  uint8_t frameRate = frames[absT(player->getYDelta())];

  switch (player->getYDelta()) {

    case -4 ... -1:

      if (arduboy.everyXFrames(frameRate)) { 
        arduboy.drawCompressed(player->getX(), player->getY() - 4, spaceship_backwards_1_mask, BLACK);
        arduboy.drawCompressed(player->getX(), player->getY() - 4, spaceship_backwards_1, WHITE);
      }
      else {
        arduboy.drawCompressed(player->getX(), player->getY() - 4, spaceship_backwards_2_mask, BLACK);
        arduboy.drawCompressed(player->getX(), player->getY() - 4, spaceship_backwards_2, WHITE);
      }
      break;

    case 0:

      arduboy.drawCompressed(player->getX(), player->getY(), spaceship_neutral_mask, BLACK);
      arduboy.drawCompressed(player->getX(), player->getY(), spaceship_neutral, WHITE);
      break;

    case 1 ... 4:

      if (arduboy.everyXFrames(frameRate)) { 
        arduboy.drawCompressed(player->getX(), player->getY(), spaceship_advance_1_mask, BLACK);
        arduboy.drawCompressed(player->getX(), player->getY(), spaceship_advance_1, WHITE);
      }
      else {
        arduboy.drawCompressed(player->getX(), player->getY(), spaceship_advance_2_mask, BLACK);
        arduboy.drawCompressed(player->getX(), player->getY(), spaceship_advance_2, WHITE);
      }
      break;

  }

}
