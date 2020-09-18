#include <WiFi.h>
#include "private.h"

void setup_wifi() {
		WiFi.begin(SSID, PASSWORD);

		while (WiFi.status() != WL_CONNECTED) {
			delay(500);
			Serial.print(".");
		}
}

void setup() {
	Serial.begin(115200);
	delay(10);
	setup_wifi();

	Serial.println("");
	Serial.println("WiFi connected");
	Serial.println("IP address: ");
	Serial.println(WiFi.localIP());
}

void loop() {
}
