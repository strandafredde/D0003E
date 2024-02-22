//
// Created by stran on 2023-04-09.
//
#include <stdio.h>
#include "gui.h"
#include "simHandler.h"
void printStatus(void) {
    printf("===================== CAR-BRIDGE SIMULATION =====================\n");
    printf("Lights | North: %d | South: %d \n ", northLight, southLight);
    printf("Queue  | S:%d | N:%d | B:%d\n", queues[1], queues[0], queues[2]);
    printf("=================================================================\n");
}

void printQueue(void) {
    printf("Queue  | S:%d | N:%d | B:%d\n", queues[1], queues[0], queues[2]);
}

void printLights(void) {
    printf("Lights | North: %d | South: %d \n ", northLight, southLight);
}