#! /bin/bash
chmod ugoa+wrx /dev/ttyUSB1 
stty -F /dev/ttyUSB1 115200
#screen  /dev/ttyUSB1 115200 
# polyphony!

echo -n -e '\xff\xff\x00' > /dev/ttyUSB1; sleep 0.1
echo -n -e '\xa7\xa7\xa7\x00' > /dev/ttyUSB1; sleep 0.05

echo -n -e '\x90\x90\x90\x00' > /dev/ttyUSB1; sleep 0.05

echo -n -e '\x40\x40\x40\x00' > /dev/ttyUSB1; sleep 0.05

echo -n -e '\x91\x91\x91\x00' > /dev/ttyUSB1; sleep 0.05
echo -n -e '\x3e\x3e\x3e\x00' > /dev/ttyUSB1; sleep 0.05

echo -n -e '\x92\x92\x92\x00' > /dev/ttyUSB1; sleep 0.05
echo -n -e '\x3b\x3b\x3b\x00' > /dev/ttyUSB1; sleep 0.05

echo -n -e '\x93\x93\x93\x00' > /dev/ttyUSB1; sleep 0.05
echo -n -e '\x38\x38\x38\x00' > /dev/ttyUSB1; sleep 0.05

echo -n -e '\x94\x94\x94\x00' > /dev/ttyUSB1; sleep 0.05
echo -n -e '\x34\x34\x34\x00' > /dev/ttyUSB1; sleep 0.05

echo -n -e '\x95\x95\x95\x00' > /dev/ttyUSB1; sleep 0.05
echo -n -e '\x2f\x2f\x2f\x00' > /dev/ttyUSB1; sleep 0.05

echo -n -e '\x96\x96\x96\x00' > /dev/ttyUSB1; sleep 0.05
echo -n -e '\x31\x31\x31\x00' > /dev/ttyUSB1; sleep 8
echo -n -e '\xff\xff\xff\x00' > /dev/ttyUSB1


