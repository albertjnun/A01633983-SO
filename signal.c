#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void processSignal(int s){
    printf("Recibí señal %d\n",s);
}
void killSignal(int s){
    printf("No puedes matar el proceso\n");
}

int main(){
    signal(10,processSignal);
    signal(15,killSignal);
    while(1){
        sleep(3);
        printf("Trabajando\n");
    }
    return 1;
}