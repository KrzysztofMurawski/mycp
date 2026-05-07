
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>


char * extract_filename_from_path(char * path);


int main(int argc, char *argv[]){
    if (argc < 3){
        printf("usage: mycp [source_file] [dest_dir]\n");
        return 1;
    }


    char *source_file = argv[1];
    char *dest_dir = argv[2];

    char dest_path[256] = {0};
    strcat(dest_path, dest_dir);
    strcat(dest_path, "/");

    char *src_filename = extract_filename_from_path(source_file);

    strcat(dest_path, src_filename);

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


char * extract_filename_from_path(char * path){
    
    char *src_filename = malloc(32);
    memset(src_filename, 0, 32);
    
    int filename_i = 0;
    for (int i = 0; i < strlen(path); ++i){
        if (path[i] == '/'){
            filename_i = 0;
        }
        src_filename[filename_i] = path[i];
        filename_i++;
    }

    return src_filename;
}