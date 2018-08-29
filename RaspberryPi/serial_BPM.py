import serial

ser = serial.Serial('/dev/ttyACM0', 9600)
s = [0]

while True:
    read_serial = ser.readline()
    try:
        sample = float(read_serial)
        print sample
    except:
        pass


