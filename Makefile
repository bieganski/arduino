PROJECT_NAME := test # myBLE_server
CLI := arduino-cli
UART_TTY := /dev/ttyUSB0


FQBN := esp32:esp32:esp32


# FQBN := arduino:avr:uno

config:
	curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sh

	# poniższy krok tworzy plik arduino-cli.yaml, jednak go pomijamy, bo posiadamy już gotowy (zawierający esp32 dependency) 
	### arduino-cli config init

	# poniższy krok tworzy nowy projekt (folder), a w nim plik MyFirstSketch.ino, zawierający plik
	# 	void setup() {
	# 	}
	# 	void loop() {
	# 	}
	### arduino-cli sketch new MyFirstSketch

	$(CLI) core update-index

	$(CLI) board list # wypisuje podłączone płytki
	$(CLI) core install esp32:esp32
	pip2 install pyserial

info:
	$(CLI) board list # wypisuje podłączone płytki

run:
	# $(CLI) core install arduino:avr
	$(CLI) compile --fqbn $(FQBN) --build-cache-path ./tmp $(PROJECT_NAME)
	$(CLI) upload -p $(UART_TTY) --fqbn $(FQBN) $(PROJECT_NAME)
