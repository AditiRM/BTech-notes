#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>           
#include <errno.h>
#include <dirent.h>

int main(int argc, char* argv[]){
	int i;
	struct stat buf;

	struct dirent *direntp;
	DIR *dirp;

	dirp = opendir(argv[1]);

	while((direntp = readdir(dirp)) != NULL){
		printf("File : %s\t", direntp->d_name);
		if(stat(direntp->d_name, &buf) < 0 ){
			perror("stat error");
		}

		struct passwd *pw = getpwuid(buf.st_uid);
		if(pw != 0)
			printf("Owner = %s\t", pw->pw_name);

		printf("dev = %ld\t", buf.st_dev);
		printf("rdev = %ld\t", buf.st_rdev);
	
		//Check all modes & add switch case
		if ((buf.st_mode & S_IFMT) == S_IFREG) {
        	       printf("file type(mode) = Regular\n\n");
	        }	
		if ((buf.st_mode & S_IFMT) ==  S_IFDIR) {
                       printf("file type(mode) = Directory\n\n");
                }  
		if ((buf.st_mode & S_IFMT) == S_IFLNK) {
                       printf("file type(mode) = Symbolic Link\n\n");
                }


	}
	closedir(dirp);
	return 0;
}
