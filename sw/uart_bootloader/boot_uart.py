#!/usr/bin/python3
import os
import sys
import argparse
import time
import serial

parser = argparse.ArgumentParser(prog='boot_uart')
parser.add_argument('program_bin', type=argparse.FileType('rb'), help='bin file to boot')
parser.add_argument('port', help='serial port device')
args = parser.parse_args()

ser = serial.Serial(port=args.port,baudrate=115200, parity=serial.PARITY_NONE, stopbits=serial.STOPBITS_ONE,timeout=1)
print('Bootloader ready')
ser.reset_input_buffer()
ser.reset_output_buffer()

while(ser.read(1) != b'B'): pass
while(ser.read(1) != b'o'): pass
while(ser.read(1) != b'o'): pass
while(ser.read(1) != b't'): pass
while(ser.read(1) != b'?'): pass

time.sleep(0.01)
print('Bootloader start')
ser.write(b'Y')

while(ser.read(1) != b'O'): pass
while(ser.read(1) != b'K'): pass

len = os.fstat(args.program_bin.fileno()).st_size
print('Bootloader OK, writing %d bytes.' % len)
byte_len = len.to_bytes(4, byteorder='little')
ser.write(byte_len)

ser.write(args.program_bin.read(len))

print("%d bytes programmed." % len)
while(ser.read(1) != b'G'): pass
while(ser.read(1) != b'o'): pass
while(ser.read(1) != b'!'): time.sleep(100e-6)

print('Programming done!')
ser.close()
args.program_bin.close()
