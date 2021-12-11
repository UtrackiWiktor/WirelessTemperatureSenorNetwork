/*
 * MSP430_delay.c
 *
 *  Created on: 1 gru 2021
 *      Author: licht
 */
#include "MSP430_delay.h"


void delay(unsigned int us)
{
    while(us)
    {
        us--;
    }
    return;
}

