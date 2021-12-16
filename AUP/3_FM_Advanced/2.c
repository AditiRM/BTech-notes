#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>           
#include <errno.h>
#include <dirent.h>
#include <string.h>

void time(struct stat buf, char* syscall){
	printf("Time after %s syscall \n", syscall);
	printf("a_time : %ld\t", buf.st_atime);
	printf("c_time : %ld\t", buf.st_ctime);
	printf("m_time : %ld\n", buf.st_mtime);
}

int main(int argc, char* argv[]){
	int md;
	//Create dir
	md = mkdir(argv[1], 0777);
	
	//Get path
	char* PATH;
	//char* PATH2;
	long max;
	max = pathconf("/", _PC_PATH_MAX);
	PATH = (char*)malloc(max);
	//PATH2 = (char*)malloc(max);
	getcwd(PATH, max);
	strcat(PATH, "/");
	strcat(PATH, argv[1]);
	if( chdir(PATH) == 0);
		printf("PATH : %s\n", PATH);
 
 	//getcwd(PATH2, max);
	//printf("After cat : %s\n",PATH2);


	//now change ownership to user1  - chown
        int set_u = atoi(argv[2]);	
	struct stat statv1;
	if(stat(argv[1], &statv1) < 0)
		perror("stat error");
	chown(PATH, set_u, statv1.st_uid);
	

	//now change mode o+w others write - chmod
	if(chmod(PATH, S_IWOTH) < 0){	
	perror("chmod error");
		exit(1);
	}
	
	//create a file inside that directory
	int fd;
	fd = mknod(argv[3], S_IFREG,0);
	if(fd == 0)
		printf("File created successfully\n");

	//print uid & gid of file & dir
	//argv[3] -> filename
	struct stat buf;
	if(stat(argv[3], &buf) < 0)
		perror("stat error");

	//change owner to user2
        int setuf = atoi(argv[4]);
        chown(PATH, setuf,buf.st_uid);

	printf("File uid : %d\t File gid : %d\n", buf.st_uid, buf.st_gid);
	printf("Dir uid : %d\t Dir gid : %d\n",statv1.st_uid, statv1.st_gid);
	
	//open file/
	fd = open(argv[3], O_RDWR | O_CREAT);
	if(fd == -1)
		perror("Open fail");
	time(buf, "open");
	
	//write into file 
	int size = write(fd, "Hello Aditi\n", strlen("Hello Aditi\n"));
	time(buf, "write");
	
	//access file
	int acc = access(argv[3], F_OK);
	if(acc == -1)
		perror("Error:");
	time(buf, "access");
	
	//chmod file
	char mode[] = "0777";
	int i;
	i = strtol(mode, 0, 8);
	if(chmod (PATH, i) < 0)
		perror("Error");
	
	time(buf, "chmod");

	return 0;
}
