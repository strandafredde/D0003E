//
// Created by stran on 2023-04-10.
//

#include "simHandler.h"
#include "gui.h"
#include "aaa.h"

//  gcc main.c aaa.c simHandler.c gui.c -o main.exe

int main(void){
        initSimHandler();
        printStatus();
        while(running) {
            inputHandler();
        }

}
