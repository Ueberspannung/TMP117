# TMP117
simple Interface for configuring the TMP117 Temperature sensor

The TMP117 is a temperature sensor and monitor chip produce by [Texas Instrmensts](https:www.ti.com).
It features 
- a programmable alert pin
- an I2C Interface
- 4 selectable I2C addresses
- a temperature resolution of up to 1/128°C
- the temperature Reading is given as an singed 9.7 IQ value

# TMP117 Class
The TMP117 class provides a simple interface to program the temperature sensor and read the temperature.
The alert pin is currently unused.

The interface is closely related to the naming in the datasheet.

There is one task funkion to reduce blocking calls.
The acces to the EEPROM could need several milliseconds, therfore the EEPROM access is divided into several steps consecutively executed through the task function

The Class ist build around the Arduino framework and uses the arduino Wire Class
The TMP117 Class assumes that the Wire class has alread been initialized.

## TMP117 Class Interface
- constructor
- task function
- several enums named after register bit description in the datasheet
- functions for reading the temperature 
- functions for accessing the limit registers (read / write)
- functions for reading the ID registers
- function for setting the operation mode


### constructor
Needs to be called with the desired chip addresses

### task function
needs to be called primarily if EEPROM acces is needed or a chip reset is performed.
There is no time limit

### reading the temperature
The native numerical format ist the signed IQ9.7 format.  
An overloaded function allows the retrievil in decimal format as an integer Valu. A value of 21.5 with one decimal is representad as 215, with 2 decimals it is 2150

### setting / reading temperaturer limits
There are functions for accesing the registers for upper and lower temperature limit. (set and get)  
for numerical details see [reading the tempature](#reading-the-tempature)

### setting / reading operation mode
There are several functions for adjusting the devices operating mode. Use those in conjunction with the enum types named after the datasheet

