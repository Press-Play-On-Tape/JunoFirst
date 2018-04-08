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

#ifdef SCOREBOARD_BOTTOM
    if (y <= 56) {
      arduboy.drawHorizontalDottedLine((col + 2) / 2, WIDTH, y, col + 2);
    }
#endif

#ifdef SCOREBOARD_SIDE
    if (y <= HEIGHT) {
      arduboy.drawHorizontalDottedLine((col + 2) / 2, WIDTH, y, col + 2);
    }
#endif

  }



  // Render the enemies ..

  for (uint8_t x = 0; x < MAX_NUMBER_OF_ENEMIES; x++) {

    Enemy *enemy = &enemies[x];

    uint8_t const *imageName = nullptr;
    uint8_t const *maskName = nullptr;
    uint8_t frame = 0;

    if (enemy->isVisible()) {

      if (enemy->getStatus() == EnemyStatus::Active) {

        switch (enemy->getSize()) {

          case ImageSize::Horizon:

            imageName = alien_horizon;
            maskName = alien_horizon_mask;
            break;

          case ImageSize::Far:

            imageName = alien_far;
            maskName = alien_far_mask;
            break;

          case ImageSize::Medium:

            if (arduboy.getFrameCount(ENEMY_FRAME_COUNT) < ENEMY_FRAME_COUNT_HALF) {
              imageName = alien_medium_1;
              maskName = alien_medium_1_mask;
            }
            else {
              imageName = alien_medium_2;
              maskName = alien_medium_2_mask;
            }

            frame = static_cast<uint8_t>(enemy->getType());

            break;

          case ImageSize::Close:

            if (arduboy.getFrameCount(ENEMY_FRAME_COUNT) < ENEMY_FRAME_COUNT_HALF) {
              imageName = alien_close_1;
              maskName = alien_close_1_mask;
            }
            else {
              imageName = alien_close_2;
              maskName = alien_close_2_mask;
            }

            frame = static_cast<uint8_t>(enemy->getType());

            break;

        }


        // Render image ..

        Sprites::drawExternalMask(enemy->getXDisplay(), enemy->getYDisplay(), imageName, maskName, frame, frame);

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


  // Render the space ship ..  

  const uint8_t frames[] = {0, 4, 3, 3, 2};
  uint8_t frameRate = frames[absT(player->getYDelta())];

  if (player->getStatus() == PlayerStatus::Active) {
      
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

  }
  else {

    uint8_t const *imageName = nullptr;

    switch (player->getStatus()) {

      case PlayerStatus::Explosion1:
        imageName = alien_close_explosion_4;
        break;

      case PlayerStatus::Explosion2:
        imageName = alien_close_explosion_3;
        break;

      case PlayerStatus::Explosion3:
        imageName = alien_close_explosion_2;
        break;

      case PlayerStatus::Explosion4:
        imageName = alien_close_explosion_1;
        break;

      default: 
        imageName = alien_close_explosion_5;
        break;
        
    }

    Sprites::drawSelfMasked(player->getX(), player->getY(), imageName, 0);
    
  }


  // Render player bullet ..

  if (playerBullet.getY() > 0) {

    // arduboy.drawLine(playerBullet.getX(), playerBullet.getY(), playerBullet.getX(), playerBullet.getY() - 2, WHITE); 
    // arduboy.drawLine(playerBullet.getX(), playerBullet.getY() - 4, playerBullet.getX(), playerBullet.getY() - 5, WHITE); 
    // arduboy.drawLine(playerBullet.getX(), playerBullet.getY() - 7, playerBullet.getX(), playerBullet.getY() - 8, WHITE); 
    // arduboy.drawLine(playerBullet.getX(), playerBullet.getY() - 10, playerBullet.getX(), playerBullet.getY() - 10, WHITE); 

    arduboy.drawLine(playerBullet.getX(), playerBullet.getY(), playerBullet.getX(), playerBullet.getY() - 5, WHITE); 

  }


  // Render enemy bullets ..

  for (uint8_t x = 0; x < MAX_NUMBER_OF_BULLETS; x++) {

    Bullet *bullet = &bullets[x];

    if (bullet->getY() > 0) { 

      arduboy.drawRect(bullet->getX(), bullet->getY(), 2, 2, WHITE);

    }

  }


#ifdef SCOREBOARD_BOTTOM

  // Render scoreboard ..

  arduboy.fillRect(0, 56, WIDTH, HEIGHT, BLACK);


  // Score ..
  {
      uint8_t digits[6] = {};
      extractDigits(digits, score);
      
      for(uint8_t i = 0, x = 25; i < 6; ++i, x -= 5) {
        Sprites::drawOverwrite(x, 59, numbers, digits[i]);
      }
  }

  Sprites::drawOverwrite(50, 59, wave, 0);
  Sprites::drawOverwrite(74, 59, numbers, 0);
  Sprites::drawOverwrite(79, 59, numbers, 1);
  
  Sprites::drawOverwrite(102, 59, life, 0);
  Sprites::drawOverwrite(109, 59, life, 0);
  Sprites::drawOverwrite(116, 59, life, 0);
  Sprites::drawOverwrite(123, 59, life, 0);


  // Fuel ?

  arduboy.drawLine(0, 57, 93, 57);

#endif

#ifdef SCOREBOARD_SIDE

  if (arduboy.everyXFrames(2)) {
    
    alternate++;

  }


  // Render scoreboard ..

  arduboy.fillRect(120, 0, WIDTH, HEIGHT, BLACK);
  arduboy.drawLine(121, 0, 121, HEIGHT, WHITE);


  if (alternate < 128) {

    // Score ..
    {
        uint8_t digits[6] = {};
        extractDigits(digits, level.getScore());
        
        for(int8_t i = 5, y = 1; i >= 0; --i, y += 5) {
          Sprites::drawOverwrite(123, y, numbers_vert, digits[i]);
        }
    }


    Sprites::drawOverwrite(123, 40, life_vert, 0);
    Sprites::drawOverwrite(123, 46, life_vert, 0);
    Sprites::drawOverwrite(123, 52, life_vert, 0);
    Sprites::drawOverwrite(123, 58, life_vert, 0);

  }
  else {

    Sprites::drawOverwrite(123, 0, fuel, 0);

    uint8_t fuel = player->getFuel() / 10;
    for (uint8_t x = 5; x < fuel; x+=2) {

      arduboy.drawRect(123, x, WIDTH, 1, WHITE);

    }

    Sprites::drawOverwrite(123, 50, heart, 0);

    for (uint8_t x = 0; x < player->getHealth(); x+=2) {

      arduboy.drawRect(123, 57 + x, WIDTH, 1, WHITE);

    }


  }

#endif
}