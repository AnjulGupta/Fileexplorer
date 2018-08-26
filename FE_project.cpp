#include"normal_mode.h"
//#include"module2.h"
#include<iostream>

using namespace std;

int main() {

  enter_normal_mode();
  char ch;
  while (read(0, &ch, 1) == 1 && ch != ':');

  atexit(exit_normal_mode);
  
  return 0;
}

