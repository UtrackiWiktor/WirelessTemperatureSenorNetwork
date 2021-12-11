/*
 * ds18b20.c
 *
 *  Created on: 21 Nov 2021
 *      Author: Wiktor Utracki
 */
#include "ds18b20.h"
#include <stdint.h>

void ds18b20_initialization()
{
    ONE_WIRE_DIR |= ONE_WIRE_PIN;
    ONE_WIRE_OUT &= ~ONE_WIRE_PIN;
    __delay_cycles(500);
    ONE_WIRE_OUT |= ONE_WIRE_PIN;
    ONE_WIRE_DIR &= ~ONE_WIRE_PIN;
    __delay_cycles(500);
}

unsigned long long ds18b20_read_ROM()
{
    uint64_t serial = 0;

    ds18b20_initialization();
    send_command(ROM_READ);

    uint8_t i;
    for(i = 64; i > 0; i--){
            serial >>= 1;
            ONE_WIRE_DIR |= ONE_WIRE_PIN;
            ONE_WIRE_OUT &= ~ONE_WIRE_PIN;
            __delay_cycles(2);
            ONE_WIRE_OUT |=ONE_WIRE_PIN;
            ONE_WIRE_DIR &= ~ONE_WIRE_PIN;
            __delay_cycles(8);
            if(ONE_WIRE_IN & ONE_WIRE_PIN)
            {
                serial |= 0x8000000000000000;
            }
            __delay_cycles(55);
        }
    return serial;
}

float ds18b20_read_temperature()
{
    unsigned int temperature_raw;

    ds18b20_initialization();
    send_command(ROM_SKIP);
    send_command(FUNC_CONVERT_TEMP);
    delay_ms(750); //750ms is the max conversion time for 12-bit resolution
    ds18b20_initialization();
    send_command(ROM_SKIP);
    send_command(FUNC_READ_SCRATCHPAD);
    temperature_raw = read_temperature_bytes();
    float temperature_celsius;
    temperature_celsius = (float)temperature_raw;
    return (float)temperature_celsius/8.0;
}


void send_command(char command)
{
    int i;
    for(i = 0; i<8; i++)
    {
        ONE_WIRE_DIR |= ONE_WIRE_PIN;
        ONE_WIRE_OUT &= ~ONE_WIRE_PIN;
        __delay_cycles(5); //keep low for a bit but no longer than 15us
        if(command & 0x01) //there is a logic '1' to be send - "Write 1" time slot
        {
            ONE_WIRE_DIR &= ~ONE_WIRE_PIN; //set to input for high-z, pull-up will set high
            //ONE_WIRE_OUT |= ONE_WIRE_PIN;
        } //if a logic '0' is to be send, keep the low state
        __delay_cycles(60); //<15;60>
        ONE_WIRE_OUT |= ONE_WIRE_OUT;
        ONE_WIRE_DIR &= ~ONE_WIRE_PIN;
        command = command >> 1;
    }
}

unsigned int read_temperature_bytes()
{
    //read 2 bytes, sign-extended, 2-s complement
    unsigned int result_raw = 0;
    int i;
    for(i = 0; i < 16; i++)
    {
        ONE_WIRE_DIR |= ONE_WIRE_PIN;
        ONE_WIRE_OUT &= ~ONE_WIRE_PIN;
        __delay_cycles(1);
        ONE_WIRE_OUT |=ONE_WIRE_PIN;
        ONE_WIRE_DIR &= ~ONE_WIRE_PIN;
        __delay_cycles(5);
        if(ONE_WIRE_IN & ONE_WIRE_PIN)
        {
            result_raw |= 0b1000000000000000;
        }
        result_raw = result_raw >> 1;
        __delay_cycles(60); //this whole cycle must be >60us
    }
    return result_raw;
}

void delay_ms(unsigned int ms) //TODO: implement with better power saving
{
    int i;
    for(i = 0; i < ms; i++)
    {
        __delay_cycles(1000);
    }
}
