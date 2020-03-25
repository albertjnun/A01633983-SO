#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
    pid_t pid = fork();

    if (pid == 0) {
        printf("Soy el hijo\n");
    }
    else {
        printf("Soy el padre\n");
    }
    return 0;      
}