#include <msp430.h>
#include "DS18B20_library/ds18b20.h"

/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

    /* Check if 1MHz Calibration is present and set DCO to 1MHz */
    if (CALBC1_1MHZ != 0xFF)
    {
        DCOCTL = 0; // Select lowest DCOx and MODx
        BCSCTL1 = CALBC1_1MHZ; // Set range
        DCOCTL = CALDCO_1MHZ; // Set DCO step + modulation
    }

    float temperature = ds18b20_read_temperature();

    unsigned long long serial_number = ds18b20_read_ROM();

    while(1)
    {

    }
	return 0;
}
