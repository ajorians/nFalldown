#ifndef DEFINES_H
#define DEFINES_H

extern "C"
{
        #include <os.h>
        #include "SDL/SDL.h"
}

#ifndef DEBUG_MSG
#define DEBUG_MSG//     printf
#endif

#define FALLDOWN_HIGHSCORE_FILENAME    "FalldownHighScore.tns"

#define GAME_BACKGROUND_R	(205)
#define GAME_BACKGROUND_G	(205)
#define GAME_BACKGROUND_B	(205)

#endif
