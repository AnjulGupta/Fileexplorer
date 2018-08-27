#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <dirent.h>             // fdopendir(fd) , readdir(DIR *dp) 
#include <fcntl.h>              //open(path,mode)
#include <sys/stat.h>           //int stat(const char *restrict pathname, struct stat *restrict buf )
#include <pwd.h> 
#include <grp.h>
#include <time.h>               //asctime(),localtime()
#include <unistd.h>

using namespace std;
int main()
{

//  //int open(const char *path, int oflags);
   int fd= open("/home/anjul/Documents/Fileexp",O_RDONLY);   // mode 'O_RDWR' not working may be becoz of we cannot modify dir
// // cout<<fd;
DIR *fdopendir(int fd);
DIR *d;
 d= fdopendir(fd);
  // d=opendir("/home/anjul/Documents");
//struct dirent *readdir(DIR *dp);  
  struct dirent *dir;

  struct stat stbuff;
  struct passwd  *pwd_id;
  struct group   *grp_id;

  struct tm *tm;
  char  datestring[64];

  //int stbuff.st_mode;
 //cout<<"-");
  

  if(d)
  {
    //write(1, "\x1b[2J", 4);  this not working 
    cout<<"\033[H\033[J";  

  	while((dir=readdir(d))!=NULL )
  {

   if(stat(dir->d_name,&stbuff)!=-1 && (pwd_id = getpwuid(stbuff.st_uid)) != NULL && ((grp_id = getgrgid(stbuff.st_gid)) != NULL))
        cout<<setw(10)<<dir->d_name<<"\t"<<stbuff.st_mode<<"\t"<<pwd_id->pw_name<<"\t"<<grp_id->gr_name<<"\t";
       if(stat(dir->d_name,&stbuff)==0)
            cout<<setw(4)<<stbuff.st_size<<" bytes \t";
        
        
        

  //------------
  //file f or Directory d
       if (S_ISREG(stbuff.st_mode))		
          cout<<"F ";
        else if (S_ISDIR(stbuff.st_mode))  
          cout<<"D ";
        else if (S_ISCHR(stbuff.st_mode))
          cout<<"C ";
        else if (S_ISBLK(stbuff.st_mode))
          cout<<"B ";
  		else if (S_ISLNK(stbuff.st_mode))
  			cout<<"S ";
  		else
  			cout<<" ";
  		//---------------------------------
 //struct stat fileattrib;
   
        
        if ((stbuff.st_mode & S_IRUSR) && (stbuff.st_mode & S_IREAD))
          cout<<"r";
        else
          cout<<"-";
        if ((stbuff.st_mode & S_IWUSR) && (stbuff.st_mode & S_IWRITE)) 
          cout<<"w";
        else
          cout<<"-";
        if ((stbuff.st_mode & S_IXUSR) && (stbuff.st_mode & S_IEXEC))
          cout<<"x";
        else
          cout<<"-";
       

        if ((stbuff.st_mode & S_IRGRP) && (stbuff.st_mode & S_IREAD))
          cout<<"r";
        else
          cout<<"-";
        if ((stbuff.st_mode & S_IWGRP) && (stbuff.st_mode & S_IWRITE))
          cout<<"w";
        else
          cout<<"-";
        if ((stbuff.st_mode & S_IXGRP) && (stbuff.st_mode & S_IEXEC))
          cout<<"x";
        else
          cout<<"-";
      
//-------------------  		
        cout<<"\t"; 
        tm = localtime(&stbuff.st_mtime);
        cout<<asctime(tm);
     
  	}


  	cout<<"\n";
 } 

write(1, "\x1b[H", 3);
 
closedir(d); 


return 0;	
}