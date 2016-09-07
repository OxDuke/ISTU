/*=====================================================================

istu.h - ISTU modual, Sunduino Library for STM32F4

Copyright (c) 2016 Weidong Sun.  All right reserved.

Contact information
 -------------------
 Weidong Sun, China
 Web      :  https://oxduke.github.io
 e-mail   :  swdswd28@gmail.com

This file is part of the ISTU modual of Sunduino project
======================================================================*/
#ifndef ISTU_H
#define ISTU_H

#include  "istu_types.h"

//extern const char* commandList[];

void istuExecute(uint8_t* inputStr);

//helpers
void printStorageFunctionInfo(const functionInfo_t* functionInfo);
void printInputFunctionInfo(functionInfo_t* functionInfo);

bool istuMatchFunction(const functionInfo_t* inputFunctionInfo, const functionInfo_t* storedFunctionInfo);

#endif /* ISTU_H */
