#include "src/utils/Arduboy2Ext.h"

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

    uint8_t y = horizon[row][col] + 4;

    if (y <= 56) {
//      arduboy.drawLine(0, y, WIDTH, y, WHITE);
      arduboy.drawHorizontalDottedLine((col + 2) / 2, WIDTH, y, col + 2);
//      arduboy.drawHorizontalDottedLine(0, WIDTH, y, col + 2);

    }

  }



  // Render the enemies ..

  for (uint8_t x = 0; x < MAX_NUMBER_OF_ENEMIES; x++) {

    Enemy *enemy = &enemies[x];

    uint8_t const *imageName = nullptr;
    uint8_t const *maskName = nullptr;

    if (enemy->isVisible()) {

      if (enemy->getStatus() == EnemyStatus::Active) {
          
        switch (enemy->getType()) {

          case EnemyType::EnemyType1:

            switch (enemy->getSize()) {

              case ImageSize::Horizon:

                imageName = alien_1_horizon;
                maskName = alien_1_horizon_mask;
                break;

              case ImageSize::Far:

                imageName = alien_1_far;
                maskName = alien_1_far_mask;
                break;

              case ImageSize::Medium:

                if (arduboy.getFrameCount(ENEMY_FRAME_COUNT) < ENEMY_FRAME_COUNT_HALF) {
                  imageName = alien_1_medium_1;
                  maskName = alien_1_medium_1_mask;
                }
                else {
                  imageName = alien_1_medium_2;
                  maskName = alien_1_medium_2_mask;
                }
                break;

              case ImageSize::Close:

                if (arduboy.getFrameCount(ENEMY_FRAME_COUNT) < ENEMY_FRAME_COUNT_HALF) {
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

        Sprites::drawExternalMask(enemy->getXDisplay(), enemy->getYDisplay(), imageName, maskName, 0, 0 );

      }
      else {

        switch (enemy->getStatus()) {

          case (EnemyStatus::Explosion1):
            imageName = alien_close_explosion_4;
            break;

          case (EnemyStatus::Explosion2):
            imageName = alien_close_explosion_3;
            break;

          case (EnemyStatus::Explosion3):
            imageName = alien_close_explosion_2;
            break;

          case (EnemyStatus::Explosion4):
            imageName = alien_close_explosion_1;
            break;

          default: break;
            
        }

        Sprites::drawSelfMasked(enemy->getXDisplay(), enemy->getYDisplay(), imageName, 0);

      }
 
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

      if (arduboy.getFrameCount(frameRate) % frameRate < frameRate / 2) { 
        Sprites::drawExternalMask(player->getX(), player->getY() - 4, spaceship_backwards_1, spaceship_backwards_1_mask, 0, 0);
      }
      else {
        Sprites::drawExternalMask(player->getX(), player->getY() - 4, spaceship_backwards_2, spaceship_backwards_2_mask, 0, 0);
      }
      break;

    case 0:

      Sprites::drawExternalMask(player->getX(), player->getY(), spaceship_neutral, spaceship_neutral_mask, 0, 0);
      break;

    case 1 ... 4:

      if (arduboy.getFrameCount(frameRate) % frameRate < frameRate / 2) { 
        Sprites::drawExternalMask(player->getX(), player->getY(), spaceship_advance_1, spaceship_advance_1_mask, 0, 0);
      }
      else {
        Sprites::drawExternalMask(player->getX(), player->getY(), spaceship_advance_2, spaceship_advance_2_mask, 0, 0);
      }
      break;

  }



  // Render player bullet ..

  if (playerBullet.getY() > 0) {

    // arduboy.drawLine(playerBullet.getX(), playerBullet.getY(), playerBullet.getX(), playerBullet.getY() - 2, WHITE); 
    // arduboy.drawLine(playerBullet.getX(), playerBullet.getY() - 4, playerBullet.getX(), playerBullet.getY() - 5, WHITE); 
    // arduboy.drawLine(playerBullet.getX(), playerBullet.getY() - 7, playerBullet.getX(), playerBullet.getY() - 8, WHITE); 
    // arduboy.drawLine(playerBullet.getX(), playerBullet.getY() - 10, playerBullet.getX(), playerBullet.getY() - 10, WHITE); 

    arduboy.drawLine(playerBullet.getX(), playerBullet.getY(), playerBullet.getX(), playerBullet.getY() - 5, WHITE); 

  }



  // Render scoreboard ..

  arduboy.fillRect(0, 56, WIDTH, HEIGHT, BLACK);

  Sprites::drawOverwrite(0, 59, numbers, 0);
  Sprites::drawOverwrite(5, 59, numbers, 0);
  Sprites::drawOverwrite(10, 59, numbers, 0);
  Sprites::drawOverwrite(15, 59, numbers, 0);
  Sprites::drawOverwrite(20, 59, numbers, 0);
  Sprites::drawOverwrite(25, 59, numbers, 0);

  Sprites::drawOverwrite(50, 59, wave, 0);
  Sprites::drawOverwrite(74, 59, numbers, 0);
  Sprites::drawOverwrite(79, 59, numbers, 1);
  
  Sprites::drawOverwrite(102, 59, life, 0);
  Sprites::drawOverwrite(109, 59, life, 0);
  Sprites::drawOverwrite(116, 59, life, 0);
  Sprites::drawOverwrite(123, 59, life, 0);


  // Fuel ?

  arduboy.drawLine(0, 57, 93, 57);
  
}