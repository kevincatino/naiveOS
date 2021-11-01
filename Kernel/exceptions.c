
#include <stdint.h>
#include <naiveConsole.h>
#include <clock.h>

#define ZERO_EXCEPTION_ID 0
#define INVALID_OP_EXCEPTION_ID 6
#define RED_COLOR 4

// static char registers[16][20] = {
// 	"RAX: 0x", "RBS: 0x", "RCX: 0x", "RDX: 0x", "RBP: 0x", "RDI: 0x", "RSI: 0x",
// 	"R8: 0x", "R9: 0x", "R10: 0x", "R11: 0x", "R12: 0x", "R13: 0x", "R14: 0x",
// 	"R15: 0x"};

// static uint64_t * regInfoPTR;

static void zero_division();
static void invalid_op();
extern void infoReg(char ** buf);

static uint64_t * restoreIp = 0x400000;


void exceptionDispatcher(int exception, uint64_t * regs) {
	switch(exception) {
		case ZERO_EXCEPTION_ID:
		zero_division();
		break;
		case INVALID_OP_EXCEPTION_ID:
		invalid_op();
		break;
	}
	int s = seconds();
	// ACA HABRIA QUE IMPRIMIR LOS REGISTROS QUE SE PASARON EN 'regs' (provienen del pushState en el codigo asm)

	char * buf[17];
	infoReg(buf);
	for (int i=0 ; i<17 ; i++) {
		ncPrint(buf[i]);
		ncNewline();
	}

	while(seconds() - s < 3 && seconds() >= s);

	regs[15] = restoreIp; // pisamos el RET con la direccion de ip para restaurarlo
	
	
}

static void zero_division() {
	// Handler para manejar excepcíon
	ncSplitConsole(1,0);
	ncClear();
	ncPrintColor("Exception: division by zero",RED_COLOR);
	ncNewline();
}

static void invalid_op() {
	// Handler para manejar excepcíon
	ncSplitConsole(1,0);
	ncClear();
	ncPrintColor("Exception: invalid operation code",RED_COLOR);
	ncNewline();
}