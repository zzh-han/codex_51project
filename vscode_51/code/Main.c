#include <STC89C5xRC.H>

void Delay1ms(unsigned int n)
{
    unsigned int i, j;
    for(i = 0; i < n; i++)
        for(j = 0; j < 120; j++);
}

void main() 
{
    unsigned char i = 1;
    bit direction = 1;

    while(1)
    {   
        P0 = ~i;

        if(direction == 1)
        {
            i = i<<1;
        }
        else 
        {
            i = i>>1;
        }
        Delay1ms(100);

        if(i == 0x80)
            direction = 0;
        if(i == 0x01)
            direction = 1;
    }    
}