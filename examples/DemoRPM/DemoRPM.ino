
/// 
///  Created for personal use, use it at your own risk and benefit.
/// 

#include "FastSegment.h"

#define DIGIT_COUNT 3
#define DEMO_REFRESH_PERIOD_MILLIS 100

#define SERIAL_DATA_PIN   5  //SDD Serial data input SER_Pin
#define REGISTER_CLOCK_PIN  6 //SCLK  //Register clock RCLK_Pin
#define REGISTER_SHIFT_PIN 7 //LOAD  //Shift register clock SRCLK_Pin

FastSegment SegmentDriver;

void Demo()
{
	while (true)
	{
		SegmentDriver.SetDigitsAll(SEGMENT_BAR);
		SegmentDriver.ShowDigits();
		delay(2000);

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

			if (SegmentDriver.GetLastNumber() != Number)
			{
				Serial.println(Number);
				SegmentDriver.SetDigitsReplaceMSZero(Number, SEGMENT_UNDER, true);
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
