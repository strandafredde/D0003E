//
// Created by stran on 2023-04-10.
//

#include "simHandler.h"
#include "gui.h"
#include "aaa.h"



//  gcc main.c aaa.c simHandler.c gui.c -o main.exe

int main(void){

        void *inputHandler();
        void *lightHandler();

        pthread_t inputThread;
        pthread_t lightThread;

        initSimHandler();
        printStatus();

        pthread_create(&inputThread, NULL, inputHandler, NULL);
        pthread_create(&lightThread, NULL, lightHandler, NULL);

        pthread_join(inputThread, NULL);
        pthread_join(lightThread, NULL);


}
