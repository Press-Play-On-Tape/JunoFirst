#include "src/utils/Arduboy2Ext.h"


// --------------------------------------------------------------------------------------
//  Game Over !
//
void GameOver() {

  Sprites::drawOverwrite(1, 18, gameOver, 0);


  // If 'A' bUtton is pressed move to game play ..

  if (arduboy.justPressed(A_BUTTON)) { 

    player.reset();  
    gameState = GameState::SaveScore; 
    introDelay = 0;
    
  }

}