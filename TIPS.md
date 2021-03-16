# TIPS

* The bootloader has the `CONFIG_BOOTLOADER_SKIP_VALIDATE_IN_DEEP_SLEEP` option which allows to reduce the wake-up time (useful to reduce consumption). This option is available when the `CONFIG_SECURE_BOOT` option is disabled. Reduction of time is achieved due to the lack of image verification. During the first boot, the bootloader stores the address of the application being launched in the RTC FAST memory. And during the awakening, this address is used for booting without any checks, thus fast loading is achieved.


* https://github.com/espressif/esp-idf/issues/5869
 ESP32 DevKit-C contains components such as USB-UART adapter which continue to draw current even when the ESP32 is in deep sleep mode. For this reason, with DevKit-C it is very hard to get accurate current measurement for the ESP32 module only.
