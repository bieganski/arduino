#!/bin/bash

LIBS_URLS_FNAME='git_libs.txt'
ESP32_VERSION="1.0.4"

# set -u
# set -x


log() {
	echo "==== $1"
}

check_file() {
	if ! [ -f $1 ]; then
		log "$1 file not found!"
	fi
}


find_libs_path() {
	pushd . > /dev/null
	ARDU_DATA_DIR=`arduino-cli config dump | grep data | cut -d : -f 2`
	local path=$ARDU_DATA_DIR/packages/esp32/hardware/esp32/
	if ! [[ $(ls -1 $path | grep "$ESP32_VERSION") ]]; then
		log "error! couldn't find ESP32 v.$ESP32_VERSION in $path! please change LIB32_VERSION variable value!"
		exit
	fi
	popd . > /dev/null
	echo $path/$ESP32_VERSION/libraries
}

install_lcd_libs() {
	log "installing LCD libs (GFX, BusIO)..."
	local $path=$(find_libs_path)
	pushd . > /dev/null
	cd $path
	git clone https://github.com/adafruit/Adafruit_BusIO
	cp Adafruit_BusIO/* .
	git clone https://github.com/adafruit/Adafruit-GFX-Library
	cp Adafruit-GFX-Library/* .
	popd . > /dev/null
	log "LCD libraries installed successfully!"
}

install_git_repos() {
	log "reading libraries from git repositories from file $LIBS_URLS_FNAME.."
	local LIBS_URLS_FULL_PATH=`pwd`/$LIBS_URLS_FNAME
	local path=$(find_libs_path)
	
	pushd . > /dev/null
	cd $path
	log "cloning repositories from $LIBS_URLS_FULL_PATH to $path/libraries directory..."
	cat $LIBS_URLS_FULL_PATH | rev | cut -d / -f 1 | rev | xargs rm -rf
	cat $LIBS_URLS_FULL_PATH | xargs -I git clone "{}"
	log "all repositories cloned properly!"
	popd > /dev/null
}

install_all() {
	check_file $LIBS_URLS_FNAME
	install_git_repos
	install_lcd_libs
}


all() {
	install_all
}

all
