#include <Arduboy2.h>
#include "Images.h"
#include "Enums.h"

Arduboy2 arduboy;
GameState gameState = GameState::Intro;

uint8_t introDelay = 0;
uint8_t yPos = 0;
uint8_t xPos = 60;

// --------------------------------------------------------------------------------------
//  Setup ..
//
void setup() {

  arduboy.boot();
  arduboy.flashlight();
  arduboy.systemButtons();
  arduboy.setFrameRate(30);
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

  arduboy.drawCompressed(14, 8, logo, WHITE);


  // Display 'Press A' button after a short period of time ..

  if (introDelay < 32) {
    introDelay++;
  }
  else {    
    arduboy.drawCompressed(97, 55, pressA, WHITE); 
  }


  // If 'A' bUtton is pressed move to game play ..

  if (arduboy.justPressed(A_BUTTON)) { gameState = GameState::GamePlay; }

}


void Play() {

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

  if (arduboy.everyXFrames(4)) {

    if (arduboy.pressed(DOWN_BUTTON))   { yPos = (yPos == 0 ? 2: yPos - 1); }
    if (arduboy.pressed(UP_BUTTON))     { yPos = (yPos == 2 ? 0: yPos + 1); }

  }


  if (arduboy.pressed(LEFT_BUTTON))     { xPos = (xPos == 10 ? 10: xPos - 2); }
  if (arduboy.pressed(RIGHT_BUTTON))     { xPos = (xPos == 118 ? 118: xPos + 2); }


  arduboy.drawCompressed(xPos, 50, spaceship_neutral_mask, BLACK);
  arduboy.drawCompressed(xPos, 50, spaceship_neutral, WHITE);

}