#include "Dri_Timer0.H"
#include "Int_Flowled.h"


void main() 
{
    LED = 0xfe;

    Dri_Timer0_Init();
    Dri_Timer0_Register(Int_Flowled);        

    while(1);
}