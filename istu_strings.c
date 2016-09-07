/*=====================================================================

istu_strings.c - ISTU modual, Sunduino Library for STM32F4

Copyright (c) 2016 Weidong Sun.  All right reserved.

Contact information
 -------------------
 Weidong Sun, China
 Web      :  https://oxduke.github.io
 e-mail   :  swdswd28@gmail.com

This file is part of the ISTU modual of Sunduino project
======================================================================*/

#include "istu_strings.h"

uint8_t istuStrlen(const uint8_t* str)
{
	uint8_t i;

	i = 0;

	while (1)
	{
		if (*str == '\0')
			break;
		str++;
		i++;
	}

	return i;
}

bool istuStrcmp(const uint8_t* str1, const uint8_t* str2)
{
	while (1)
	{
		if (*str1 != *str2)
			return false;
		if (*str1 == '\0' || *str2 == '\0')
			break;
		str1++;
		str2++;
	}

	return true;
}

bool istuStrFindFirstCharacter(const uint8_t* str, const uint8_t target, uint8_t* position)
{
	uint8_t i;
	uint8_t strLength = istuStrlen(str);

	*position = 0;

	for (i = 0; i < strLength; i++)
	{
		if (*(str + i) == target)
		{
			*position = i;
			return true;
		}
	}
	return false;
}

uint8_t istuStrCharacterCount(const uint8_t* str, const uint8_t target)
{
	uint8_t i = 0 ;
	uint8_t counter = 0;

	while (* (str + i) != '\0')
	{
		if (*(str + i) == target)
		{
			counter++;
		}
		i++;
	}

	return counter;
}

void istuStrcpy(uint8_t* str1, const uint8_t* str2)
{
	while (1)
	{
		*str1 = *str2;
		if (*str2 == '\0')
			break;
		str1++;
		str2++;
	}
}

uint32_t istuPow(uint8_t number, uint8_t power)
{
	uint32_t result;
	result = 1;

	while (1)
	{
		if (power == 0)
			break;

		result = result * number;
		power--;
	}

	return result;
}

bool istuStrAllNumbers(const uint8_t* str)
{
	uint8_t i = 0;

	while (*str != '\0')
	{
		if (*str < '0' || *str > '9')
		{
			if (*str == '-' && i == 0) //negative sign
				;
			else
				return false;
		}
		str++;
		i++;
	}

	return true;
}

/**
* convert string to number with signs in decimal,
* @param  str    string
* @param  number pointer to result number
* @return        true: conversion a success, false: conversion a failure
*/
bool istuStrToNum(const uint8_t* str, int32_t* number)
{
	uint8_t i;

	//characteristcis of a number
	uint8_t sign = 1; //sign=1: positive, sign=0:negative

	//variables used in searching a char in str
	bool searchResult;
	uint8_t searchPosition;

	//array used to store valid digits, maxium digits are 16
#define NUMBER_OF_VALID_DIGITS 16
	uint8_t validDigits[NUMBER_OF_VALID_DIGITS];

	//temp variables
	uint8_t numberOfDigits;
	int32_t tempResult;

	//step1. get sign
	sign = 1; //default: positive
	searchResult = istuStrFindFirstCharacter(str, '-', &searchPosition);
	if (searchResult == true)
	{
		sign = 0; //negative sign detected
	}

	//step2. get valid digits
	//clear the array
	for (i = 0; i < NUMBER_OF_VALID_DIGITS; i++)
	{
		validDigits[i] = '\0';
	}

	//get the position of the first valid digit
	while (1)
	{
		if ((*str >= '0' && *str <= '9') || (*str == '\0'))
			break;

		str++;
	}

	//no valid digits
	if (*str == '\0')
		return false;

	//copy the valid digits
	for (i = 0; *str >= '0' && *str <= '9' && i < NUMBER_OF_VALID_DIGITS; i++, str++)
	{
		validDigits[i] = *str;
	}

	//step3. convert digits to number
	//calculate number of digits
	numberOfDigits = 0;
	numberOfDigits = istuStrlen(validDigits);

	//start conversion
	tempResult = 0;
	for (i = 0; i < numberOfDigits; i++)
	{
		tempResult = tempResult + (validDigits[i] - 48) * istuPow(10, numberOfDigits - i - 1);
	}


	if (sign == 0)
		tempResult = -tempResult;

	*number = tempResult;

	return true;
}

