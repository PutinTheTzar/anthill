#!/usr/bin/python3
import serial
import sys
import binascii

port = serial.Serial(
                port=sys.argv[1],
                baudrate=256000,
                parity=serial.PARITY_NONE,
                stopbits=serial.STOPBITS_ONE,
                rtscts = False,
                dsrdtr = False,
                timeout=1)

while 1:
    rb = port.read(1);
    print(binascii.hexlify(rb))
