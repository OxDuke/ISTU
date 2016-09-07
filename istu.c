/*=====================================================================

istu.c - ISTU modual, Sunduino Library for STM32F4

Copyright (c) 2016 Weidong Sun.  All right reserved.

Contact information
 -------------------
 Weidong Sun, China
 Web      :  https://oxduke.github.io
 e-mail   :  swdswd28@gmail.com

This file is part of the ISTU modual of Sunduino project
======================================================================*/

#include "istu.h"

#include "istu_strings.h"
#include "istu_config.h"

// command list array
const char* commandList[] =
{
	"Help",
	"List",
	"Address"
};


void istuExecute(uint8_t* inputStr)
{
	functionInfo_t inputFunction, storedFunction;

	uint8_t i;

	bool matchResult;

	uint8_t tempString[FUNCTION_DECLARATION_MAX_LENGTH];
	int32_t tempArgumentList[FUNCTION_PARAMETERS_MAX_NUMBER];

	void (*ptr)();

	uint32_t returnValue;

	//starts here
	istuStrTrimSpace(inputStr);

	istuExtractFuntionInfoFromInput(inputStr, &inputFunction);

	//start matching one by one
	matchResult = false;
	for (i = 0; i < istuNumberOfStorageFunction(); i++)
	{

		//extract info from stored function's declaration
		istuStrcpy(tempString, functionStorageList[i].functionDeclaration);
		istuStrTrimSpace(tempString);
		istuExtractFunctionInfoFromStorage(tempString, &storedFunction);

		if (istuMatchFunction(&inputFunction, &storedFunction) == true)
		{
			matchResult = true;
			break;
		}
	}

	if (matchResult == true)
	{
//		printf("find a match, No.%d\r\n", i);

		//start loading the function
		ptr = (void(*)())functionStorageList[i].pointerToFunction;

		//load arguments
		for (i = 0; i < storedFunction.parameterNumber; i++)
		{
			if (storedFunction.parameterType[i] == PARAMETER_TYPE_NOT_STRING)
			{
				istuStrToNum(inputFunction.parameterPointer[i], &tempArgumentList[i]);
			}
			else
			{
				tempArgumentList[i] = (int32_t)inputFunction.parameterPointer[i];
			}
		}

		switch (storedFunction.parameterNumber)
		{
		case 0:
			returnValue = (*(uint32_t(*)())ptr)();
			break;
		case 1:
			returnValue = (*(uint32_t(*)())ptr)(tempArgumentList[0]);
			break;
		case 2:
//			(*ptr)(tempArgumentList[0], tempArgumentList[1]);
			returnValue = (*(uint32_t(*)())ptr)(tempArgumentList[0], tempArgumentList[1]);
			break;
		case 3:
			returnValue = (*(uint32_t(*)())ptr)(tempArgumentList[0], tempArgumentList[1], tempArgumentList[2]);
			break;
		case 4:
			returnValue = (*(uint32_t(*)())ptr)(tempArgumentList[0], tempArgumentList[1], tempArgumentList[2], tempArgumentList[3]);
			break;
		case 5:
			returnValue = (*(uint32_t(*)())ptr)(tempArgumentList[0], tempArgumentList[1], tempArgumentList[2], tempArgumentList[3], tempArgumentList[4]);
			break;
		}

		if (storedFunction.returnType == RETURN_TYPE_NOT_VOID)
			printf("return value: %d\n", returnValue);

	}
	else
		printf("did not find a match\n");

}

bool istuMatchFunction(const functionInfo_t* inputFunctionInfo, const functionInfo_t* storedFunctionInfo)
{
	bool matchResult;

	uint8_t i ;

	//match process
	matchResult = false;

	matchResult = istuStrcmp(inputFunctionInfo->functionName, storedFunctionInfo->functionName);
	if (matchResult == false)
		return false;

	if (inputFunctionInfo->parameterNumber != storedFunctionInfo->parameterNumber)
		return false;

	for (i = 0; i < inputFunctionInfo->parameterNumber; i++)
	{
		if (inputFunctionInfo->parameterType[i] != storedFunctionInfo->parameterType[i])
			return false;
	}

	return true;
}


void printStorageFunctionInfo(const functionInfo_t* functionInfo)
{
	int i;

	printf("\n   now print function information \n");

	if (functionInfo->returnType == RETURN_TYPE_VOID)
		printf("return: void \n");
	else
		printf("return: not void\n");

	printf("name: %s\n", functionInfo->functionName);

	printf("paramter number: %d \n", functionInfo->parameterNumber);

	for (i = 0; i < functionInfo->parameterNumber; ++i)
	{
		printf("paramter type: ");
		if (functionInfo->parameterType[i] == PARAMETER_TYPE_STRING)
			printf("string\n");
		else if (functionInfo->parameterType[i] == PARAMETER_TYPE_NOT_STRING)
			printf("not string\n");
		else if (functionInfo->parameterType[i] == PARAMETER_TYPE_VOID)
			printf("void\n");
		else
			printf("error\n");
	}
}

void printInputFunctionInfo(functionInfo_t* functionInfo)
{
	int i;

	printf("\n====now print input function information==== \n");

	printf("name: %s\n", functionInfo->functionName);

	printf("paramter number: %d \n", functionInfo->parameterNumber);

	for (i = 0; i < functionInfo->parameterNumber; ++i)
	{
		printf("paramter type: ");
		if (functionInfo->parameterType[i] == PARAMETER_TYPE_STRING)
			printf("string\n");
		else if (functionInfo->parameterType[i] == PARAMETER_TYPE_NOT_STRING)
			printf("not string\n");
		else if (functionInfo->parameterType[i] == PARAMETER_TYPE_VOID)
			printf("void\n");
		else
			printf("error\n");
	}
}




#if 0
uint8_t commandProcess(uint8_t* nameBuffer)
{

	uint16_t i;
	uint8_t commandIndex;

//	commandRead();

	switch (commandIndex)
	{

	//Help
	case 0:
		printf("\r\n");
		printf("-----------------------ISTU----------------------- \r\n");
		printf("ISTU stands for Interactive Serial-based Tune Unit \r\n");
		printf("commands are: \r\n");
		printf("Help          get help\r\n");
		printf("List          list all the function controlled by ISTU\r\n");
		printf("Address       get the address for a function dec  \r\n");
		break;

	//List
	case 1:
		printf("---------------------function list--------------------- \r\n");
		for (i = 0; i < count; ++i)
		{
			printf("%s", *d);
		}
		break;
	case 2://Address
		break;

	}

}

#endif
