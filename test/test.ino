
#include <esp_sleep.h>

#define _DEEP_SLEEP_TIME_SEC 3

#define DEEP_SLEEP_TIME (_DEEP_SLEEP_TIME_SEC * 1000000L)


void setup() {
    Serial.println("REBOOT!");
    // delay(100); // it doesn't print without that delay, how come? two cores used or what

    esp_sleep_enable_timer_wakeup(DEEP_SLEEP_TIME);

    // go to sleep, after wakeup 'setup' will be called
    esp_deep_sleep_start();
}

void loop() {
    Serial.print("ERROR: I shouldn't be in loop anytime! Deep sleep wakeup implies reboot!");
}
