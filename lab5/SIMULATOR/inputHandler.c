#include <termios.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
void sendChar(int fd){


    char input = getchar();

    if (input == 'n') {
        uint8_t out = 0b0001;
        write(fd, &out, 1);
    }

    if (input == 's') {
        uint8_t out = 0b0100;
        write(fd, &out, 1);
    }

    if (input == 'e') {
        printf("You have exited the simulation");

    }
    close(fd);
}

void main() {
    int fd;
    fd = open("/dev/ttyS2",  O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd==-1) {printf("Funkar inte");}
    struct termios tty;
    tcgetattr(fd, &tty);
    cfsetospeed(&tty, B9600);
    cfsetispeed(&tty, B9600);
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;
    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    tcsetattr(fd, TCSANOW, &tty);
    sendChar(fd);
    }

