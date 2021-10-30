#include "stdinout.h"
#include "colors.h"
static long tickss;
static long startTicks;
static int lastTick;
static int stopped;;
static int started;;
static int accumTicks;



void initStopWatch() {
    tickss = startTicks = lastTick = stopped = started = accumTicks = 0;
}


void stopWatchStart() {
    int aux = ticks();
    do {
        startTicks = ticks();
    }
    while (startTicks == aux);
    lastTick = startTicks;
    stopped = 0;
    started = 1;
}

int stopWatchChanged() {
    if (!started || stopped)
        return 0;
    tickss = ticks();
    return tickss - lastTick >= 2;
}

// static int numToStr2(int num, char * str) {
// 	    if (num == 0) {
//         str[0] = '0';
//         return 1;
//     }
// 	int neg=0;
// 	if (num<0) {
// 		str[0]='-';
// 		str++;
// 		num=num*(-1);
// 		neg=1;
// 	}	
// 	int i, rem, n, len = 0;
// 	n = num;
// 	while (n != 0) {
// 	  len++;
// 	  n /= 10;
// 	}
// 	for (i = 0; i < len; i++) {
// 	  rem = num % 10;
// 	  num = num / 10;
// 	  str[len - (i + 1)] = rem + '0';
// 	}
// 	return len+neg;
// }

static void twoDigitsNumToStr(int num, char * buf) {
    if (num<10) {
        buf[0] = '0';
        numToStr(num, &buf[1],10);
    }
    else {
        numToStr(num, &buf[0],10);
    }  
}

void stopWatchStop() {
    if (stopped)
        return;
    stopped = 1;
    accumTicks += ticks() - startTicks;
}

void printStopWatch() {
    
    char template[] = "00:00:00,00\n";

    if (!started) {
        print(template);
        return;
    }
    int total_sec, hh, mm, ss, cs;
    lastTick = tickss = ticks();
    long total_ms = (tickss - startTicks + (accumTicks))*55;
    total_sec = total_ms/1000;
    cs = (total_ms % 1000)/100;

    hh = total_sec/3600;
	mm = (total_sec - hh*3600)/60;
	ss = total_sec - hh*3600 - mm*60;

    twoDigitsNumToStr(hh,&template[0]);
    twoDigitsNumToStr(mm,&template[3]);
    twoDigitsNumToStr(ss,&template[6]);
    twoDigitsNumToStr(cs,&template[9]);
    printColor(template,RED);

}