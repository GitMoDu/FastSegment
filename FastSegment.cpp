/// 
///  Created for personal use, use it at your own risk and benefit.
/// 

#include "FastSegment.h"


bool FastSegment::Setup(const uint8_t dataPin, const uint8_t clockPin, const uint8_t shiftPin, const uint8_t digitCount)
{
	if (dataPin < ARDUINO_MAX_PIN
		&& clockPin < ARDUINO_MAX_PIN
		&& shiftPin < ARDUINO_MAX_PIN
		&& digitCount <= MAX_DIGIT_COUNT)
	{
		DataPin = dataPin;
		ClockPin = clockPin;
		ShiftPin = shiftPin;
		DigitCount = digitCount;


		Data.Setup(DataPin, LOW);
		Shift.Setup(ShiftPin, HIGH);
		Clock.Setup(ClockPin, HIGH);

		Active.Setup(LED_BUILTIN, LOW);

		Reset();
		Clear();

		return true;
	}
	else
	{
		return false;
	}
}

uint32_t FastSegment::GetLastNumber()
{
	return LastNumber;
}

//void FastSegment::BootUpAnimation()
//{
//	Clear();
//	uint64_t NextRefresh = micros();
//	uint64_t Elapsed = micros();
//	NextRefresh = 0;
//	Demo();
//
//}


byte FastSegment::GetNumberByte(const uint8_t number0to9, const bool decimalOn)
{

	if (number0to9 > 9)
	{
		return SEGMENT_ERROR;
	}
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
		}
	}

}

void FastSegment::SetDigitsAll(const byte value)
{
	for (uint8_t i = 0; i < DigitCount; i++)
	{
		Digits[i] = value;
	}
}

void FastSegment::SetDigits(const uint32_t value, const bool show)
{
	LastNumber = value;
	for (uint8_t i = DigitCount - 1; i >= 0; i--)
	{
		Digits[i] = GetNumberByte(((value / TenPower(i)) % 10));

		if (i < 1)
		{
			break;
		}
	}

	if (show)
	{
		ShowDigits();
	}
}

void FastSegment::SetDigitsReplaceMSZero(const uint32_t value, const byte replaceZero, const bool show)
{
	LastNumber = value;
	bool ReachedMSB = false;
	for (uint8_t i = DigitCount - 1; i >= 0; i--)
	{
		uint8_t intValue = ((value / TenPower((uint8_t)i)) % 10);
		if (!ReachedMSB)
		{
			ReachedMSB = intValue > 0;

			if (!ReachedMSB && intValue == 0)
			{
				Digits[i] = replaceZero;
			}
			else
			{
				Digits[i] = GetNumberByte(intValue);
			}
		}
		else
		{
			Digits[i] = GetNumberByte(intValue);
		}

		if (i < 1)
		{
			break;
		}
	}

	if (show)
	{
		//Clear();
		ShowDigits();
	}
}

void FastSegment::ShowDigits()
{
	for (uint8_t i = 0; i < DigitCount; i++)
	{
		WriteByte(Digits[i]);
	}
}

void FastSegment::Reset()
{
	Data.Set(LOW);
	Clock.Set(LOW);
	Shift.Set(LOW);
	Clock.Set(HIGH);
	Shift.Set(HIGH);
}


void FastSegment::SetAll(const bool value)
{
	Active.PulseHigh();

	SetHead(value);
	for (uint8_t i = 0; i < DigitCount; i++)
	{
		Active.PulseHigh();
		for (uint8_t j = 0; j < BYTE_SIZE; j++)
		{
			Clock.PulseLow();
			Push();
		}
	}
}
void FastSegment::Clear()
{
	SetAll(HIGH);
}

void FastSegment::SetHead(const bool value)
{
	Active.PulseHigh();

	Data.Set(value);

	Clock.PulseLow();
}

void FastSegment::Push(const uint8_t times)
{
	Active.PulseHigh();

	for (uint8_t i = 0; i < times; i++)
	{
		Shift.PulseLow();
	}
}


void FastSegment::WriteByte(const byte value)
{
	Active.PulseHigh();

	for (int i = 0; i < BYTE_SIZE; i++)
	{
		SetHead((value)&(1 << (BYTE_SIZE - 1 - i)));
		Push();
	}
}

uint32_t FastSegment::TenPower(const uint8_t power)
{
	uint32_t Ten = 1;

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
		while (true);;
		break;
	}
	//Equivalent to this, up to 10 power and much, much faster.
	//for (uint8_t i = 0; i < power; i++)
	//{
	//	Ten *= (uint32_t)10;
	//}
	//return Ten;
}

