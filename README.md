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

The Class ist build around the Arduino framework and uses the arduino Wire class  
The TMP117 Class assumes that the Wire class has alread been initialized.

## TMP117 Class Interface
- constructor
- task function
- several enums named after register bit description in the datasheet
- functions for reading the temperature 
- functions for accessing the limit registers (read / write)
- functions for reading the ID registers
- functions for setting the operation mode
- functions for checking status flags


### constructor
```
TMP117(uint8_t addr);		// Constructor with i2c address
```
Needs to be called with the desired chip addresses

### task function
```
bool process_idle(void);	// non blocking processing, returns true if idle
```
needs to be called primarily if EEPROM acces is needed or a chip reset is performed.
There is no time limit.  
As long as the chip is busy the task function will return false

### reading the temperature
```
int16_t getTemp(uint8_t decimals);	// gets temperature in decimal fixed point notation
int16_t getTemp(void);				// gets temperature in binary s8.7 fixed point notiation
```
The native numerical format ist the signed IQ9.7 format.  
An overloaded function allows the retrievil in decimal format as an integer Valu. A value of 21.5 with one decimal is representad as 215, with 2 decimals it is 2150

### setting / reading temperaturer limits
```
void setHighTemperaturLimit(int16_t tempDec, uint8_t decimals);	// set value in decimal fixed point notation
void setHighTemperaturLimit(int16_t tempIQ);					// set value in binary s8.7 fixed point notation
void setLowTemperaturLimit(int16_t tempDec, uint8_t decimals);	// set value in decimal fixed point notation
void setLowTemperaturLimit(int16_t tempIQ);						// set value in binary s8.7 fixed point notation

int16_t getHighTemperaturLimit(uint8_t decimals);	// get value in decimal fixed point notation
int16_t getHighTemperaturLimit(void);				// get value in binary s8.7 fixed point notation 						
int16_t getLowTemperaturLimit(uint8_t decimals);	// get value in decimal fixed point notation
int16_t getLowTemperaturLimit(void);                // get value in binary s8.7 fixed point notation
```
There are functions for accesing the registers for upper and lower temperature limit. (set and get)  
for numerical details see [reading the tempature](#reading-the-temperature)  


### setting / reading operation mode
```

typedef enum:uint8_t {	ALERT_PIN_ACTIVE_LOW,
						ALERT_PIN_ACTIVE_HIGH 
						} alert_pin_polarity_et;

typedef enum:uint8_t {	ALERT_PIN_ALERT,
						ALERT_PIN_DATA_READY 
						} alert_pin_select_et;

typedef enum:uint8_t {	ALERT_MODE_THERMISTOR,
						ALERT_MODE_ALERT 
						} alert_mode_select_et;

typedef enum:uint8_t {	AVERAGING_OFF,
						AVERAGING_8,
						AVERAGING_32,
						AVERAGING_64
						} averaging_mode_et;

typedef enum:uint8_t {	CONVERSION_TIME_1_64s,
						CONVERSION_TIME_1_8s,
						CONVERSION_TIME_1_2s,
						CONVERSION_TIME_1s,
						CONVERSION_TIME_2s,
						CONVERSION_TIME_4s,
						CONVERSION_TIME_8s,
						CONVERSION_TIME_16s
						} conversion_time_et;
						
typedef enum:uint8_t {	MODE_CONTINUOUS,
						MODE_SHUTDOWN,
						MODE_CONTINUOUS_RES,
						MODE_ONE_SHOT
						} conversion_mode_et;

typedef enum:uint8_t {	EEPROM_LOCK,
						EEPROM_UNLOCK
						} eeprom_lock_mode_et;

typedef enum:uint8_t {  EEPROM_POS_1,
						EEPROM_POS_2,
						TEMPERATURE_OFFSET,
						EEPROM_POS_3 
						} eeprom_pos_et;

void setAlertPinSource(alert_pin_select_et source);
void setAlertPinPolarity(alert_pin_polarity_et polarity);
void setAlertMode(alert_mode_select_et mode);
void setAveragingMode(averaging_mode_et mode);
void setConversionTime(conversion_time_et time);
void setConversionMode(conversion_mode_et mode);


alert_pin_select_et 	getAlertPinSource(void);
alert_pin_polarity_et 	getAlertPinPolarity(void);
alert_mode_select_et 	getAlertMode(void);
averaging_mode_et		getAveragingMode(void);
conversion_time_et		getConversionTime(void);
conversion_mode_et		getConversionMode(void);
```
There are several functions for adjusting the devices operating mode. Use those in conjunction with the enum types named after the datasheet

### aquiring status flags
```
bool isDataReady(void);
bool testHighTemperatureAlert(void);
bool testLowTemperatureAlert(void);
bool testEepromBusy(void);
bool testEepromLocked(void);
```
These function correspond to the respective status bit

### aquiring chip details
```
uint16_t getDeviceID(void);
uint8_t getDeviceRevision(void);
```
There are functions to read out the  ID and revision registers

### chip reset
```
void reset(void);
```
The chip reset will last a few milliseconds, during which a call to the task function will return false
