#include <os.h>
#include "Defines.h"

int HS_Min(int a, int b) { return a<b ? a : b; }

int HS_NumberOfDigits(int n)//Very quickly thrown together
{
        if( n == 0 )
                return 1;
        int nDigits = 0;
        while(n/10 > 0 || n%10 > 0)
        {
                nDigits++;
                n/=10;
        }
        return nDigits;
}

void HS_itoa(int n, char buffer[], int nBufferSize)//Very quickly thrown together
{
        int i=2;
        nBufferSize = HS_Min(nBufferSize, HS_NumberOfDigits(n)+1);
        for(; i<=nBufferSize; i++)
        {
                int nRemainder = n%10;
                buffer[nBufferSize-i] = '0' + nRemainder;
                n/=10;
        }
        buffer[nBufferSize-1] = '\0';
}

