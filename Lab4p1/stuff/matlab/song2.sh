#! /bin/bash
chmod ugoa+wrx /dev/ttyUSB1 
stty -F /dev/ttyUSB1 115200
#screen  /dev/ttyUSB1 115200 
echo -n -e '\x92\x92\x00' > /dev/ttyUSB1; sleep 0.2

echo -n -e '\x40\x40\x00' > /dev/ttyUSB1; sleep 0.2
echo -n -e '\xFF\xFF\x00' > /dev/ttyUSB1; sleep 0.2

echo -n -e '\x80\x80\x00' > /dev/ttyUSB1; sleep 0.2
echo -n -e '\x40\x40\x00' > /dev/ttyUSB1; sleep 0.2
echo -n -e '\xFF\xFF\x00' > /dev/ttyUSB1; sleep 0.2
echo -n -e '\x80\x80\x00' > /dev/ttyUSB1; sleep 0.2

echo -n -e '\x81\x81\x00' > /dev/ttyUSB1; sleep 0.2
echo -n -e '\x40\x40\x00' > /dev/ttyUSB1; sleep 0.2
echo -n -e '\xFF\xFF\x00' > /dev/ttyUSB1; sleep 0.3  
echo -n -e '\x81\x81\x00' > /dev/ttyUSB1; sleep 0.2

echo -n -e '\x82\x82\x00' > /dev/ttyUSB1; sleep 0.2
echo -n -e '\x40\x40\x00' > /dev/ttyUSB1; sleep 1.2
echo -n -e '\xFF\xFF\x00' > /dev/ttyUSB1; sleep 1  
echo -n -e '\x82\x82\x00' > /dev/ttyUSB1; sleep 0.2

echo -n -e '\x83\x83\x00' > /dev/ttyUSB1; sleep 0.2
echo -n -e '\x40\x40\x00' > /dev/ttyUSB1; sleep 1.2
echo -n -e '\xFF\xFF\x00' > /dev/ttyUSB1; sleep 1 
echo -n -e '\x83\x83\x00' > /dev/ttyUSB1; sleep 0.2

echo -n -e '\x84\x84\x00' > /dev/ttyUSB1; sleep 0.2
echo -n -e '\x40\x40\x00' > /dev/ttyUSB1; sleep 0.2
echo -n -e '\xFF\xFF\x00' > /dev/ttyUSB1; sleep 1 
echo -n -e '\x84\x84\x00' > /dev/ttyUSB1; sleep 0.2

echo -n -e '\x85\x85\x00' > /dev/ttyUSB1; sleep 0.2
echo -n -e '\x40\x40\x00' > /dev/ttyUSB1; sleep 0.2
echo -n -e '\xFF\xFF\x00' > /dev/ttyUSB1; sleep 1 
echo -n -e '\x85\x85\x00' > /dev/ttyUSB1; sleep 0.2

echo -n -e '\x86\x86\x00' > /dev/ttyUSB1; sleep 0.2
echo -n -e '\x40\x40\x00' > /dev/ttyUSB1; sleep 0.2
echo -n -e '\xFF\xFF\x00' > /dev/ttyUSB1; sleep 1 
echo -n -e '\x86\x86\x00' > /dev/ttyUSB1; sleep 0.2

echo -n -e '\x87\x87\x00' > /dev/ttyUSB1; sleep 0.2
echo -n -e '\x40\x40\x00' > /dev/ttyUSB1; sleep 0.2
echo -n -e '\xFF\xFF\x00' > /dev/ttyUSB1; sleep 1 
echo -n -e '\x87\x87\x00' > /dev/ttyUSB1; sleep 0.2

echo -n -e '\x88\x88\x00' > /dev/ttyUSB1; sleep 0.2
echo -n -e '\x40\x40\x00' > /dev/ttyUSB1; sleep 0.2
echo -n -e '\xFF\xFF\x00' > /dev/ttyUSB1; sleep 1 
echo -n -e '\x88\x88\x00' > /dev/ttyUSB1; sleep 0.2

