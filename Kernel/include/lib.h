#ifndef LIB_H
#define LIB_H

#include <stdint.h>

#include <stddef.h>

void * memset(void * destination, int32_t character, uint64_t length);
void * memcpy(void * destination, const void * source, uint64_t length);

char *cpuVendor(char *result);

int getRTC(int code);

// Waits for the next key and returns its scancode
char kbReadUntilCode();

int keyboardActivated();

int getKbCode();

// char* itoa(int num, char* str, int base);

#endif