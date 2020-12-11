#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <malloc.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>

    int64_t getFileSize(const char* file_name){
        int64_t _file_size = 0;
        FILE* fd2 = fopen(file_name, "rb");
        if (fd2 == NULL){
            _file_size = -1;
        }
        else {
            while(getc(fd2) != EOF)
                _file_size++;
            fclose(fd2);
        }
        return _file_size;
    }


int main(int argc, char *argv[])
{
    int fd, fd1, fd3, result;
    int nb = 14;
    size_t size;
    char *str;
    char name[] = "a.fifo";
    char nam[] = "a1.fifo";

    (void) umask(0);

    int64_t file_size = getFileSize(argv[1]);
    printf("File size: %" PRId64 "\n", file_size);
    nb = file_size++;
    str = (char*)malloc(nb);
//
   if (mknod(nam, S_IFIFO | 0666, 0) < 0){
        printf("Can\'t create FIFO\n");
        exit(-1);
    }
    if ((fd3 = open(nam, O_WRONLY)) < 0){
        printf("Can\'t open FIFO for writing\n");
        exit(-1);
    }
    char nbs[20];
    sprintf(nbs, "%d", nb);
    size = write(fd3, nbs, 20);
    close(fd3);
//
    if((fd1 = open(argv[1], O_RDONLY)) < 0){
        printf("Can\'t open file for reading\n");
        exit(-1);       
    }
    
    size = read(fd1, str, nb);
    if (mknod(name, S_IFIFO | 0666, 0) < 0){
        printf("Can\'t create FIFO\n");
        exit(-1);
    }
    if ((fd = open(name, O_WRONLY)) < 0){
        printf("Can\'t open FIFO for writing\n");
        exit(-1);
    }
    size = write(fd, str, nb);
    if (size != nb)
    {
        printf("Can\'t write all string to FIFO\n");
        exit(-1);
    }
    close(fd);
    return 0;
}