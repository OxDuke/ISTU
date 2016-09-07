#ifndef TYPE_H
#define TYPE_H

#include "stdint.h"
#include <stdbool.h>

#if 0
typedef char int8_t;
typedef unsigned char uint8_t;

typedef unsigned short uint16_t;

typedef int int32_t;
typedef unsigned int uint32_t;

typedef long long int64_t;
#endif



#define FUNCTION_DECLARATION_MAX_LENGTH 150
#define FUNCTION_CALL_MAX_LENGTH 150

typedef struct functionInfo
{

#define FUNCTION_NAME_MAX_LENGTH 30
	uint8_t functionName[FUNCTION_NAME_MAX_LENGTH];

#define RETURN_TYPE_VOID     0
#define RETURN_TYPE_NOT_VOID 1
	uint8_t returnType;

#define PARAMETER_TYPE_STRING      0
#define PARAMETER_TYPE_NOT_STRING  1
#define PARAMETER_TYPE_VOID        2
#define PARAMETER_TYPE_ERROR       3
	uint8_t parameterNumber;

#define FUNCTION_PARAMETERS_MAX_NUMBER 10
	uint8_t parameterType[FUNCTION_PARAMETERS_MAX_NUMBER];

	uint8_t* parameterPointer[FUNCTION_PARAMETERS_MAX_NUMBER];

} functionInfo_t;


typedef struct functionStored
{
	void* pointerToFunction;
	const uint8_t* functionDeclaration;
} functionStored_t;

#endif /* TYPE_H */
