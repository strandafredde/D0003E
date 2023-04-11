//
// Created by stran on 2023-04-09.
//
#include <stdio.h>
#include "gui.h"
#include "simHandler.h"
void printStatus(void) {
    printf("===================== CAR-BRIDGE SIMULATION =====================\n");
    printf("Lights | %d | %d = SouthGreen, %d = NorthGreen, %d = Red\n", lights,0,1,2);
    printf("Queue  | S:%d | N:%d | B:%d\n", queues[1], queues[0], queues[2]);
    printf("=================================================================\n");
}