void istuStrAdvanceOneStep(uint8_t* str)
{
	while (1)
	{
		if (*str == '\0')
			break;
		*str = *(str + 1);
		str++;
	}
}

/**
* @breif 1.remove leading and trailing spaces in str,
*        2. remove redundant spaces(no contiguous spaces, only one space a time)
*            e.g. [  I Love   You] ==> [I Love You]
*        3. remove space before and after '(' and ')' and ","
*        4. asterisk always comes before space
*            e.g. [int* a]=>[int* a]
*
*        not able to trim string with more than 256 characters
*
* @param str the string need to be trimed
*/
void istuStrTrimSpace(uint8_t* str)
{
	uint8_t i;
	uint8_t* tempPointer;
	uint8_t spaceCounter = 0;

	//	tempPointer = str;

	//step1.trim leading spaces
	while (*str == ' ')
	{
		istuStrAdvanceOneStep(str);
	}

	//step2.trim trailing spaces
	//find the position of the first '\0'
	tempPointer = str;
	while (1)
	{
		if (*tempPointer == '\0')
			break;
		tempPointer++;
	}
	//trim spaces
	spaceCounter = 0;
	i = 1;
	while (1)
	{
		if (*(tempPointer - i) != ' ')
			break;
		spaceCounter++;
		i++;
	}
	*(tempPointer - spaceCounter) = '\0';

	//step3.trim contiguous spaces
	spaceCounter = 0;
	tempPointer = str;
	while (*tempPointer != '\0')
	{
		if (*tempPointer == ' ')
		{
			spaceCounter++;
			if (spaceCounter >= 2)
			{
				istuStrAdvanceOneStep(tempPointer);
				spaceCounter--;
				tempPointer--;
			}
		}
		else
			spaceCounter = 0;

		tempPointer++;
	}

	//step4. trim spaces before and after "(" and ")" and ","
	tempPointer = str;
	while (*tempPointer != '\0')
	{
		if (*tempPointer == '(' || *tempPointer == ')' || *tempPointer == ',')
		{
			if (*(tempPointer - 1) == ' ')
			{
				istuStrAdvanceOneStep(tempPointer - 1);
				*tempPointer--; //always points to the current character
			}
			if (*(tempPointer + 1) == ' ')
				istuStrAdvanceOneStep(tempPointer + 1);
		}

		tempPointer++;
	}

	//step5, asterisk always comes before space e.g.[int* a]=>[int* a]
	tempPointer = str;
	while (*tempPointer != '\0')
	{
		if (*tempPointer == '*' && *(tempPointer - 1) == ' ')
		{
			*(tempPointer - 1) = '*';
			*tempPointer = ' ';
		}

		tempPointer++;
	}


}

uint8_t istuParameterTypeRecognize(const uint8_t* parameterTypeStart)
{
	if (istuStrcmp(parameterTypeStart, "char*") == true || istuStrcmp(parameterTypeStart, "uint8_t*") == true)
		return PARAMETER_TYPE_STRING;
	else if (istuStrcmp(parameterTypeStart, "void") == true)
		return PARAMETER_TYPE_VOID;
	else
		return PARAMETER_TYPE_NOT_STRING;
}

