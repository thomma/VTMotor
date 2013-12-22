#include "storage.h" 

uint8_t GetAddr(void){
	return  eeprom_read_byte((uint8_t *)LOC_ADDR);
}
void StoreAddr(uint8_t addr){
	eeprom_update_byte((uint8_t *)LOC_ADDR, addr);
}