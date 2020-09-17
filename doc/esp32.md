# ESP32 board code

### setup & compilation, upload

ESP32 is compatible with Arduino, however Arduino IDE lacks some lovely features like code navigation, therefore we need possiblity to easily compile and upload code, while using another, more user friendly IDE.
Happily, there exists utility called **arduino-cli**, allowing compilation and code upload without Arduino IDE.

Both configuration and running phase are performed using Makefile attached.

`make config` - run it once, it installs and configs arduino-cli and esp32 library in current working directory.
`make run` - it compiles and uploads code to board.

Remark, that there are some customizable variables in Makefile like PROJECT\_NAME.


### Adding library

To add new library simply add URL with library json to `arduino-cli.yaml` file
