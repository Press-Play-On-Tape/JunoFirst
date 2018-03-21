#include "src/utils/Arduboy2Ext.h"
#include "src/characters/Player.h"
#include "src/images/Images.h"
#include "src/utils/Enums.h"
#include "src/characters/Enemy.h"

Arduboy2Ext arduboy;
GameState gameState = GameState::Intro;

uint8_t introDelay = 0;
uint8_t yPos = 0;
uint8_t xPos = 60;

Player player;
Enemy enemies[MAX_NUMBER_OF_ENEMIES];


// --------------------------------------------------------------------------------------
//  Setup ..
//
void setup() {

  arduboy.boot();
  arduboy.flashlight();
  arduboy.systemButtons();
  arduboy.setFrameRate(30);
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


  // Handle players actions ..

  if (arduboy.pressed(DOWN_BUTTON))     { player.decYDelta(); }
  if (arduboy.pressed(UP_BUTTON))       { player.incYDelta(); }
  if (arduboy.pressed(LEFT_BUTTON))     { player.decX(); }
  if (arduboy.pressed(RIGHT_BUTTON))    { player.incX(); }

  RenderScreen(&player, enemies);

}


// --------------------------------------------------------------------------------------
//  Render the screen
//
void RenderScreen(Player *player, Enemy *enemies) {

  arduboy.setCursor(0,0);
  arduboy.print(player->getYDelta());

  switch (yPos) {

    case 0:
      arduboy.drawLine(0, 20, WIDTH, 20, WHITE);
      arduboy.drawLine(0, 22, WIDTH, 22, WHITE);
      arduboy.drawLine(0, 26, WIDTH, 26, WHITE);
      arduboy.drawLine(0, 32, WIDTH, 32, WHITE);
      arduboy.drawLine(0, 40, WIDTH, 40, WHITE);
      arduboy.drawLine(0, 50, WIDTH, 50, WHITE);
      arduboy.drawLine(0, 62, WIDTH, 62, WHITE);
      break;

    case 1:
      arduboy.drawLine(0, 20, WIDTH, 20, WHITE);
      arduboy.drawLine(0, 23, WIDTH, 23, WHITE); //1
      arduboy.drawLine(0, 28, WIDTH, 28, WHITE); //2
      arduboy.drawLine(0, 35, WIDTH, 35, WHITE); //3
      arduboy.drawLine(0, 44, WIDTH, 44, WHITE); //4
      arduboy.drawLine(0, 55, WIDTH, 55, WHITE); //5
      arduboy.drawLine(0, 68, WIDTH, 68, WHITE); //6
      break;

    case 2:
      arduboy.drawLine(0, 20, WIDTH, 20, WHITE);
      arduboy.drawLine(0, 24, WIDTH, 24, WHITE); //2
      arduboy.drawLine(0, 30, WIDTH, 30, WHITE); //4
      arduboy.drawLine(0, 38, WIDTH, 38, WHITE); //6
      arduboy.drawLine(0, 48, WIDTH, 48, WHITE); //8
      arduboy.drawLine(0, 60, WIDTH, 60, WHITE); //10
      arduboy.drawLine(0, 74, WIDTH, 74, WHITE); //12
      break;

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