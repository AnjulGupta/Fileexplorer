# include "LS_cmd.h"

using namespace std;

void LS_cmd()
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
  

  if(d)
  {
    //write(1, "\x1b[2J", 4);  this not working 
    cout<<"\033[H\033[J";      //this working fine but y

  	while((dir=readdir(d))!=NULL )
  {

// f OR d name, st_mode, user, group, last modified
   if(stat(dir->d_name,&stbuff)!=-1 && (pwd_id = getpwuid(stbuff.st_uid)) != NULL && ((grp_id = getgrgid(stbuff.st_gid)) != NULL))
        cout<<setw(10)<<dir->d_name<<"\t"<<stbuff.st_mode<<"\t"<<pwd_id->pw_name<<"\t"<<grp_id->gr_name<<"\t";
       if(stat(dir->d_name,&stbuff)==0)
            cout<<setw(4)<<stbuff.st_size<<" bytes \t";
        
        
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

   //file permisisons        
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
      
   // modified time
        cout<<"\t"; 
        tm = localtime(&stbuff.st_mtime);
        cout<<asctime(tm);
     
  	}


  	cout<<"\n";
 } 

write(1, "\x1b[H", 3);
 
closedir(d); 
	
}