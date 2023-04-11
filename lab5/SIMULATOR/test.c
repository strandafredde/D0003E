//
// Created by stran on 2023-04-10.
//
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include "simHandler.h"

int main(void) {
    int fd;
    fd = open("/dev/ttyS2",  O_RDWR );
    if (fd==-1) {
        printf("Couldn't open specified file");
    }
    else {

        static struct termios tty;
        initSimHandler();
        tcgetattr(fd, &tty);
        fcntl(fd, F_SETFL, O_NONBLOCK);
        //Set port speed
        cfsetospeed(&tty, B9600);
        cfsetispeed(&tty, B9600);

        tty.c_cflag &= ~CSIZE;              // Clear char size
        tty.c_cflag |= CS8;                 // Set 8 bit char size
        tty.c_cflag &= ~PARENB;             // no parity
        tty.c_cflag &= ~CSTOPB;             // 1 stop bit
        tty.c_cflag |= CREAD;    // Enable receive
        tty.c_cc[VMIN] = 1;
        printf("hello");
        printf("");
        uint8_t out = 0b0011;
        printf("%u", out);
        write(fd, &out, 1);
    }
}

// gcc test.c -o test.exe
// test.exe