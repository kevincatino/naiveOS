
#include <stdint.h>
#define ZERO_EXCEPTION_ID 0
#define INVALID_OP_EXCEPTION_ID 6

static void zero_division();
static void invalid_op();

void exceptionDispatcher(int exception, uint64_t * regs) {
	switch(exception) {
		case ZERO_EXCEPTION_ID:
		zero_division();
		break;
		case INVALID_OP_EXCEPTION_ID:
		invalid_op();
		break;
	}
	// ACA HABRIA QUE IMPRIMIR LOS REGISTROS QUE SE PASARON EN 'regs' (provienen del pushState en el codigo asm)
}

static void zero_division() {
	// Handler para manejar excepcíon
}

static void invalid_op() {
	// Handler para manejar excepcíon
}