#include <stdint.h>
#include <videoD.h>
#include "lib.h"

#define SECONDS 0
#define MINUTES 2
#define HOURS 4
#define DAY 7
#define MONTH 8
#define YEAR 9
#define TIMEZONE_DIFF -3
#define DATETIME_LENGTH (DATE_LENGTH + 3 + TIME_LENGTH)
#define TIME_LENGTH 8
#define DATE_LENGTH 10 


int BCDToDecimal(uint64_t value) {
    return ((value & 0xF0) >> 4) * 10 + (value & 0x0F);
}

unsigned int seconds() {
    return BCDToDecimal(getRTC(SECONDS));
}

unsigned int minutes() {
    return BCDToDecimal(getRTC(MINUTES));
}

unsigned int hours() {
    return BCDToDecimal(getRTC(HOURS))+TIMEZONE_DIFF;
}

unsigned int day() {
    return BCDToDecimal(getRTC(DAY));
}

unsigned int month() {
    return BCDToDecimal(getRTC(MONTH));
}

unsigned int year() {
    return BCDToDecimal(getRTC(YEAR));
}





