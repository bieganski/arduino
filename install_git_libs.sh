#!/bin/bash

LIBS_URLS_FNAME='git_libs.txt'
ESP32_VERSION="1.0.4"

set -u

log() {
	echo "==== $1"
}

check_file() {
	if ! [ -f $1 ]; then
		log "$1 file not found!"
	fi
}

install_git_repos() {
	pushd . > /dev/null
	LIBS_URLS_FULL_PATH=`pwd`/$LIBS_URLS_FNAME
	log "reading libraries from git repositories from file $LIBS_URLS_FNAME.."
	ARDU_DATA_DIR=`arduino-cli config dump | grep data | cut -d : -f 2`
	path=$ARDU_DATA_DIR/packages/esp32/hardware/esp32/
	if ! [[ $(ls -1 $path | grep "$ESP32_VERSION") ]]; then
		log "error! couldn't find ESP32 v.$ESP32_VERSION in $path! please change LIB32_VERSION variable value!"
		exit
	fi
	
	cd $path/$ESP32_VERSION/libraries
	log "cloning repositories from $LIBS_URLS_FULL_PATH..."
	cat $LIBS_URLS_FULL_PATH | rev | cut -d / -f 1 | rev | xargs rm -rf
	cat $LIBS_URLS_FULL_PATH | xargs git clone
	log "all repositories cloned properly!"
	popd > /dev/null
}

install_all() {
	check_file $LIBS_URLS_FNAME
	install_git_repos
}


all() {
	install_all
}

all
