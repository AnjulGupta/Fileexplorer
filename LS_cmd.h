#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <dirent.h>             // fdopendir(fd) , readdir(DIR *dp) 
#include <fcntl.h>              //open(path,mode)
#include <sys/stat.h>           //int stat(const char *restrict pathname, struct stat *restrict buf )
#include <pwd.h>                //struct passwd, getpwuid() 
#include <grp.h>                //struct grp, getgrgid()  
#include <time.h>               //asctime(),localtime()
#include <unistd.h>             //Standard streams


void LS_cmd ();