echo -n -e '\x89\x89\x00' > /dev/ttyUSB1; sleep 0.2
echo -n -e '\x40\x40\x00' > /dev/ttyUSB1; sleep 0.2
echo -n -e '\xFF\xFF\x00' > /dev/ttyUSB1; sleep 3  
echo -n -e '\x89\x89\x00' > /dev/ttyUSB1; sleep 0.2




echo -n -e '\x30\x30\x00' > /dev/ttyUSB1; sleep 0.05
echo -n -e '\x37\x37\x00' > /dev/ttyUSB1; sleep 0.05
echo -n -e '\x3c\x3c\x00' > /dev/ttyUSB1; sleep 0.05
echo -n -e '\x43\x43\x00' > /dev/ttyUSB1; sleep 0.05

echo -n -e '\x30\x30\x00' > /dev/ttyUSB1; sleep 0.05
echo -n -e '\x37\x37\x00' > /dev/ttyUSB1; sleep 0.05
echo -n -e '\x3c\x3c\x00' > /dev/ttyUSB1; sleep 0.05
echo -n -e '\x43\x43\x00' > /dev/ttyUSB1; sleep 0.05

echo -n -e '\x30\x30\x00' > /dev/ttyUSB1; sleep 0.05
echo -n -e '\x37\x37\x00' > /dev/ttyUSB1; sleep 0.05
echo -n -e '\x3c\x3c\x00' > /dev/ttyUSB1; sleep 0.05
echo -n -e '\x43\x43\x00' > /dev/ttyUSB1; sleep 0.05

echo -n -e '\x30\x30\x00' > /dev/ttyUSB1; sleep 0.05
echo -n -e '\x38\x38\x00' > /dev/ttyUSB1; sleep 0.05
echo -n -e '\x3c\x3c\x00' > /dev/ttyUSB1; sleep 0.05
echo -n -e '\x44\x44\x00' > /dev/ttyUSB1; sleep 0.05

echo -n -e '\x30\x30\x00' > /dev/ttyUSB1; sleep 0.05
echo -n -e '\x37\x37\x00' > /dev/ttyUSB1; sleep 0.05
echo -n -e '\x3c\x3c\x00' > /dev/ttyUSB1; sleep 0.05
echo -n -e '\x43\x43\x00' > /dev/ttyUSB1; sleep 0.05
echo -n -e '\x30\x30\x00' > /dev/ttyUSB1; sleep 0.05
echo -n -e '\x38\x38\x00' > /dev/ttyUSB1; sleep 0.05
echo -n -e '\x3c\x3c\x00' > /dev/ttyUSB1; sleep 0.05
echo -n -e '\x44\x44\x00' > /dev/ttyUSB1; sleep 0.05

echo -n -e '\x30\x30\x00' > /dev/ttyUSB1; sleep 0.05
echo -n -e '\x37\x37\x00' > /dev/ttyUSB1; sleep 0.05
echo -n -e '\x3c\x3c\x00' > /dev/ttyUSB1; sleep 0.05
echo -n -e '\x43\x43\x00' > /dev/ttyUSB1; sleep 0.05
echo -n -e '\xff\xff\x00' > /dev/ttyUSB1; sleep 0.05

	
echo -n -e '\x81\x81\x00' > /dev/ttyUSB1; sleep 0
echo -n -e '\x83\x83\x00' > /dev/ttyUSB1; sleep 0
	echo -n -e '\x91\x91\x00' > /dev/ttyUSB1; sleep 0
for run in {1..10}
do
	echo -n -e '\x1b\x1b\x00' > /dev/ttyUSB1; sleep 2
	echo -n -e '\x16\x16\x00' > /dev/ttyUSB1; sleep 2
	echo -n -e '\x1b\x1b\x00' > /dev/ttyUSB1; sleep 2
	echo -n -e '\x1c\x1c\x00' > /dev/ttyUSB1; sleep 2
done

echo -n -e '\x92\x92\x00' > /dev/ttyUSB1; sleep 0.2




