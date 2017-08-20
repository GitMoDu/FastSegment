
/// 
///  Created for personal use, use it at your own risk and benefit.
///  https://github.com/GitMoDu/FastSegment
///  Depends on Fast for IO https://github.com/GitMoDu/Fast
/// 

#include "FastSegment.h"

bool FastSegment::Setup(const uint8_t dataPin, const uint8_t clockPin, const uint8_t shiftPin, const uint8_t digitCount)
{
	if (dataPin < NUM_DIGITAL_PINS
		&& clockPin < NUM_DIGITAL_PINS
		&& shiftPin < NUM_DIGITAL_PINS
		&& digitCount <= NUM_DIGITAL_PINS)
	{
		DataPin = dataPin;
		ClockPin = clockPin;
		ShiftPin = shiftPin;
		DigitCount = digitCount;

		Data.Setup(DataPin, LOW);
		Shift.Setup(ShiftPin, HIGH);
		Clock.Setup(ClockPin, HIGH);

		Reset();
		Clear();

		return true;
	}
	else
	{
		return false;
	}
}

uint8_t FastSegment::GetLastNumber()
{
	return LastNumber;
}

void FastSegment::SetDigitsAll(const uint8_t value)
{
	for (uint8_t i = 0; i < DigitCount; i++)
	{
		Digits[i] = value;
	}
}


bool FastSegment::SetNumber(const uint32_t number, const bool forceUpdate, const bool replaceZero)
{
	if (forceUpdate || number != LastNumber)
	{
		LastNumber = number;

		uint8_t IntValue;
		bool ReachedMSD = false;
		for (int8_t i = DigitCount - 1; i >= 0; i--)
		{
			IntValue = ((number / TenPower((uint8_t)i)) % 10);

			if (!ReachedMSD)
			{
				ReachedMSD = IntValue > 0 || i == 0;
			}

			if (ReachedMSD)
			{
				Digits[i] = GetDigitByte(IntValue);
			}
			else
			{
				Digits[i] = (uint8_t)SEGMENT_CLEAR;
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}

void FastSegment::ShowBytes(uint8_t byteArray[], uint8_t byteArraySize)
{
	for (uint8_t i = 0; i < byteArraySize; i++)
	{
		WriteByte(byteArray[i]);
	}

	Shift.PulseLow();
}

void FastSegment::ShowNumber(const bool clearBefore)
{
	if (clearBefore)
	{
		Clear();
	}

	ShowBytes(Digits, DigitCount);
}

void FastSegment::Reset()
{
	Data.Set(HIGH);
	Clock.PulseLow();
	Data.Set(LOW);
	Shift.PulseLow();
}

void FastSegment::SetAll(const bool bitValue)
{
	Data.Set(bitValue);
	for (uint8_t i = 0; i < DigitCount * BYTE_SIZE; i++)
	{
		Clock.PulseLow();
	}
	Data.Set(LOW);
	Shift.PulseLow();
}
void FastSegment::Clear()
{
	SetAll(HIGH);
}

void FastSegment::SetHead(const bool value)
{
	Data.Set(value);
	Clock.PulseLow();
	Data.Set(LOW);
}

void FastSegment::WriteByte(const uint8_t value)
{
	for (int i = 0; i < BYTE_SIZE; i++)
	{
		SetHead((value)&(1 << (BYTE_SIZE - 1 - i)));
	}
}

uint32_t FastSegment::TenPower(const uint8_t power)
{
	switch (power)
	{
	case 0:
		return (uint32_t)1;
	case 1:
		return (uint32_t)10;
	case 2:
		return (uint32_t)100;
	case 3:
		return (uint32_t)1000;
	case 4:
		return (uint32_t)10000;
	case 5:
		return (uint32_t)100000;
	case 6:
		return (uint32_t)1000000;
	case 7:
		return (uint32_t)10000000;
	case 8:
		return (uint32_t)100000000;
	case 9:
		return (uint32_t)1000000000;
	case 10:
		return (uint32_t)10000000000;
	default:
		return (uint32_t)0;
	}
}

uint8_t FastSegment::GetDigitByte(const uint8_t number0to9, const bool decimalOn)
{
	if (decimalOn)
	{
		switch (number0to9)
		{
		case 0:
			return SEGMENT_0D;
		case 1:
			return SEGMENT_1D;
		case 2:
			return SEGMENT_2D;
		case 3:
			return SEGMENT_3D;
		case 4:
			return SEGMENT_4D;
		case 5:
			return SEGMENT_5D;
		case 6:
			return SEGMENT_6D;
		case 7:
			return SEGMENT_7D;
		case 8:
			return SEGMENT_8D;
		case 9:
			return SEGMENT_9D;
		default:
			return SEGMENT_ERROR;
		}
	}
	else
	{
		switch (number0to9)
		{
		case 0:
			return SEGMENT_0;
		case 1:
			return SEGMENT_1;
		case 2:
			return SEGMENT_2;
		case 3:
			return SEGMENT_3;
		case 4:
			return SEGMENT_4;
		case 5:
			return SEGMENT_5;
		case 6:
			return SEGMENT_6;
		case 7:
			return SEGMENT_7;
		case 8:
			return SEGMENT_8;
		case 9:
			return SEGMENT_9;
		default:
			return SEGMENT_ERROR;
		}
	}
}

