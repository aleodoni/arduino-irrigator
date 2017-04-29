#include <RFTransmitter.h>

#define pin_analog_sig A0
#define pin_red_led 5
#define pin_yellow_led 6
#define pin_green_led 7

int analog_val;

void setup() {
	Serial.begin(9600);
	pinMode(pin_analog_sig, INPUT);
	pinMode(pin_red_led, OUTPUT);
	pinMode(pin_yellow_led, OUTPUT);
	pinMode(pin_green_led, OUTPUT);
}

void loop() {
	analog_val = analogRead(pin_analog_sig);
	
	Serial.print("Analogic port: ");
	Serial.println(analog_val);

	if (analog_val > 0 && analog_val < 400) {
		Serial.println(" Status: Humid soil");
		turn_off_leds();
		digitalWrite(pin_green_led, HIGH);
	}

	if (analog_val > 400 && analog_val < 800) {
		Serial.println("Status: Moderate soil");
		turn_off_leds();
		digitalWrite(pin_yellow_led, HIGH);
	}

	if (analog_val > 800 && analog_val < 1024) {
		Serial.println("Status: Dry soil");
		turn_off_leds();
		digitalWrite(pin_red_led, HIGH);
	}

	delay(1000);
}

void turn_off_leds() {
	digitalWrite(pin_red_led, LOW);
	digitalWrite(pin_yellow_led, LOW);
	digitalWrite(pin_green_led, LOW);
}


