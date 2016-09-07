#include "istu_config.h"
#include "Sunduino.h"
#include "led.h"

uint16_t test1(uint16_t num, uint8_t* str);

functionStored_t functionStorageList[] =
{
	(void*)test1, "uint16_t test1(uint16_t num, uint8_t* str)",
	(void*)ledToggle, "void ledToggle(void)"
};

uint8_t istuNumberOfStorageFunction(void)
{
	return sizeof(functionStorageList) / sizeof(functionStorageList[0]);
}

uint16_t test1(uint16_t num, uint8_t* str)
{
	printf("\r\n ===This is test1===  \r\n");
	printf("number: %d \r\n", num);
	printf("string: %s \r\n", str);
	
	return num;
}
