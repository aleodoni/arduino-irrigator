#include <RFTransmitter.h>

#define pin_analog_sig A0
#define pin_red_led 5
#define pin_yellow_led 6
#define pin_green_led 7
#define pin_digital_relay 8
#define irrigation_time 30000
#define NODE_ID 1
#define OUTPUT_RF_PIN 11
#define MAX_PACKAGE_SIZE 4

int analog_val;
char msg[MAX_PACKAGE_SIZE];
char *msg_humid = "Humid soil";
char *msg_moderate = "Moderate soil";
char *msg_dry = "Dry soil";

// Send on digital pin 11 and identify as node 1
RFTransmitter transmitter(OUTPUT_RF_PIN, NODE_ID);

void setup() {
	Serial.begin(9600);
	pinMode(pin_analog_sig, INPUT);
	pinMode(pin_red_led, OUTPUT);
	pinMode(pin_yellow_led, OUTPUT);
	pinMode(pin_green_led, OUTPUT);
	pinMode(pin_digital_relay, OUTPUT);
}

void loop() {
	analog_val = analogRead(pin_analog_sig);
	
	Serial.print("Analogic port: ");
	Serial.println(analog_val);

	if (analog_val > 0 && analog_val < 400) {
		Serial.println(msg_humid);
		turn_off_leds();
		digitalWrite(pin_green_led, HIGH);
		send_info_rf(msg_humid);
	}

	if (analog_val > 400 && analog_val < 800) {
		Serial.println(msg_moderate);
		turn_off_leds();
		digitalWrite(pin_yellow_led, HIGH);
		send_info_rf(msg_moderate);
	}

	if (analog_val > 800 && analog_val < 1024) {
		Serial.println(msg_dry);
		turn_off_leds();
		digitalWrite(pin_red_led, HIGH);
		send_info_rf(msg_dry);
		irrigate();
	}

	delay(1000);
}

void turn_off_leds() {
	digitalWrite(pin_red_led, LOW);
	digitalWrite(pin_yellow_led, LOW);
	digitalWrite(pin_green_led, LOW);
}

void irrigate() {
	digitalWrite(pin_digital_relay, HIGH);
	delay(irrigation_time);
	digitalWrite(pin_digital_relay, LOW);
}

void send_info_rf(char *mensagem) {
	transmitter.send((byte *)mensagem, strlen(mensagem) + 1);
	delay(5000);
	transmitter.resend((byte *)mensagem, strlen(mensagem) + 1);
}