#include "src/utils/Arduboy2Ext.h"
#include "src/utils/FadeEffects.h"




// --------------------------------------------------------------------------------------
//  Show introduction screen ..
//
void Intro() {


  // Draw logo ..

  Sprites::drawOverwrite(18, 4, logo, 0);


  if (!fadeInEffect.isComplete()) {

    fadeInEffect.draw(arduboy);
    fadeInEffect.update();

  }


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
    level.reset(enemies, bullets, &playerBullet);
    gameState = GameState::ScoreTable; 
    introDelay = 0;
    
  }


  // If 'B' bUtton show high scores ..

  if (arduboy.justPressed(B_BUTTON)) { 

    player.reset();
    level.reset(enemies, bullets, &playerBullet);
    gameState = GameState::HighScore; 
    
  }

}