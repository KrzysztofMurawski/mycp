
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char *argv[]){
    
    if (argc < 3){
        printf("help message: mycp [source_file] [dest_dir]\n");
        return 0;
    }

    char source_file[32];
    char dest_dir[32];
    strcat(source_file, argv[1]);
    strcat(dest_dir, argv[2]);

    printf("src dest / %s %s\n", source_file, dest_dir);
    
    int source_fd = open(source_file, O_RDONLY);
    if (source_fd < 0){
        perror("Open Source File");
        return 1;
    }


    char dest_path[256];
    char filename[32];
    // int i = 11;//sizeof(argv[1]);
    // printf("%s\n", argv[1]);
    // while(i > 0 && source_file[i] != '/'){
    //     printf("> %s\n", source_file[i]);
    //     --i;
    // }
    // int j = i;
    // while (j < sizeof(source_file)){
    //     filename[j-i] = source_file[j];
    //     ++j;
    // }
    // printf("%d %s\n", i, filename);


    strcat(dest_path, dest_dir);
    strcat(dest_path, source_file);
    printf("%s\n", dest_path);
    int dest_fd = creat(dest_path, O_CREAT); // no such file or dir...
    if (dest_fd < 0){
        perror("Open Destination File");
        return 1;
    }



    if (close(dest_fd) != 0){
        perror("Closing Destination File");
        return 1;
    };
    if (close(source_fd) != 0){
        perror("Closing Source File");
        return 1;
    };
    return 0;
}