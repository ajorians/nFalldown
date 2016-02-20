#ifndef FALLDOWNLIB_H_INCLUDED
#define FALLDOWNLIB_H_INCLUDED

typedef void* FalldownLib;

#define FALLDOWNLIB_OK			(0)
#define FALLDOWNLIB_BADARGUMENT		(-1)
#define FALLDOWNLIB_OUT_OF_MEMORY	(-2)

#define FALLDOWN_GAME_OVER		(1)
#define FALLDOWN_NOT_GAME_OVER		(0)

#define NUMBER_FALLDOWN_ROWS    	(4)
#define FALLDOWN_ROW_SEGMENTS   	(16)

//////////////////////////////////////////////
//Initalization/Error checking/Mode functions
//////////////////////////////////////////////
int FalldownLibCreate(FalldownLib* api);
int FalldownLibFree(FalldownLib* api);

int GetFalldownLibError(FalldownLib api);
void ClearFalldownLibError(FalldownLib api);

//////////////////////////////////////////////
//FalldownLib related functions
//////////////////////////////////////////////
int AdjustFallDownSpeed(FalldownLib api, int nSpeed);
int AdjustFallDownExtraSpeed(FalldownLib api, int nSpeedExtra, int nSpeedExtraLimit);
int GetFalldownBallPos(FalldownLib api, int* pnX, int* pnY);
int GetStepIndexForX(FalldownLib api, int nX, int* pnStepX);
int MoveFalldownBall(FalldownLib api, int nChangeX);
int StepFalldown(FalldownLib api);
int IsFalldownGameOver(FalldownLib api);
int GetFalldownScore(FalldownLib api);
int GetFalldownRowY(FalldownLib api, int nRowIndex);
int IsFalldownRowGap(FalldownLib api, int nRowIndex, int nPos);

#endif //FALLDOWNLIB_H_INCLUDED
