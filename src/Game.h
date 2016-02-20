#ifndef GAME_H
#define GAME_H

extern "C"
{
	#include <os.h>
	#include "SDL/SDL.h"
	#include "FalldownLib/FalldownLib.h"
}

#include "Defines.h"

class Game
{
public:
	Game(SDL_Surface* pScreen);
	~Game();

	bool Loop();
	bool IsGameOver() const;
	int GetScore() const;
	
protected:
	bool PollEvents();
	void UpdateLevel();
	void UpdateDisplay();

protected:
	SDL_Surface	*m_pScreen;//Does not own
	FalldownLib	m_Falldown;
	SDL_Surface	*m_pBall;
	SDL_Surface	*m_pRow;
	nSDL_Font *m_pFont;
        int m_nLevel;
	bool m_bGameOver;
	bool m_bPaused;
};

#endif
