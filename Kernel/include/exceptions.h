
#ifndef _EXCEPTIONS_H_
#define _EXCEPTIONS_H_
#include <stdio.h>
#include <naiveConsole.h>

void exceptionHandlerRebootPoint(uint64_t IP, uint64_t SP);


extern uint64_t getStack();

#endif