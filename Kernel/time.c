#include <time.h>
#include "stdint.h"
#include "naiveConsole.h"

static unsigned long ticks = 0;
static unsigned long prevTicks = 0;
void (*routine)() = 0;

void timer_handler() {
	ticks++;
	// if (ticks - prevTicks > 5 && routine) {
	// 	uint8_t * videoAux = pointer();
	// 	routine();
	// 	setPointer(videoAux);
	// 	prevTicks = ticks;
	// }
		
}

void set_routine(void (*f)()) {
	routine = f;
}

int ticks_elapsed() {
	return ticks;
}

int seconds_elapsed() {
	return ticks / 18;
}
