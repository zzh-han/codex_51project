#include "buzzer.h"
#include "Dri_Timer0.h"



void main()
{
    Dri_Timer0_Init();
    Dri_Timer0_Register(buzzer_Int);

    while (1)
    {
        /* code */
    }
}

