#ifndef LIB_H
#define LIB_H

#include <stdint.h>

#include <stddef.h>

void * memset(void * destination, int32_t character, uint64_t length);
void * memcpy(void * destination, const void * source, uint64_t length);

char *cpuVendor(char *result);

int getRTC(int code);

char kbReadUntilCode();

int keyboardActivated();

int getKbCode();

extern void infoReg(char ** buf);

// extern uint32_t getModuleSize();

// extern void setModuleSize(uint32_t size);


#endif