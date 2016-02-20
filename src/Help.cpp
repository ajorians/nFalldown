#include "Help.h"

FalldownHelp::FalldownHelp(SDL_Surface* pScreen)
: m_pScreen(pScreen)
{
	m_pFont = nSDL_LoadFont(NSDL_FONT_VGA, 0, 0, 0);
}

FalldownHelp::~FalldownHelp()
{
	nSDL_FreeFont(m_pFont);
}

bool FalldownHelp::Loop()
{
	//Handle keypresses
	if( PollEvents() == false )
		return false;
	
	UpdateDisplay();
	
	return true;
}

bool FalldownHelp::PollEvents()
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
					case SDLK_RETURN:
					case SDLK_SPACE:
						return false;
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

void FalldownHelp::UpdateDisplay()
{
	SDL_FillRect(m_pScreen, NULL, SDL_MapRGB(m_pScreen->format, 101, 205, 204));

	nSDL_DrawString(m_pScreen, m_pFont, 25, 50, 
"Falldown is a very simple game\n\
basically just use the arrow keys\n\
or the 4 & 6 keys to move the ball\n\
left and right.\n\
\n\
Just make sure the ball doesn't go\n\
too high or else it is game over!\n\
\n\
And have fun!");		
	
	SDL_UpdateRect(m_pScreen, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}




