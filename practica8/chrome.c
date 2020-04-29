#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

int main(){
    int shmId = shmget(200,100,0644 | IPC_CREAT);
    for(int i = 0; i < 5; i++){
        int pid = fork();
        if (pid != 0) {
            shmId = shmget(200,100,0644);
            char * var = (char *)shmat(shmId,NULL,0);
            break;
        }        
    }
    sprintf(var,"hola mundo");
    printf("esto tiene var %s",var);
    return 0;
}