void istuExtractFunctionInfoFromStorage(uint8_t* str, functionInfo_t* functionInfo)
{
	uint8_t i;

	uint8_t searchPosition;

	//pointers used to divide the string
	uint8_t* returnTypeStart, *returnTypeEnd;
	uint8_t returnTypeLength;
	uint8_t* functionNameStart, *functionNameEnd;
	uint8_t functionNameLength;
	uint8_t* parameterListStart, *parameterListEnd;
	uint8_t parameterListLength;
	uint8_t* parameterTypeStart, *parameterTypeEnd;
	uint8_t parameterTypeLength;

	uint8_t commaCounter = 0;

	uint8_t parameterTypeExtracted;

	//extract return type string
	returnTypeStart = str;
	istuStrFindFirstCharacter(returnTypeStart, ' ', &returnTypeLength);
	returnTypeEnd = returnTypeStart + returnTypeLength;
	*returnTypeEnd = '\0';

	functionNameStart = returnTypeEnd + 1;
	istuStrFindFirstCharacter(functionNameStart, '(', &functionNameLength);
	functionNameEnd = functionNameStart + functionNameLength;
	*functionNameEnd = '\0';

	//	tempStr = functionNameEnd + 1;
	parameterListStart = functionNameEnd + 1;
	istuStrFindFirstCharacter(parameterListStart, ')', &parameterListLength);
	parameterListEnd = parameterListStart + parameterListLength;
	*parameterListEnd = ','; //',' replaces ')'
	parameterListEnd++;
	*parameterListEnd = '\0';

	//step1. extract return type
	if (istuStrcmp(returnTypeStart, "void") == true)
		functionInfo->returnType = RETURN_TYPE_VOID;
	else
		functionInfo->returnType = RETURN_TYPE_NOT_VOID;

	//step2. extract function name
	istuStrcpy(functionInfo->functionName, functionNameStart);

	//step3. extract parameters
	commaCounter = 0;
	commaCounter = istuStrCharacterCount(parameterListStart, ',');
	functionInfo->parameterNumber = commaCounter;

	//recognize parameter type one by one, e.g.[uint8* ptr]
	parameterTypeStart = parameterListStart;

	if (functionInfo->parameterNumber == 1) //determine if the only parameter is "void"
	{
		istuStrFindFirstCharacter(parameterTypeStart, ',', &parameterTypeLength);
		parameterTypeEnd = parameterTypeStart + parameterTypeLength;
		*parameterTypeEnd = '\0'; //mark the end of type declaration

		parameterTypeExtracted = istuParameterTypeRecognize(parameterTypeStart);

		if (parameterTypeExtracted == PARAMETER_TYPE_VOID)
			functionInfo->parameterNumber = 0;

		//restore
		*parameterTypeEnd = ',';
	}

	for (i = 0; i < functionInfo->parameterNumber; i++)
	{
		istuStrFindFirstCharacter(parameterTypeStart, ' ', &parameterTypeLength);
		parameterTypeEnd = parameterTypeStart + parameterTypeLength;
		*parameterTypeEnd = '\0'; //mark the end of type declaration

		parameterTypeExtracted = istuParameterTypeRecognize(parameterTypeStart);

		if (parameterTypeExtracted == PARAMETER_TYPE_STRING)
			functionInfo->parameterType[i] = PARAMETER_TYPE_STRING;
		else
			functionInfo->parameterType[i] = PARAMETER_TYPE_NOT_STRING;

		*parameterTypeEnd = ' '; //re-store from '\0' to ' '
		istuStrFindFirstCharacter(parameterTypeStart, ',', &searchPosition);
		parameterTypeStart = parameterTypeStart + searchPosition + 1; //next start
	}

}


/**
* test if input string is an match for a function call
* @param  str               input string
* @param  inputFunctionInfo info extracted from input string stores here
* @param  matchFunctionInfo the function the string is intended to match
* @return                   true: match a success, false: match a failure
*/
void istuExtractFuntionInfoFromInput(uint8_t* str, functionInfo_t* inputFunctionInfo)
{
	uint8_t i;

	uint8_t* functionNameStart, *functionNameEnd;
	uint8_t functionNameLength;
	uint8_t* parameterListStart, *parameterListEnd;
	uint8_t parameterListLength;
	uint8_t* argumentStart, *argumentEnd;
	uint8_t argumentLength;

	uint8_t parameterNumber;

	//step1. pre-process the input string
	//string should be trimed before this function is called.

	//step2. extract function name
	functionNameStart = str;
	istuStrFindFirstCharacter(functionNameStart, '(', &functionNameLength);
	functionNameEnd = functionNameStart + functionNameLength;
	*functionNameEnd = '\0';
	istuStrcpy(inputFunctionInfo->functionName, functionNameStart);

	//step3. extract argument number
	parameterListStart = functionNameEnd + 1;
	istuStrFindFirstCharacter(parameterListStart, ')', &parameterListLength);
	parameterListEnd = parameterListStart + parameterListLength;
	*parameterListEnd = ',';
	parameterListEnd++;
	*parameterListEnd = '\0';

	if (parameterListLength == 0) // no parameter input, then parameter number is not determined by the number of ','
		parameterNumber = 0;
	else
		parameterNumber = istuStrCharacterCount(parameterListStart, ',');

	inputFunctionInfo->parameterNumber = parameterNumber;

	//step4. extract argument type
	argumentStart = parameterListStart;
	for (i = 0; i < parameterNumber; i++)
	{
		istuStrFindFirstCharacter(argumentStart, ',', &argumentLength);
		argumentEnd = argumentStart + argumentLength;
		*argumentEnd = '\0'; //mark the end of type declaration

		if (*argumentStart == '"' && *(argumentEnd - 1) == '"') //string
		{
			inputFunctionInfo->parameterType[i] = PARAMETER_TYPE_STRING;
			inputFunctionInfo->parameterPointer[i] = argumentStart + 1; //ignore '"'
			*(argumentEnd - 1) = '\0'; //mark the end of string, replace '"' with '\0'
		}
		else if (istuStrAllNumbers(argumentStart) == true) //not string
		{
			inputFunctionInfo->parameterType[i] = PARAMETER_TYPE_NOT_STRING;
			inputFunctionInfo->parameterPointer[i] = argumentStart;
		}
		else
			inputFunctionInfo->parameterType[i] = PARAMETER_TYPE_ERROR;

		argumentStart = argumentEnd + 1;
	}
}




