
#include"normal_mode.h"
#include<iostream>




using namespace std;

int main() {

  enter_normal_mode();
  char ch;
  while (read(0, &ch, 1) == 1 && ch != ':');
  cout<<"\033[H\033[J";  
  atexit(exit_normal_mode);
  
  return 0;
}

