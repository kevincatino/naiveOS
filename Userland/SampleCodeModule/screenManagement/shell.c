

#include "shell.h"

int cmdIndex(char * buf);
void processCommands(char * buf, char shellBuffer[][SHELLW], int lines);
void loadCommand(void (*f)(), char *name, char *desc);

static char buffer1[32] = { 0 };
static char buffer2[32] = { 0 };
int buf1Size = 0;
int buf2Size = 0;
static char consoleMsg1 [80] = {0};
static char consoleMsg2 [80] = {0};
char * consoleMsg = consoleMsg1;
static uint8_t * const video = (uint8_t*)0xB8000;
static const uint32_t width = 80;
static const uint32_t height = 25;
static int cmdCounter = 0;
int currentShell = 0;
static int flag = 1;

typedef struct
{
    char line[SHELLW];
    int isCmd;
} shell_line;

static char shellBuffer1[SHELLH][SHELLW];
static char shellBuffer2[SHELLH][SHELLW];

// static shell_line shellBuffer1[SHELLH];
// static shell_line shellBuffer2[SHELLH];

static int buffer1Lines = 0;
static int buffer2Lines = 0;

static int kb = 0;

typedef struct
{
    void (*shellf)(int argSize, char *args[]);
    char *name;
    char *description;
    // int builtIn; //flag for declaring if the function is built in.
} t_shellc;

static t_shellc shellCommands[10] = {{0,0,0}};




void printShell(char * buffer, char shellBuffer[SHELLH][SHELLW]) {
    for (int i = 0 ; i < SHELLH ; i++) {
        if (shellBuffer[i][0] == 0)
            putChar('\n');
        else {
            printColor(SHELL_MSG,SHELL_COLOR);
            print(shellBuffer[i]);
            putChar('\n');
        }  
    }
    print(consoleMsg);
    //consoleMsg[0]=0;
    putChar('\n');

    printColor(SHELL_MSG,SHELL_COLOR);
    print(buffer);
    
}

void updateConsoleMsg(char * s) {
    strcpy(consoleMsg,s);
}



void printHola() {
    updateConsoleMsg("Hola");
}

void printDateTime() {
    char buf[20] = {0};
    get_date(buf);
    buf[8] = buf[10] = ' ';
    buf[9] = '-';
    get_time(&buf[11]);
    updateConsoleMsg(buf);
}

void help() {
    
}


void setupShellCommands() {
    loadCommand(&printHola,"HolaP", "Printea Hola");
    loadCommand(&multipleWindows,"multiple", "starts multiple window environment");
    loadCommand(&printDateTime,"datetime", "displays the date and time");
    loadCommand(&help,"datetime", "displays the date and time");
}

void loadCommand(void (*f)(), char *name, char *desc)
{
    shellCommands[cmdCounter].shellf = f;
    shellCommands[cmdCounter].name = name;
    shellCommands[cmdCounter].description = desc;
    // shellCommands[cmdCounter].builtIn = builtIn;
    cmdCounter++;
}

void processCommands(char * buf, char shellBuffer[SHELLH][SHELLW], int lines) {
    for (int i=1 ; i<SHELLH ; i++) {
        strcpy(shellBuffer[i-1], shellBuffer[i]);
    }

    strcpy(shellBuffer[SHELLH-1], buf);

    int idx = cmdIndex(buf);
    buf[0]=0;
    if (idx < 0) {
        updateConsoleMsg("Comando invalido");
        return;
    }
    shellCommands[idx].shellf(0,0);
}

void cleanBuffers() {
    for (int i=0 ; i<SHELLH ; i++)
        shellBuffer1[i][0] = 0;
    for (int i=0 ; i<SHELLH ; i++)
        shellBuffer2[i][0] = 0;
    consoleMsg1[0] = consoleMsg2[0] = 0;
}

void manageConsole(char bufferIn[SHELLH][SHELLW], char * buf, int* bufSize, char * consoleMsgC, int bufferLines) {
        consoleMsg = consoleMsgC;
        console_clear();
        printShell(buf, bufferIn);
        if(readInput(buf, bufSize, SHELL_MSG,GREEN,30)) {
            return;
        }
        flag = 1;
        processCommands(buf, bufferIn, bufferLines);
        // console_clear();
        // printShell(bufferIn);
}

int theShell() {
    cleanBuffers();
    setupShellCommands();
    set_kb_target(&kb);
    console_clear();
    split_screen(2,0);
    // print(levels[0]);
    // while(1);
    while(1) {
        int previous = currentShell;
        set_screen(currentShell);
        switch(currentShell) {
            case 0:
                manageConsole(shellBuffer1, buffer1, &buf1Size, consoleMsg1, buffer1Lines);
                break;
            case 1:
                manageConsole(shellBuffer2, buffer2, &buf2Size, consoleMsg2, buffer2Lines);
                break;
        }
    }
}

int readInput(char *buffer, int* size, char * def, char color, int maxSize)
{
    int begin=1, c;
    
    while ((*size) < (maxSize - 1) && ((c = getRealChar()) != '\n')  && (c != UP_ARROW) && (c != DOWN_ARROW))
    { 
        if (begin) {
            clear_line();
            printColor(def, color);
            print(buffer);
            begin=0;
        }

            if (c != '\b' && PRINTABLE(c))
            {
                putChar(c);
                buffer[(*size)++] = c;
            }
            else if (c == '\b' && (*size) > 0) // solo borro si escribi algo
            {
                putChar('\b');
                (*size)--;
            }
            c=0;
    }
    if (c == UP_ARROW || c == DOWN_ARROW) {
        currentShell = currentShell == 0 ? 1 : 0;
        buffer[(*size)] = 0;
        return c - 500;
    }
    buffer[(*size)] = 0;
    putChar('\n');
    (*size) = 0;
    return 0;
}

// retorna -1 si el buffer no tiene ningun comando valido
int cmdIndex(char * buf) {


    for (int i = 0 ; i < cmdCounter ; i++) {
        if (strcmp(buf,shellCommands[i].name)==0)
            return i;
    }
    return -1;
}



