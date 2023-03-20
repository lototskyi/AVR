#ifndef RTC_H_
#define RTC_H_

#include "main.h"

unsigned char RTC_ConvertToDec(unsigned char c); // binary-coded decimal (BCD) to decimal
unsigned char RTC_ConvertFromBinDec(unsigned char c); // decimal to binary-coded decimal

#endif /* RTC_H_ */