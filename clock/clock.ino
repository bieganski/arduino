
// #include <esp_timer/include/esp_timer.h>


esp_timer_handle_t TIMER;

#include <esp_timer.h>
void setup() {

	Serial.begin(115200);
	// init timer

	if (esp_timer_init() != ESP_OK) {
		Serial.println("Error: canot init high-resolution timer!");
	}

	// create timer instance

	esp_timer_create_args_t args;
	
	if (esp_timer_create(&args, &TIMER) != ESP_OK) {
		Serial.println("Error: cannot instantiate timer handle!");
	}
}

// 1000 us
#define START_TIMER do { \
	esp_timer_start_once(TIMER, 1000); \
} while(0)

#define STOP_TIMER do { \
	esp_timer_stop(TIMER); \
} while(0)

// in micro seconds
// from doc: "number of microseconds since esp_timer_init was called"
// strange, so why to call esp_timer_start_once?
#define TIMER_GET_TIME do { \
	esp_timer_get_time(); \
} while (0)

// 10075 us == 2.4m cycles
void test() {
	volatile int a = 13, b = 3131;

	for(int i = 0; i < 100000; i++) {
		a += 2;
		b -= a * 4;
	}

}

volatile int b = 13;

// 3357 us
// 805 k cycles
void loads() {
	volatile int a;

	for(int i = 0; i < 100000; i++) {
		a = b;
	}
}
#include <Esp.h>

unsigned get_cpu_frequency_mhz() {
	return ESP.getCpuFreqMHz();
}

unsigned get_rtc_cycles() {
	return  ESP.getCycleCount();
}

void print_cpu_frequency() {
	unsigned freq = get_cpu_frequency_mhz();

	Serial.print("CPU frequency:");
	Serial.println(freq, DEC);
}

// microseconds to cycles
unsigned us2cycles(unsigned us) {
	unsigned freq = get_cpu_frequency_mhz();
	// micro * mega = 1
	return freq * us; 
}


// using two methods
void print_result(unsigned us, unsigned rtc_cycles) {
	Serial.println("=========");
	Serial.println("== Measured time: (using us-timer and knowing CPU Frequency)");
	Serial.print(us, DEC);
	Serial.print(" us == ");
	unsigned cycles = us2cycles(us);
	Serial.print(cycles, DEC);
	Serial.println(" cycles"); 
	Serial.println("== Measured RTC cycles directly: ");
	Serial.print(rtc_cycles, DEC);
	Serial.println(" cycles");
	Serial.println("=========");
}


void test_cycles(void (*f) (void)) {
	unsigned us1, us2, rtc1, rtc2;
	print_cpu_frequency();
	us1 = esp_timer_get_time(); // TIMER_GET_TIME; // ();
	rtc1 = get_rtc_cycles();
	f();
	rtc2 = get_rtc_cycles();
	us2 = esp_timer_get_time(); // TIMER_GET_TIME; // ();
	print_result(us2 - us1, rtc2 - rtc1);

}

void loop() {
	delay(1000);
	test_cycles(loads);
}

