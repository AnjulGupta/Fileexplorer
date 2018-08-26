#include "normal_mode.h"

using namespace std;

struct termios c_mode;

void enter_normal_mode() {
  //tcgetattr(STDIN_FILENO,&struct termios) , STDIN_FILENO=0
  tcgetattr(0, &c_mode);

  struct termios n_mode = c_mode;
  n_mode.c_lflag &= ~( ECHO);  //for preventing  characters on output
  n_mode.c_lflag &= ~(ICANON); // for entering non-canonical mode

  //tcsetattr(STDIN_FILENO,TCSANOW,&struct termios)
  tcsetattr(0, TCSANOW, &n_mode);

  //atexit(exit_normal_mode);
     
}

void exit_normal_mode() {
  //tcsetattr(STDIN/OUT/ERROR_FILENO,TCSANOW,&struct termios) 
   tcsetattr(0,TCSANOW, &c_mode);
}


