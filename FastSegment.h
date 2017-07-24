/// 
///  Created for personal use, use it at your own risk and benefit.
/// 

#ifndef _FASTSEGMENT_h
#define _FASTSEGMENT_h

#include <Arduino.h>
#include <Fast.h>

#define ARDUINO_MAX_PIN NUM_DIGITAL_PINS
#define MAX_DIGIT_COUNT 10
#define BYTE_SIZE 8

class FastSegment
{
private:
#define SEGMENT_ERROR B10101010//Error

	uint8_t DataPin, ClockPin, ShiftPin, DigitCount;

	FastShifter Clock, Shift;
	//FastShifter ActiveLed;
	FastOut Data;

	uint32_t TenPower(const uint8_t power);

	void Push(const uint8_t times = 1);
	void SetHead(const bool value);
	void SetAll(const bool value);
	void Clear();
	void Reset();
	void WriteByte(const byte value);
	uint32_t LastNumber = 0;
	byte GetNumberByte(const uint8_t number1to9, const bool decimalOn = false);


public:

	///////////////////B76543210
#define SEGMENT_0  B11000000 //All but 6 and 7
#define SEGMENT_1  B11111001 //1 and 2
#define SEGMENT_2  B10100100 //0, 1, 6, 4, 3
#define SEGMENT_3  B10110000 //0, 1, 6, 2, 3
#define SEGMENT_4  B10011001 //5, 6, 1, 2
#define SEGMENT_5  B10010010 //0, 5, 6, 2, 3
#define SEGMENT_6  B10000011 //5, 4, 3, 2, 6
#define SEGMENT_7  B11111000 //0, 1, 2
#define SEGMENT_8  B10000000 //All but 7
#define SEGMENT_9  B10011000 //0, 5, 6, 1, 2

#define SEGMENT_0D  B01000000 //All but 6 and 7
#define SEGMENT_1D  B01111001 //1 and 2
#define SEGMENT_2D  B00100100 //0, 1, 6, 4, 3
#define SEGMENT_3D  B00110000 //0, 1, 6, 2, 3
#define SEGMENT_4D  B00011001 //5, 6, 1, 2
#define SEGMENT_5D  B00010010 //0, 5, 6, 2, 3
#define SEGMENT_6D  B00000011 //5, 4, 3, 2, 6
#define SEGMENT_7D  B01111000 //0, 1, 2
#define SEGMENT_8D  B00000000 //All but 7
#define SEGMENT_9D  B00011000 //0, 5, 6, 1, 2

#define SEGMENT_UNDER  B11110111
#define SEGMENT_BAR	   B10111111

#define SEGMENT_CLEAR  B11111111
#define SEGMENT_ALL_ON B00000000

	byte Digits[MAX_DIGIT_COUNT];
	
	bool Setup(const uint8_t dataPin, const uint8_t clockPin, const uint8_t shiftPin, const uint8_t digitCount);

	///Show the digits set from the number
	void SetDigits(const uint32_t value, const bool show = true);

	///Show the digits set from the number, omitting the leftmost zeros
	void SetDigitsReplaceMSZero(const uint32_t value, const byte replaceZero, const bool show = true);
	
	void SetDigitsAll(const byte value);
	uint32_t GetLastNumber();
	void ShowDigits();
};

#endif

