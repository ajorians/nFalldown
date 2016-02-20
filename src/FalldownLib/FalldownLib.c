//Public domain :)

#include <os.h>
#include "include/FalldownLib.h"
#include "Defines.h"

#define FALLING_SPEED		(3)
#define INITIAL_LINE_SPEED	(1)
#define BALL_WIDTH		(10)

//#define TESTING_LIVE_FOREVER

struct FalldownRow
{
   int m_nRow[FALLDOWN_ROW_SEGMENTS];
   int m_nY;
};

struct Falldown
{
   int m_nBallPosX, m_nBallPosY;
   struct FalldownRow m_Rows[NUMBER_FALLDOWN_ROWS];
   int m_nFallingSpeed;
   int m_nSpeed;
   int m_nSpeedExtra;//How I increment speed more gradually
   int m_nSpeedExtraPart;
   int m_nSpeedExtraPartLimit;
   int m_nLastError;
   int m_nScore;
};

void RandomizeRow(int nRow[FALLDOWN_ROW_SEGMENTS])
{
   int n;
   for(n=0; n<FALLDOWN_ROW_SEGMENTS; n++) {
      nRow[n] = 1;
   }

   int nGaps = (rand() % 3) + 3;//OK if less than gaps are created.
   for(n=0; n<nGaps; n++) {
      nRow[rand()%FALLDOWN_ROW_SEGMENTS] = 0;
   }
}

int GetLineSpacing()
{
   int nSpacing = SCREEN_HEIGHT/(NUMBER_FALLDOWN_ROWS-1);
   return nSpacing;
}

int FalldownLibCreate(FalldownLib* api)
{
   DEBUG_FUNC_NAME;

   struct Falldown* pF = malloc(sizeof(struct Falldown));
   if( pF == NULL ){//Out of memory
      return FALLDOWNLIB_OUT_OF_MEMORY;
   }

   pF->m_nBallPosX = 100;
   pF->m_nBallPosY = 10;

   pF->m_nFallingSpeed = FALLING_SPEED;
   pF->m_nSpeed = INITIAL_LINE_SPEED;
   pF->m_nSpeedExtra = pF->m_nSpeedExtraPart = pF->m_nSpeedExtraPartLimit = 0;

   int n;
   int nSpacing = GetLineSpacing();
   for(n=0; n<NUMBER_FALLDOWN_ROWS; n++) {
      pF->m_Rows[n].m_nY = SCREEN_HEIGHT + n*nSpacing;//(n+1)*nSpacing;
      RandomizeRow(pF->m_Rows[n].m_nRow);
   }

   pF->m_nScore = 0;

   pF->m_nLastError = FALLDOWNLIB_OK;

   *api = pF; 

   return FALLDOWNLIB_OK;
}

int FalldownLibFree(FalldownLib* api)
{
   DEBUG_FUNC_NAME;

   struct Falldown* pF = *api;

   free(pF);
   *api = NULL;
   return FALLDOWNLIB_OK;
}

int GetFalldownError(FalldownLib api)
{
   DEBUG_FUNC_NAME;

   struct Falldown* pF = (struct Falldown*)api;
   return pF->m_nLastError;
}

void ClearFalldownError(FalldownLib api)
{
   DEBUG_FUNC_NAME;

   struct Falldown* pF = (struct Falldown*)api;
   pF->m_nLastError = FALLDOWNLIB_OK;
}

//FalldownLib related functions
int AdjustFallDownSpeed(FalldownLib api, int nSpeed)
{
   DEBUG_FUNC_NAME;

   struct Falldown* pF = (struct Falldown*)api;
   pF->m_nSpeed = nSpeed;

   return FALLDOWNLIB_OK;
}

int AdjustFallDownExtraSpeed(FalldownLib api, int nSpeedExtra, int nSpeedExtraLimit)
{
   DEBUG_FUNC_NAME;

   struct Falldown* pF = (struct Falldown*)api;
   pF->m_nSpeedExtra = nSpeedExtra;
   pF->m_nSpeedExtraPartLimit = nSpeedExtraLimit;

   return FALLDOWNLIB_OK;
}

int GetFalldownBallPos(FalldownLib api, int* pnX, int* pnY)
{
   DEBUG_FUNC_NAME;

   struct Falldown* pF = (struct Falldown*)api;
   if( pnX != NULL )
      *pnX = pF->m_nBallPosX;

   if( pnY != NULL )
      *pnY = pF->m_nBallPosY;

   return FALLDOWNLIB_OK;
}

