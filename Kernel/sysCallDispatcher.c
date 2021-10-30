#include <stdint.h>
#include "clock.h"
#include "time.h"
#include <naiveConsole.h>
#include <keyboard.h>
#include <lib.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2
#define RED 4
#define REG_COUNT 17

static char registers[REG_COUNT][20] = {
	"RAX: 0x", "RBX: 0x", "RCX: 0x", "RDX: 0x", "RBP: 0x", "RDI: 0x", "RSI: 0x",
	"R8: 0x", "R9: 0x", "R10: 0x", "R11: 0x", "R12: 0x", "R13: 0x", "R14: 0x",
	"R15: 0x","RSP: 0x","RIP: 0x"};

typedef uint64_t (*SysCallR)(uint64_t, uint64_t, uint64_t, uint64_t); // defino un puntero a funcion SysCallR
// void updateRegs(uint64_t* regs);
// void getRegs(char ** buf);
static long read(unsigned int fd, char * buf, uint64_t count); //deberia ser lo mismo que size_t
static long write(unsigned int fd,char * buf, uint64_t count, char color);
static void clear();
static int splitScreen(int screens, int screen);
static int changeScreen(int screen);
static int getChar(unsigned int ascii);
static void getTime(char * buf);
static long timerTick(void (*f)());
static void getDate(char * buf);

// 32 bytes de vuelco de memoria en p = 4 ints
// static void getMemory(uint32_t * p);

// static uint64_t * regInfoPTR;

static SysCallR sysCalls[255] = {(SysCallR) &read, (SysCallR) &write, (SysCallR) &clear, (SysCallR) &splitScreen, (SysCallR) &changeScreen, (SysCallR)&getChar,(SysCallR)&ncClearLine,(SysCallR)&getTime, (SysCallR)&timerTick, (SysCallR)&set_kb_target, (SysCallR)&getDate};//, (SysCallR) &infoReg, (SysCallR) &getMemory}; // = {(SysCall) &read, (SysCall) &write, ...} //cpuid, reg_info, mem_dump, clock

uint64_t sysCallDispatcher(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t rax) {
    SysCallR sysCall = sysCalls[rax]; // sysCalls es un arreglo de punteros a funcion, me guardo la funcion que corresponde con el valor de rax
    if (sysCall != 0) // si no se encuentra en la lista, al estar inicializado con ceros el arreglo, me devuelve cero
        return sysCall(rdi, rsi, rdx, rcx);
    
    return 0;
}

static void clear() {
    ncClear();
}

static long timerTick(void (*f)()) {
    set_routine(f);
    return ticks_elapsed();
}

static long write(unsigned int fd,char * buf, uint64_t count, char color) {
    if (buf == NULL)
        return -1;
    if (fd == STDERR)
        color = RED;
    else if (fd != STDOUT) {
        return -1;
    }


    int i;
    for (i =0 ; buf[i] && i <count ; i++) {
        switch(buf[i]) {
            case '\n':
                ncNewline();
            break;
            case '\b':
                 ncDelete();
            break;
            default:
                    ncPrintChar(buf[i], color);
        }
    }
    return i > 0 ? i : -1;
}

static long read(unsigned int fd, char * buf, uint64_t count) {
    if (fd != 0)
        return -1; // solo acepta teclado
    return readFromKeyboard(buf, count,1);
}

static int getChar(unsigned int ascii) {
    int a;
         for(int i=0 ; i<1 ; i++) {
          a = kb_read();
          if (ascii && !PRINTABLE(a))
               i--;
     }
     return a;
}

static int splitScreen(int screens, int screen) {
    return ncSplitConsole(screens, screen);
}
static int changeScreen(int screen) {
    return ncChangeScreen(screen);
}

int numToStr(int num, char * str) {
    if (num == 0) {
        str[0] = '0';
        return 1;
    }
	int neg=0;
	if (num<0) {
		str[0]='-';
		str++;
		num=num*(-1);
		neg=1;
	}	
	int i, rem, n, len = 0;
	n = num;
	while (n != 0) {
	  len++;
	  n /= 10;
	}
	for (i = 0; i < len; i++) {
	  rem = num % 10;
	  num = num / 10;
	  str[len - (i + 1)] = rem + '0';
	}
	return len+neg;
}

// void swap(char* a, char* b) {
// 	char aux = *a;
// 	*a = *b;
// 	*b = aux;
// }
// void reverse(char str[], int length)
// {
//     int start = 0;
//     int end = length -1;
//     while (start < end)
//     {
//         swap(str+start, str+end);
//         start++;
//         end--;
//     }
// }

// char* itoa(int num, char* str, int base)
// {
//     int i = 0;
//     int isNegative = 0;
 
//     /* Handle 0 explicitly, otherwise empty string is printed for 0 */
//     if (num == 0)
//     {
//         str[i++] = '0';
//         str[i] = '\0';
//         return str;
//     }
 
//     // In standard itoa(), negative numbers are handled only with
//     // base 10. Otherwise numbers are considered unsigned.
//     if (num < 0 && base == 10)
//     {
//         isNegative = 1;
//         num = -num;
//     }
 
//     // Process individual digits
//     while (num != 0)
//     {
//         int rem = num % base;
//         str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
//         num = num/base;
//     }
 
//     // If number is negative, append '-'
//     if (isNegative)
//         str[i++] = '-';
 
//     str[i] = '\0'; // Append string terminator
 
//     // Reverse the string
//     reverse(str, i);
 
//     return str;
// }

static void getTime(char * buf) {
    buf[0] = buf[3] = buf[6] = '0';
    buf[2] = buf[5] = ':';
    int h = hours();
    if (h<10)
        numToStr(h,&buf[1]);
    else numToStr(h,&buf[0]);

    int m = minutes();

    if (m<10)
        numToStr(m,&buf[4]);
    else numToStr(m,&buf[3]);

    int s = seconds();

    if (s<10)
        numToStr(s,&buf[7]);
    else numToStr(s,&buf[6]);
    buf[8] = 0;
}

static void getDate(char * buf) {
    buf[0] = buf[3] = '0';
    buf[2] = buf[5] = '/';

    int m = month();

    if (m<10)
        numToStr(m,&buf[1]);
    else numToStr(m,&buf[0]);

    int d = day();

    if (d<10)
        numToStr(d,&buf[4]);
    else numToStr(d,&buf[3]);

    int y = year();
    numToStr(y,&buf[6]);
    buf[8] = 0;
}

// void updateRegs(uint64_t* regs) {
//     for (int i=0 ; i<REG_COUNT ; i++) {
//         char * ptr = registers[i][3] == ':' ? &registers[i][7] : &registers[i][6];
//         numToStr(regs[i],ptr);
//     }
        
// }

// void getRegs(char ** buf) {
//         // for (int i=0 ; i<REG_COUNT ; i++) {
//         //     buf[i] = registers[i];
//         // }
// }

// static void getMemory(uint32_t * p) {

// }
