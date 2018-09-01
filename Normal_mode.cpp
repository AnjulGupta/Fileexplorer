#include "normal_mode.h"
using namespace std;

static struct termios c_mode,n_mode;

static int check_key_press=-1; 
char ch;
int count;


int readch()
{

ch = check_key_press;
return ch;
read(0,&ch,1);

}




int keymove()
{

n_mode.c_cc[VMIN]=0;    // vmin =0, when ch pressed

tcsetattr(0, TCSANOW, &n_mode);  // configure terminal attribute for 0(stdfilein)

int keyread;
keyread = read(0,&ch,1);   //reading ch pressed

n_mode.c_cc[VMIN]=1;         
tcsetattr(0, TCSANOW, &n_mode);
if(keyread == 1) {
check_key_press = ch;
return 1;
}
return 0;
}


void LS_cmd()
{

char curr_dir[512];
getcwd(curr_dir,sizeof(curr_dir));
 
//int open(const char *path, int oflags);
int fd= open(curr_dir,O_RDONLY);   // mode 'O_RDWR' not working may be becoz of we cannot modify dir

//DIR *fdopendir(int fd);
DIR *d;       //for opening current dir
d= fdopendir(fd);

//struct dirent *readdir(DIR *dp);  
struct dirent *dir;       //for traversing dir
struct stat stbuff;       //for getting file and sir atributes
struct passwd  *pwd_id;   //for user permissions
struct group   *grp_id;   //for group permissions
struct tm *tm;            //for last modification time
  
  

 if(d)
 {
    
    cout<<"\033[H\033[J";      //for clearing screen  //write(1, "\x1b[2J", 4);  this not working 

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
  			cout<<"U";

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

write(1, "\x1b[H", 3);   //moving cursor to top left

while (ch != ':')
  {

    if(keymove())
     {
        ch = readch();

         if(ch==65)               //moving cursor down
         {
             printf("\33[%dA",1);
             fflush(stdout);
              
         }
         else if(ch==66)          //moving cursor up
         {
             printf("\33[%dB",1);
             fflush(stdout);
             
         }

    }

 }

  closedir(d);
}



void enter_normal_mode()       //normal mode =non canonical mode
{
  //tcgetattr(STDIN_FILENO,&struct termios) , STDIN_FILENO=0
  tcgetattr(0, &c_mode);

  struct termios n_mode = c_mode;
  n_mode.c_lflag &= ~( ECHO);  //for preventing  characters on output
  n_mode.c_lflag &= ~(ICANON); // for entering non-canonical mode

  n_mode.c_lflag &= ~ISIG;
  n_mode.c_cc[VMIN] = 1;
  n_mode.c_cc[VTIME]= 0;
  
  //tcsetattr(STDIN_FILENO,TCSANOW,&struct termios)
  tcsetattr(0, TCSANOW, &n_mode);

  LS_cmd();

     
}



void exit_normal_mode() 
{
  //tcsetattr(STDIN/OUT/ERROR_FILENO,TCSANOW,&struct termios) 
   tcsetattr(0,TCSANOW, &c_mode);
}


