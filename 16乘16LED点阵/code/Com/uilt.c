#include "uilt.h"

void Delay1ms(unsigned int n)
{
    // Implementation for 1ms delay
    unsigned int i, j;
    for(i = 0; i < n; i++)
        for(j = 0; j < 50; j++);
}