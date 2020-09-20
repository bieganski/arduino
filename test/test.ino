#include <WiFi.h>
#include "private.h"

char* API_KEY = "a4c7378a-5798-40f6-a9c1-6a0fae8c4da4";
char* MACZKA_ID = "1474";
// Use this one to obtain "Maczka" bus stop ID
// String URL = "api.um.warszawa.pl/api/action/dbtimetable_get/?id=b27f4c17-5c50-4a5b-89dd-236b282bc499&name=Maczka&apikey="

char* URL = "https://api.um.warszawa.pl/api/action/dbtimetable_get?id=e923fa0e-d96c-43f9-ae6e-60518c9f3238&busstopId=%s&busstopNr=01&line=245&apikey=%s";

char url_placeholder[300];

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

	sprintf(url_placeholder, URL, MACZKA_ID, APIKEY);
	Serial.println(url_placeholder);
}

void loop() {
}
