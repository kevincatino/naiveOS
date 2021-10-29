#include "time.h"
#include <stdint.h>
#include "naiveConsole.h"
#include "lib.h"
#include "interrupts.h"
#include "keyboard.h"

typedef void (*IRQHandlerR)();

static void int_20();
static void int_21();
static IRQHandlerR handlers[8] = {(IRQHandlerR) &int_20, (IRQHandlerR) &int_21};

void irqDispatcher(uint64_t irq) {
	IRQHandlerR irqHandler = handlers[irq];

	if (irqHandler != 0)
		irqHandler();
}

void int_20() {
	//ncPrint("timer");
	 timer_handler();
}

void int_21() {
	keyboardDriver();
}


