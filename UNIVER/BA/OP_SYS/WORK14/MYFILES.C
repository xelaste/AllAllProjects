/*  myfiles User_Name Directory_Name - lists directory content */
/* that belong to User_Name                                    */
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <limits.h>
#include <pwd.h>

#define FILE_NAME_FIELD "%-60s"/*  picture of path name for print   */
#define MAX_PATH  60       /* Max expected length of full path name */
#define ERROR_EXIT 1

DIR *dp;               /* see man readdir */  
struct dirent *dirp;   /* see man readdir */  
struct stat sb;        /* see man stat */
char fullpath[MAX_PATH];
int path_len;
main(int argc, char *argv[])
{
  struct passwd *pwd ;/*record user data */
  if ( argc!=3 ) {                      
     printf( "Usage: %s User name Directory\n", argv[0] );
     exit(0);
  }
  if((pwd=getpwnam(argv[1]))==NULL)
    {
    perror(argv[1]);
    exit(ERROR_EXIT);
    }
   if ( ( dp=opendir(argv[2] ) ) == NULL ) {
      perror( argv[2]);
      exit( ERROR_EXIT );
  }
  strcpy( fullpath,argv[2] );
  if ( strcmp( fullpath,"/" )!=0 )
                     strcat( fullpath,"/" );
  path_len=strlen( fullpath );
  while (( dirp= readdir(dp) ) != NULL )  /* Read directory */
  {
      fullpath[path_len]='\0';
      strcat( fullpath,dirp->d_name );    /* Restore absolute path */
      if ( lstat( fullpath, &sb ) < 0 ) {  /* Get file and link status */
         perror( fullpath );               
         continue;
      }
      if(sb.st_uid==pwd->pw_uid)
        {
         printf( FILE_NAME_FIELD,fullpath );
         switch ( sb.st_mode & S_IFMT ) 
           {
             case S_IFREG: printf(" Regular file\n"); continue;
             case S_IFDIR: printf(" Directory\n");    continue;
             case S_IFLNK: printf(" Link\n");         continue; 
             default:      printf(" Special file\n");
            }
          }
  }
  closedir(dp);
}
