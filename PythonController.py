import time
import serial
ser = serial.Serial('COM27', 9600)
time.sleep(2)
while True:
    pixelLength = raw_input('How many pixels would you like to light up?: ')
    ser.write(pixelLength)
