#! /bin/bash
chmod ugoa+wrx /dev/ttyUSB1 
stty -F /dev/ttyUSB1 115200
#screen  /dev/ttyUSB1 115200 
#start playing minchoir4.u110 (aiff) for Obscure 90's reference to LMM SNES
echo -n -e '\xb0\xb0\x00' > /dev/ttyUSB1; sleep 3
echo -n -e '\xb0\xb0\x00' > /dev/ttyUSB1; sleep 0
echo -n -e '\x96\x96\x00' > /dev/ttyUSB1; sleep 0.2
echo -n -e '\xFF\xFF\x00' > /dev/ttyUSB1; sleep 0.2

echo -n -e '\x37\x37\x00' > /dev/ttyUSB1; sleep 2
echo -n -e '\x36\x36\x00' > /dev/ttyUSB1; sleep 2
echo -n -e '\x37\x37\x00' > /dev/ttyUSB1; sleep 2
echo -n -e '\x3a\x3a\x00' > /dev/ttyUSB1; sleep 2
echo -n -e '\x37\x37\x00' > /dev/ttyUSB1; sleep 2
echo -n -e '\x36\x36\x00' > /dev/ttyUSB1; sleep 2
echo -n -e '\x32\x32\x00' > /dev/ttyUSB1; sleep 2
echo -n -e '\x35\x35\x00' > /dev/ttyUSB1; sleep 2
echo -n -e '\x37\x37\x00' > /dev/ttyUSB1; sleep 2
