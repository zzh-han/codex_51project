#ifndef BUZZER_H
#define BUZZER_H

#include "uilt.h"
#include <STC89C5xRC.H>

sbit BUZZER = P2^5; // Buzzer pin

void buzzer_Int(void);

#endif // BUZZER_H