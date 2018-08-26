#include <iostream>
#include <unistd.h>         //STDIN_FILENO
#include <termios.h>        // struct termios, tcgetattr(), tcsetattr(), TCSAFLUSH
#include <stdlib.h>         //atexit(void func)


void enter_normal_mode();
void exit_normal_mode();



