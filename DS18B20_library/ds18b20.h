/*
 * ds18b20.h
 *
 *  Created on: 21 Nov 2021
 *      Author: Wiktor Utracki
 */
#include <msp430.h>
#ifndef DS18B20_LIBRARY_H_
#define DS18B20_LIBRARY_H_

/*
 * 1-Wire definitions
 */
#define ONE_WIRE_DIR    P1DIR
#define ONE_WIRE_OUT    P1OUT
#define ONE_WIRE_IN     P1IN
#define ONE_WIRE_PIN    BIT6

/*
 * DS18b20 ROM Commands
 */
#define ROM_SEARCH       0xF0
#define ROM_READ         0x33
#define ROM_MATCH        0x55
#define ROM_SKIP         0xCC
#define ROM_ALARM_SEARCH 0xEC

/*
 * DS18B20 Function Commands
 */
#define FUNC_CONVERT_TEMP       0x44
#define FUNC_WRITE_SCRATCHPAD   0x4E
#define FUNC_READ_SCRATCHPAD    0xBE
#define FUNC_COPY_SCRATCHPAD    0x48
#define FUNC_RECALL_EEPROM      0xB8
#define FUNC_READ_POWER_SUPPLY  0xB4

/* ----------------------------------
 * Communication procedure:
 * 1) Initialization
 * 2) ROM Command
 * 3) Function Command
 ------------------------------------
*/
/*
 * Runs initialization procedure
 */
void ds18b20_initialization();
/*
 * Reads 64-bit ROM memory from slave.
 * Is to be used with ONLY ONE slave connected, otherwise a data collision will occur!
 */
unsigned long long ds18b20_read_ROM();
/*
 * Reads temperature measurement from the device.
 */
float ds18b20_read_temperature();
/*
 * Sends specified command to the DS18B20 (ROM or function)
 */
void send_command(char command);
/*
 * Receive data from ds18b20's scratchpad. Specify number of bytes to be read and from what starting position
 */
//unsigned int receive_data(int number_of_bytes, int start_index);
/*
 * Reads temperature bytes from the scratchpad.
 */
unsigned int read_temperature_bytes();
/*
 * Create delay for x microseconds. Depends on clock frequency.b
 */
inline void delay_us(unsigned int us);
/*
 * Create delay for x miliseconds. Depends on clock frequency.
 */
void delay_ms(unsigned int ms);


#endif /* DS18B20_LIBRARY_DS18B20_H_ */
