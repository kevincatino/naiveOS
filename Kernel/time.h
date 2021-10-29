#ifndef _TIME_H_
#define _TIME_H_

#include "naiveConsole.h"

void timer_handler();
int ticks_elapsed();
int seconds_elapsed();
void set_routine(void (*f)());
void setPointer(uint8_t ptr);
#endif