//////////////////////////////////////////////////////////////////////////
//                  currently under construction                        //
//////////////////////////////////////////////////////////////////////////

#if 0
uint8_t istuInputValidityCheck(const uint8_t* str)
{
	bool result;

	//step1. trim spaces
	//	istuStrTrimSpace(str);

	//step2. is input a command?
	//	result = istuCommandRecognize(str, position);
	if (result == true)
	{	//execute command
		;
	}

	//step2. is input a function call?
	//check format
	//	result = istuFunctionFormatCheck(str);
	if (result == false)
	{
		//format check failed
		;
	}

}

/**
* [istuCommandRecognize description]
* @param  str      [description]
* @param  position [description]
* @return          [description]
*/
bool istuCommandRecognize(const uint8_t* str, uint8_t* position)
{
	uint8_t i;

	for (i = 0; i < COMMAND_MAX_NUMBER; i++)
	{
		if (istuStrcmp(str, commandList[i]) == true)
		{
			*position = i;
			return true;
		}
	}

	return false;
}


bool istuFunctionRecognize(const uint8_t* str, uint8_t* position)
{
	istuFunctionFormatCheck(str);
}

/**
* check a string if its basic format agrees to a function call
* @param  str input string
* @return     1: input string is a valid function call
*             0: input string is not a valid function call
*/
bool istuFunctionFormatCheck(const uint8_t* str)
{
	uint8_t i;

	int8_t parenthesisCounter = 0;

	//parenthesis number check
	for (i = 0; * (str + i) != '\0'; i++)
	{
		if (*(str + i) == '(')
			parenthesisCounter++;
		if (*(str + i) == ')')
			parenthesisCounter--;
	}
	if (parenthesisCounter != 0)
		return false;

	//other rules shall be added
	return true;
}


/**
* recognize quotation marks in the parameter to determine its type: string or not string
* @param  parameterStart the first character in the parameter
* @param  parameterEnd   one past the last character in the parameter
* @return                0: parameter type is string
*                        1: parameter type is not string
*                        2: parameter type void
*                        3:parameter type wrong
*/
uint8_t istuArgumentTypeRecognize(uint8_t* argumentTypeStart, uint8_t* argumentTypeEnd)
{
	uint8_t singleQuotationMarkCounter;
	uint8_t doubleQuotationMarkCounter;

	uint8_t temp;

	temp = *argumentTypeEnd;
	*argumentTypeEnd = '\0';
	if (istuStrcmp(argumentTypeStart, "void") == true)
		return PARAMETER_TYPE_VOID;
	*argumentTypeEnd = temp;

	singleQuotationMarkCounter = 0;
	doubleQuotationMarkCounter = 0;
	while (argumentTypeStart != argumentTypeEnd)
	{
		if (*argumentTypeStart == '"')
			doubleQuotationMarkCounter++;
		if (*argumentTypeStart == '\'')
			singleQuotationMarkCounter++;

		argumentTypeStart++;
	}

	if (singleQuotationMarkCounter == 0 && doubleQuotationMarkCounter == 0)
		return PARAMETER_TYPE_NOT_STRING;

	if (singleQuotationMarkCounter % 2 == 0 || doubleQuotationMarkCounter % 2 == 0)
		return PARAMETER_TYPE_STRING;

	return PARAMETER_TYPE_ERROR;
}

#endif
