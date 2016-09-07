/*=====================================================================

istu_strings.h - ISTU modual, Sunduino Library for STM32F4

Copyright (c) 2016 Weidong Sun.  All right reserved.

Contact information
 -------------------
 Weidong Sun, China
 Web      :  https://oxduke.github.io
 e-mail   :  swdswd28@gmail.com

This file is part of the ISTU modual of Sunduino project
======================================================================*/

#ifndef ISTU_STRINGS_H
#define ISTU_STRINGS_H

#include "stdio.h"
#include "istu_types.h"
//#include "istu.h"


//enum {false, true} bool;

//basic helpers
uint8_t istuStrlen(const uint8_t* str);
bool istuStrcmp(const uint8_t* str1, const uint8_t* str2);
bool istuStrFindFirstCharacter(const uint8_t* str, const uint8_t target, uint8_t* position);
uint8_t istuStrCharacterCount(const uint8_t* str, const uint8_t target);
void istuStrcpy(uint8_t* str1, const uint8_t* str2);
uint32_t istuPow(uint8_t number, uint8_t power);
bool istuStrAllNumbers(const uint8_t* str);
bool istuStrToNum(const uint8_t* str, int32_t* number);
void istuStrAdvanceOneStep(uint8_t* str);

//advanced helpers
void istuStrTrimSpace(uint8_t* str);
uint8_t istuParameterTypeRecognize(const uint8_t* parameterTypeStart);

//info extracter
void istuExtractFunctionInfoFromStorage(uint8_t* str, functionInfo_t* functionInfo);
void istuExtractFuntionInfoFromInput(uint8_t* str, functionInfo_t* inputFunctionInfo);






//////////////////////////////////////////////////////////////////////////
//                  currentlt under construction                        //
//////////////////////////////////////////////////////////////////////////

uint8_t istuInputValidityCheck(const uint8_t* str);
bool istuCommandRecognize(const uint8_t* str, uint8_t* position);
bool istuFunctionRecognize(const uint8_t* str, uint8_t* position);
bool istuFunctionFormatCheck(const uint8_t* str);
uint8_t istuArgumentTypeRecognize(uint8_t* parameterStart, uint8_t* parameterEnd);





#endif /* ISTU_STRINGS_H*/
