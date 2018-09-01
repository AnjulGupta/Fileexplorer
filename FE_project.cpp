
#include"normal_mode.h"

using namespace std;

int main() {

  enter_normal_mode();
 
  cout<<"\033[H\033[J";  //for clearing screen
  
  atexit(exit_normal_mode);  
  
  return 0;
}

