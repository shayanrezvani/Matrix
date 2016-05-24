#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libfahw.h"

#define BUF_SIZE    (64)
#define TEMP_DRIVER_MODULE        "w1-gpio"
#define TEMP_GPIO_DRIVER_MODULE   "w1-gpio-board"
int main(int argc, char ** argv)
{
    char temperature[BUF_SIZE];
    char modStr[BUF_SIZE];
    int board;
    int pin=GPIO_PIN(7);
    
    if ((board = boardInit()) < 0)
        printf("Fail to init board\n");
    
    sprintf(modStr, "modprobe %s gpio=%d", TEMP_GPIO_DRIVER_MODULE, pintoGPIO(pin));
    printf("%s\n", modStr);
    system(modStr);
    system("modprobe "TEMP_DRIVER_MODULE);
    memset(temperature, 0, BUF_SIZE);
    if (ds18b20Read(temperature) > 0) {
        printf("Temperature = %.3f C\n", atoi(temperature)/1000.0);
    } else {
        printf("Fail to get temperature\n");		
    }
    system("rmmod "TEMP_GPIO_DRIVER_MODULE);
    system("rmmod "TEMP_DRIVER_MODULE);
    return 0;
}
