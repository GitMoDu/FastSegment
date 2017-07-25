
/// 
///  Created for personal use, use it at your own risk and benefit.
///  https://github.com/GitMoDu/FastSegment
/// 

#include "FastSegment.h"

#define DIGIT_COUNT 3
#define DEMO_REFRESH_PERIOD_MILLIS 10

#define SERIAL_DATA_PIN		  5 //SDD  || Serial data input    || SER
#define REGISTER_CLOCK_PIN  6 //SCLK || Register clock		   || RCLK
#define REGISTER_SHIFT_PIN	7 //LOAD || Shift register clock || SRCLK


FastSegment SegmentDriver;

void Demo()
{
	while (true)
	{
		SegmentDriver.Clear();
		delay(1000);

		for (uint32_t i = 0; i < 30000l; i += 100l)
		{
			if (i > 100 && i < 150)
			{
				i += 30;
			}
			else if (i > 150 && i < 200)
			{
				i += 15;
			}

			int Number = i / 100;

			if (SegmentDriver.SetNumber(Number))
			{
				SegmentDriver.ShowNumber();
				Serial.println(Number);
			}		

			delay(DEMO_REFRESH_PERIOD_MILLIS);
		}
	}
}

void setup() {

	Serial.begin(9600);

	SegmentDriver.Setup(SERIAL_DATA_PIN, REGISTER_CLOCK_PIN, REGISTER_SHIFT_PIN, DIGIT_COUNT);

	Demo();
}


void loop() {
}
