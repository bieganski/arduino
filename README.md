# arduino
WIFI, Bluetooth, RFID, moisture sensor, LCD, etc.

Following diretory names correspond to projects:
* **http** - example requests by URL to WWW webpage
* **moisture** - analog moisture sensor sampling
* **time** - reading actual date from www
* **rfid** - RFID card/token reader
* **lcd** - LCD example
* **ble** - Bluetooth Low Energy protocol
* **cycles** - contains tests measuring microseconds and cycle count

`doc` directory containes some documentation.

# Setup

First, install `arduino-cli`.

MacOS:
```
brew update
brew install arduino-cli
```

Linux:
```
curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sh
```

then:

```
make config_global # it should install arduino-cli
make install_board
```


# Compile and upload
Let's say you have subdirectory `dirname`. It must contain file `dirname.ino`, containing both `setup` and `loop` functions. 


Depending on which ESP32 board you use, change `Makefile` `$(FQBN)` variable:
* Lolin32 - `FQBN := esp32:esp32:lolin32`
* DevKitC - `FQBN := esp32:esp32:esp32`

Compilation:
```
make PROJECT=dirname compile
```
Upload:
```
make PROJECT=dirname upload
```

