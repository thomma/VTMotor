#include <avr/eeprom.h>

#define LOC_ADDR		0	
#define LOC_SOFTSTART	1

// Function prototypes.
uint8_t GetAddr(void);
void StoreAddr(uint8_t addr);