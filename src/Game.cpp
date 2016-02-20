#include "Game.h"
#include "GameOver.h"
#include "FalldownBallGraphic.h"
#include "FalldownRowGraphic.h"

#define BALL_SIDE_MOVEMENT_SPEED	(3)

Game::Game(SDL_Surface* pScreen)
: m_pScreen(pScreen), m_nLevel(0), m_bGameOver(false), m_bPaused(false)
{
	FalldownLibCreate(&m_Falldown);
	m_pFont = nSDL_LoadFont(NSDL_FONT_THIN, 0/*R*/, 0/*G*/, 0/*B*/);
	m_pBall = nSDL_LoadImage(image_FallDownBall);
        SDL_SetColorKey(m_pBall, SDL_SRCCOLORKEY, SDL_MapRGB(m_pBall->format, 0, 255, 0));

	m_pRow = nSDL_LoadImage(image_FallDownRow);

	if( is_classic ) {
		AdjustFallDownExtraSpeed(m_Falldown, 0, 0);
                AdjustFallDownSpeed(m_Falldown, 2);
	} else {
		AdjustFallDownExtraSpeed(m_Falldown, 0, 0);
		AdjustFallDownSpeed(m_Falldown, 1);
	}
}

Game::~Game()
{
	FalldownLibFree(&m_Falldown);
	nSDL_FreeFont(m_pFont);

	SDL_FreeSurface(m_pBall);
	SDL_FreeSurface(m_pRow);
}

bool Game::Loop()
{
	//Handle keypresses
	if( PollEvents() == false )
		return false;

	if( !m_bPaused ) {
		StepFalldown(m_Falldown);
	        UpdateLevel();
		m_bGameOver = IsFalldownGameOver(m_Falldown);
	}
	
	//Update screen
	UpdateDisplay();
	
	//SDL_Delay(30);
	
	return !IsGameOver();
}

bool Game::IsGameOver() const
{
	return m_bGameOver;
}

int Game::GetScore() const
{
	return GetFalldownScore(m_Falldown);
}

bool Game::PollEvents()
{
	SDL_Event event;
	
	/* Poll for events. SDL_PollEvent() returns 0 when there are no  */
	/* more events on the event queue, our while loop will exit when */
	/* that occurs.                                                  */
	while( SDL_PollEvent( &event ) )
	{
		/* We are only worried about SDL_KEYDOWN and SDL_KEYUP events */
		switch( event.type )
		{
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) 
				{
					case SDLK_ESCAPE:
						fprintf(stderr, "Hit Escape!n");
					return false;
					break;

					case SDLK_RIGHT:
					case SDLK_6:
						if( !m_bPaused )
							MoveFalldownBall(m_Falldown, BALL_SIDE_MOVEMENT_SPEED);
					break;
					
					case SDLK_LEFT:
					case SDLK_4:
						if( !m_bPaused )
							MoveFalldownBall(m_Falldown, -BALL_SIDE_MOVEMENT_SPEED);
						break;

					case SDLK_p:
						m_bPaused = !m_bPaused;
						break;
					default:
						break;
				}
				break;
			
			//Called when the mouse moves
			case SDL_MOUSEMOTION:
				break;
			
			case SDL_KEYUP:
				break;
			
			default:
				break;
		}
	}
	return true;
}

