
/// 
///  Created for personal use, use it at your own risk and benefit.
///  https://github.com/GitMoDu/FastSegment
/// 

#include "FastSegment.h"

#define DIGIT_COUNT 3
#define DEMO_REFRESH_PERIOD_MILLIS 20
#define DEMO_MAX_RPM 500

#define SERIAL_DATA_PIN		0 //SDD  || Serial data input    || SER
#define REGISTER_CLOCK_PIN  2 //SCLK || Register clock		   || RCLK
#define REGISTER_SHIFT_PIN	1 //LOAD || Shift register clock || SRCLK


FastSegment SegmentDriver;

void Demo()
{
	while (true)
	{
		SegmentDriver.Clear();
		delay(1000);

		for (uint16_t i = 0; i <= DEMO_MAX_RPM; i++)
		{
			if (SegmentDriver.SetNumber(i, false))
			{
				SegmentDriver.ShowNumber();
				Serial.println(i);
			}	

			delay(DEMO_REFRESH_PERIOD_MILLIS);
		}

		delay(1000);
	}
}

void setup() {

	Serial.begin(9600);

	SegmentDriver.Setup(SERIAL_DATA_PIN, REGISTER_CLOCK_PIN, REGISTER_SHIFT_PIN, DIGIT_COUNT);
	SegmentDriver.SetNumber(0, false);

	Demo();
}


void loop() {
}
