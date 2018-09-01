// normal mode
#include <iostream>
#include <unistd.h>             //STDIN_FILENO
#include <termios.h>            // struct termios, tcgetattr(), tcsetattr(), TCSAFLUSH
#include <stdlib.h>             //atexit(void func)

#include <iomanip>
#include <stdio.h>
#include <dirent.h>             // fdopendir(fd) , readdir(DIR *dp) 
#include <fcntl.h>              //open(path,mode)
#include <sys/stat.h>           //int stat(const char *restrict pathname, struct stat *restrict buf )
#include <pwd.h>                //struct passwd, getpwuid() 
#include <grp.h>                //struct grp, getgrgid()  
#include <time.h>               //asctime(),localtime()



void LS_cmd ();

void enter_normal_mode();
void exit_normal_mode();

int keymove();
int readch();


