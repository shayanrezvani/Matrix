#include <stdio.h>
#include <string.h>
#include "libfahw.h"

int main(int argc, char ** argv)
{
    char *status = "off";
    if (argc != 2) {
        printf("Set relay on\n");
    } else {
        status = argv[1];
        printf("Set relay %s\n", argv[1]);
    }

    int pin = GPIO_PIN(7);
    int ret = -1;
    boardInit();
    if ((ret = exportGPIOPin(pin)) == -1) {	
        printf("exportGPIOPin(%d) failed!", pin);
    }
    if ((ret = setGPIODirection(pin, GPIO_OUT)) != 0) {
        printf("setGPIODirection(%d) failed", pin);
    }

    if (strcmp(status, "on") == 0) {
        ret = setGPIOValue(pin, GPIO_HIGH);
    } else if (strcmp(status, "off") == 0) {
        ret = setGPIOValue(pin, GPIO_LOW);
    }
    return ret;
}
