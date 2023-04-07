//
// Created by stran on 2023-04-07.
//
#include <stdio.h>
#include "gui.h"
void print(){
    if (lights == NORTHRED) {
        printf("======== CAR-BRIDGE SIMULATION =======");
        printf("Lights | S:" + SOUTHL + " | N:" + SOUTHL);
        printf("Queue  | S:" + SOUTHQ + " | N:" + SOUTQ);
        printf("======================================");
    }
    if (lights == NORTHGREEN) {

    }
    if (lights == SOUTHRED) {

    }
    if (lights == SOUTHGREEN) {

    }
}