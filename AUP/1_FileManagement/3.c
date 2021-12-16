#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include <stdlib.h>
#include <sys/types.h>

#define MIN(a, b) ( (a) < (b) ? (a) : (b))
#define BUFFER_SIZE 1024
#define READ_CHARS 10

/*    
 *  cp_modified
 *  param[1] - source filename,
 *  param[2] - target filename,
 *  param[3] - start position
 *  param[4] - number of bytes to be copied from source to target
 *  return value -  number of bytes written successfully to the target file
 */

int cp_modified(char *source_filename,
                char *target_filename,
                int start_position,
                int number_of_bytes) {
        
        //fs : file descriptor for source file
        //ft : file descriptor for target file
        int fs, ft;
        int count, return_value;

        int total_count = 0;
        char buffer[BUFFER_SIZE];

        //if source_file open failed -> return -1 & end of discussion!
        if ((fs = open(source_filename, O_RDONLY)) == -1) {
            //printf("fs : %d\n", fs);
            return_value = fs;
            return return_value;
        }

        //if target_file open failed -> close source_file.
        if ((ft = open(target_filename, O_CREAT | O_WRONLY | O_TRUNC , 0777)) == -1) {
            return_value = -1;
            close(fs);
        }

        if ((return_value = lseek(fs, start_position, SEEK_SET)) == -1){
            close(ft);
        }

        while((count = read(fs, buffer, MIN(number_of_bytes - total_count, BUFFER_SIZE))) == BUFFER_SIZE) {
            if ((return_value = write(ft, buffer, count)) == -1)
                close(ft);
            total_count += count;
        }

        //CASE : Nothing wriiten on target file afer "write"!
        if (count == -1){
            close(ft);
        }

        if ((return_value = write(ft, buffer, count)) != count){
            if(return_value == -1){
                close(ft);
            }
        }

        close(fs);
        close(ft);

        total_count += return_value;

        return total_count;
}

int main(int argc, char *argv[]){
    if (argc != 5) {
        fprintf(stderr, "USAGE : cpmod <source> <target> <start_position> <number_of_bytes>\n");
        return EINVAL;
    }

    int start, number_of_bytes;
    start = atoi(argv[3]);
    number_of_bytes = atoi(argv[4]);

    int return_cp;
    if ((return_cp = cp_modified(argv[1], argv[2], start, number_of_bytes)) != number_of_bytes) {
        if (return_cp == -1) {
            fprintf(stderr, "%s, %s", argv[1], argv[2]);
            perror("");
            return errno;
        }
        else {
            fprintf(stderr, "Only %d bytes copied out of %d bytes!\n", return_cp, number_of_bytes);
            return 1;
        }
    }

    return 0;
}
