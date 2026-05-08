
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define READ_BUFF_SIZE 64

char * extract_filename_from_path(char * path);


int main(int argc, char *argv[]){
    if (argc < 3){
        printf("usage: mycp [source_file] [dest_dir]\n");
        return 1;
    }

    char *source_file = argv[1];
    char *dest_dir = argv[2];

    char *src_filename = extract_filename_from_path(source_file);
  
    const ssize_t max_dest_path_len = strlen(src_filename) + strlen(dest_dir) + 2;

    char *dest_path = malloc(max_dest_path_len);
    memset(dest_path, 0, max_dest_path_len);
    strcat(dest_path, dest_dir);
    strcat(dest_path, "/");
    strcat(dest_path, src_filename);


    int source_fd = open(source_file, O_RDONLY);
    if (source_fd < 0){
        perror("Open Source File");
        return 1;
    }

    int dest_fd = creat(dest_path, 0644);
    free(dest_path);
    if (dest_fd < 0){
        close(source_fd);
        perror("Open Destination File");
        return 1;
    }
    

    ssize_t bytes_read = 0;
    char *buffer = malloc(READ_BUFF_SIZE);

    while(1){

        // memset(buffer, 0, READ_BUFF_SIZE);

        bytes_read = read(source_fd, buffer, sizeof(buffer));
        if (bytes_read == 0){
            break;
        } else if (bytes_read < 0){
            perror("Reading");
            close(source_fd);
            close(dest_fd);
            return 1;
        }

        int total_written = 0;

        while (bytes_read > total_written){

            ssize_t bytes_written = write(dest_fd, buffer + total_written, sizeof(buffer) - total_written);
            if (bytes_written < 0){
                perror("Writing");
                close(source_fd);
                close(dest_fd);
                return 1;
            }

            total_written = total_written + bytes_written;
        }


    }


    close(dest_fd);
    close(source_fd);
    return 0;
}


char * extract_filename_from_path(char * path){
    char * slash = strrchr(path, '/');
    if (slash) return slash;
    return path;
}