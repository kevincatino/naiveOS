#ifndef _clock_
#define _clock_

#define SECONDS 0
#define MINUTES 1
#define HOURS 4
#define DAY 7
#define MONTH 8
#define YEAR 9

int BCDToDecimal(uint64_t value);

unsigned int seconds();

unsigned int minutes();

unsigned int hours();

unsigned int day();

unsigned int month();

unsigned int year();

#endif