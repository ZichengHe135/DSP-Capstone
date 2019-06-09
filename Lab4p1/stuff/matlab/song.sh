#! /bin/bash
chmod ugoa+wrx /dev/ttyUSB1 
#stty -F /dev/ttyUSB1 115200
#screen  /dev/ttyUSB1 115200 
echo -n -e '\x40\x40\x00' > /dev/ttyUSB1; sleep 0.2
echo -n -e '\x42\x42\x00' > /dev/ttyUSB1; sleep 0.2
echo -n -e '\x40\x40\x00' > /dev/ttyUSB1; sleep 0.2
echo -n -e '\x3e\x3e\x00' > /dev/ttyUSB1; sleep 0.2
echo -n -e '\x40\x40\x00' > /dev/ttyUSB1; sleep 0.2
echo -n -e '\x3e\x3e\x00' > /dev/ttyUSB1; sleep 0.2
echo -n -e '\x40\x40\x00' > /dev/ttyUSB1; sleep 0.2
echo -n -e '\x3e\x3e\x00' > /dev/ttyUSB1; sleep 0.2
echo -n -e '\x3b\x3b\x00' > /dev/ttyUSB1; sleep 0.2
echo -n -e '\x92\x92\x00' > /dev/ttyUSB1; sleep 0.2