void Game::UpdateLevel()
{
   int nScore = GetScore();
   switch(m_nLevel)
   {
      default:
      case 0:
         if( nScore > 500 ) {
            m_nLevel = 1;
            if( is_classic ) {
               AdjustFallDownExtraSpeed(m_Falldown, 1, 10);
            } else {
               AdjustFallDownExtraSpeed(m_Falldown, 1, 10);
            }
         }
         break;
      case 1:
         if( nScore > 1000 ) {
            m_nLevel = 2;
            if( is_classic ) {
               AdjustFallDownExtraSpeed(m_Falldown, 1, 5);
            } else {
               AdjustFallDownExtraSpeed(m_Falldown, 1, 5);
            }
         }
         break;
      case 2:
         if( nScore > 1500 ) {
            m_nLevel = 3;
            if( is_classic ) {
               AdjustFallDownExtraSpeed(m_Falldown, 1, 3);
            } else {
               AdjustFallDownExtraSpeed(m_Falldown, 1, 3);
            }
         }
         break;
      case 3:
         if( nScore > 2000 ) {
            m_nLevel = 4;
            if( is_classic ) {
               AdjustFallDownExtraSpeed(m_Falldown, 0, 0);
               AdjustFallDownSpeed(m_Falldown, 3);
            } else
            {
               AdjustFallDownExtraSpeed(m_Falldown, 0, 0);
               AdjustFallDownSpeed(m_Falldown, 2);
            }
         }
         break;
      case 4:
         if( nScore > 2500 ) {
            m_nLevel = 5;
            if( is_classic ) {
               AdjustFallDownExtraSpeed(m_Falldown, 1, 10);
            } else
            {
               AdjustFallDownExtraSpeed(m_Falldown, 1, 10);
            }
         }
         break;
      case 5:
         if( nScore > 3000 ) {
            if( is_classic ) {
               m_nLevel = 6;
               AdjustFallDownExtraSpeed(m_Falldown, 1, 5);
            }
         }
         break;
      case 6:
         if( nScore > 3500 ) {
            if( is_classic ) {
               m_nLevel = 7;
               AdjustFallDownExtraSpeed(m_Falldown, 1, 3);
            }
         }
         break;
      case 7:
         if( nScore > 4000 ) {
            if( is_classic ) {
               m_nLevel = 8;
               AdjustFallDownExtraSpeed(m_Falldown, 0, 0);
               AdjustFallDownSpeed(m_Falldown, 4);
            }
         }
         break;
      case 8:
         if( nScore > 4500 ) {
            if( is_classic ) {
               m_nLevel = 9;
               AdjustFallDownExtraSpeed(m_Falldown, 1, 10);
            }
         }
         break;
      case 9:
         if( nScore > 5000 ) {
            if( is_classic ) {
               m_nLevel = 10;
               AdjustFallDownExtraSpeed(m_Falldown, 1, 5);
            }
         }
         break;
      case 10:
         if( nScore > 5500 ) {
            if( is_classic ) {
               m_nLevel = 11;
               AdjustFallDownExtraSpeed(m_Falldown, 1, 3);
            }
         }
         break;
      case 11:
         if( nScore > 6000 ) {
            if( is_classic ) {
               m_nLevel = 12;
               AdjustFallDownExtraSpeed(m_Falldown, 0, 0);
               AdjustFallDownSpeed(m_Falldown, 5);
            }
         }
         break;
      case 12:
         break;
   }
}

void Game::UpdateDisplay()
{
	SDL_UpdateRect(m_pScreen, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	//Draw background
	SDL_FillRect(m_pScreen, NULL, SDL_MapRGB(m_pScreen->format, GAME_BACKGROUND_R, GAME_BACKGROUND_G, GAME_BACKGROUND_B));
	
	//Draw score stuff
	nSDL_DrawString(m_pScreen, m_pFont, 0, SCREEN_HEIGHT-10, "%d", GetScore() );

	int nBallX = 0, nBallY = 0;
	GetFalldownBallPos(m_Falldown, &nBallX, &nBallY);
	SDL_Rect rectBall;
	int nBallHeight = 16;
	int nBallWidth = 16;
	rectBall.x = nBallX-(nBallWidth/2);
	rectBall.y = nBallY-nBallHeight;
	rectBall.w = nBallWidth;
	rectBall.h = nBallHeight;
	SDL_BlitSurface(m_pBall, NULL, m_pScreen, &rectBall);

	int nSegmentWidth = SCREEN_WIDTH/FALLDOWN_ROW_SEGMENTS;
	for(int i=0; i<NUMBER_FALLDOWN_ROWS; i++) {
		int nY = GetFalldownRowY(m_Falldown, i);
		for(int nX=0; nX<FALLDOWN_ROW_SEGMENTS; nX++) {
			if( IsFalldownRowGap(m_Falldown, i, nX ) )
				continue;
			SDL_Rect rectDst;
			rectDst.x = nSegmentWidth * nX;
			rectDst.y = nY;
			rectDst.w = nSegmentWidth;
			rectDst.h = 10;
			SDL_BlitSurface(m_pRow, NULL, m_pScreen, &rectDst);
		}
	}

	if( m_bPaused ) {
		int nWidth = nSDL_GetStringWidth(m_pFont, "Paused");
		nSDL_DrawString(m_pScreen, m_pFont, SCREEN_WIDTH/2-nWidth/2, SCREEN_HEIGHT/2, "Paused");
	}
}


