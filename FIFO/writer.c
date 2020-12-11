#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdint.h>
#include <inttypes.h>
#include <malloc.h>
#include <stddef.h>

int main(int argc, char *argv[])
{
    int fd, fd3, result;
    int nb = 0;
    size_t size;
    char *resstring;
    char s[20];
    char nam[] = "a1.fifo";
    //
    if ((fd3 = open(nam, O_RDONLY)) < 0){
        printf("Can't open FIFO for reading\n");
        exit(-1);
    }
    size = read(fd3, s, 20);
    close(fd3);
    //
    nb = atoi(s);

    resstring = (char*)malloc(nb);
    char name[] = "a.fifo";
    if ((fd = open(name, O_RDONLY)) < 0){
        printf("Can't open FIFO for reading\n");
        exit(-1);
    }
    size = read(fd, resstring, nb);
    if (size < 0){
        printf("Can\'t read string\n");
        exit(-1);
    }
    printf("%s\n", resstring);
    close(fd);
    remove(name);
    remove(nam);
    return 0;
}