int GetStepIndexForX(FalldownLib api, int nX, int* pnStepX)
{
   DEBUG_FUNC_NAME;

   int nStepWidth = SCREEN_WIDTH / FALLDOWN_ROW_SEGMENTS;
   int x = nX / nStepWidth;
   if( pnStepX != NULL )
      *pnStepX = x;

   return FALLDOWNLIB_OK;
}

int MoveFalldownBall(FalldownLib api, int nChangeX)
{
   DEBUG_FUNC_NAME;

   struct Falldown* pF = (struct Falldown*)api;

   pF->m_nBallPosX += nChangeX;
   if( (pF->m_nBallPosX - (BALL_WIDTH/2)) < 0 )
      pF->m_nBallPosX = (BALL_WIDTH/2);
   if( (pF->m_nBallPosX + (BALL_WIDTH/2)) >= SCREEN_WIDTH )
      pF->m_nBallPosX = (SCREEN_WIDTH-1-(BALL_WIDTH/2));

   return FALLDOWNLIB_OK;
}

int StepFalldown(FalldownLib api)
{
   DEBUG_FUNC_NAME;

   struct Falldown* pF = (struct Falldown*)api;

   int n;

   //Move ball down
   int nAmountToDrop = pF->m_nFallingSpeed;
   int nX = 0;
   GetStepIndexForX(api, pF->m_nBallPosX, &nX);
   for(n=0; n<NUMBER_FALLDOWN_ROWS; n++) {
      int nSpeed = 0;

      int nY = GetFalldownRowY(api, n);
      int nDistanceAway = nY - pF->m_nBallPosY;
      //This line is too far away; either behind or in front to think about.
      if( (nDistanceAway < 0) || (nDistanceAway > pF->m_nFallingSpeed ) ) {
         continue;
      }

      for(nSpeed = 0; nSpeed <= pF->m_nFallingSpeed; nSpeed++) {
         if( nY == (pF->m_nBallPosY+nSpeed) ) {
            if( !IsFalldownRowGap(api, n, nX) ) {
               nAmountToDrop = nSpeed;
               break;
            }
         }
      }
      break;
   }

   //If nothing under it; drop the ball.
   for(n=0; n<nAmountToDrop; n++) {
      if( pF->m_nBallPosY < SCREEN_HEIGHT ) {
         pF->m_nBallPosY++;
      }
   }

   int nAdditionalMove = 0;
   pF->m_nSpeedExtraPart++;
   if( pF->m_nSpeedExtraPart > pF->m_nSpeedExtraPartLimit ) {
      pF->m_nSpeedExtraPart = 0;
      nAdditionalMove = pF->m_nSpeedExtra;
      printf("Moving an additional %d\n", nAdditionalMove);
   }

   //Move rows up
   for(n=0; n<NUMBER_FALLDOWN_ROWS; n++) {
      int nAmountToRiseRows = pF->m_nSpeed + nAdditionalMove;
      int m = 0;
      for(m=0; m<nAmountToRiseRows; m++) {
         int nY = GetFalldownRowY(api, n);
         //If collides with ball; bring ball up
         if( nY == pF->m_nBallPosY && !IsFalldownRowGap(api, n, nX) ) {
            pF->m_nBallPosY--;
         }
         pF->m_Rows[n].m_nY--;
      }
   }

   //Check if need to reset rows
   int nSpacing = GetLineSpacing();
   for(n=0; n<NUMBER_FALLDOWN_ROWS; n++) {
      if( pF->m_Rows[n].m_nY <= (-1 * nSpacing) ) {
         pF->m_Rows[n].m_nY = SCREEN_HEIGHT;
         RandomizeRow(pF->m_Rows[n].m_nRow);
      }
   }

   pF->m_nScore++;

   return FALLDOWNLIB_OK;
}

int IsFalldownGameOver(FalldownLib api)
{
   DEBUG_FUNC_NAME;

   struct Falldown* pF = (struct Falldown*)api;

   return 
#ifndef TESTING_LIVE_FOREVER
      (pF->m_nBallPosY < 0) ? FALLDOWN_GAME_OVER :
#endif
      FALLDOWN_NOT_GAME_OVER;
}

int GetFalldownScore(FalldownLib api)
{
   DEBUG_FUNC_NAME;

   struct Falldown* pF = (struct Falldown*)api;

   return pF->m_nScore;
}

int GetFalldownRowY(FalldownLib api, int nRowIndex)
{
   DEBUG_FUNC_NAME;

   struct Falldown* pF = (struct Falldown*)api;

   return pF->m_Rows[nRowIndex].m_nY;
}

int IsFalldownRowGap(FalldownLib api, int nRowIndex, int nPos)
{
   DEBUG_FUNC_NAME;

   struct Falldown* pF = (struct Falldown*)api;

   return pF->m_Rows[nRowIndex].m_nRow[nPos] == 0;
}



