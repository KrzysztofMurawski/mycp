
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>



int main(int argc, char *argv[]){
    if (argc < 3){
        printf("usage: mycp [source_file] [dest_dir]\n");
        return 1;
    }


    char *source_file = argv[1];
    char *dest_dir = argv[2];

    char dest_path[256] = {0};
    strcat(dest_path, dest_dir);
    strcat(dest_path, source_file);

    int source_fd = open(source_file, O_RDONLY);
    if (source_fd < 0){
        perror("Open Source File");
        return 1;
    }

    int dest_fd = creat(dest_path, 0777);
    if (dest_fd < 0){
        perror("Open Destination File");
        return 1;
    }
    
    ssize_t bytes_read = 0;

    while(1){

        char buffer[64] = {0};
        bytes_read = read(source_fd, buffer, sizeof(buffer));
        if (bytes_read == 0){
            break;
        } else if (bytes_read < 0){
            perror("Reading");
            return 1;
        }

        int total_written = 0;

        while (bytes_read > total_written){

            ssize_t bytes_written = write(dest_fd, buffer, sizeof(buffer));
            if (bytes_written < 0){
                perror("Writing to file");
                return 1;
            }

            total_written = total_written + bytes_written;
        }


    }



    close(dest_fd);
    close(source_fd);
    return 0;
}


