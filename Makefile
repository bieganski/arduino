PROJECT_DEFAULT := test

ifeq ($(PROJECT),)
$(info "==== PROJECT variable not set, assuming default - $(PROJECT_DEFAULT)")
endif

PROJECT ?= $(PROJECT_DEFAULT)
CLI := arduino-cli
UART_TTY := /dev/ttyUSB0
FQBN := esp32:esp32:esp32
# FQBN := arduino:avr:uno


UNAME_S := $(shell uname -s)
APT_MANAGER := 
ifeq ($(UNAME_S),Linux)
	APT_MANAGER := apt
endif
ifeq ($(UNAME_S),Darwin)
	APT_MANAGER := brew
endif
ifeq ($(APTP_MANAGER)),)
	$(error "not supported OS, add it manually")
endif


all:	run

install_board:
	# $(CLI) core install arduino:avr
	$(CLI) core install esp32:esp32

minicom:
	@echo "==== configuring minicom... (need root)"
	@sudo $(APT_MANAGER) install minicom
	@sudo mkdir -p /etc/minicom
	@sudo cp minirc.dfl /etc/minicom
	@echo "==== minicom configured properly!"


config_global:
	curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sh

	# poniższy krok tworzy plik arduino-cli.yaml, jednak go pomijamy, bo posiadamy już gotowy (zawierający esp32 dependency) 
	### arduino-cli config init
	### arduino-cli sketch new MyFirstSketch

	$(CLI) core update-index

	$(CLI) board list # wypisuje podłączone płytki
	$(CLI) core install esp32:esp32
	pip2 install pyserial
	
config_external:
	./install_external_libs.sh

configure: minicom config_global config_external info


info:
	@echo "==== connected boards: "
	$(CLI) board list

compile:
	@echo "==== compiling '$(PROJECT)' example..."
	$(CLI) compile --fqbn $(FQBN) --build-cache-path ./tmp $(PROJECT)

upload:
	@echo "==== uploading  '$(PROJECT)'..."
	$(CLI) upload -p $(UART_TTY) --fqbn $(FQBN) $(PROJECT)

run: compile upload

