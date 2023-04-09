//
// Created by stran on 2023-04-09.
//
#include <stdio.h>
#include "gui.h"
void printStatus(){
        printf("===================== CAR-BRIDGE SIMULATION =====================");
        printf("Lights | S:" + southGreen + " | N:" + northGreen);
        printf("Queue  | S:" + queues[1] + " | N:" + queues[2]+ " | B:" + queues[0];
        printf("=================================================================");
}