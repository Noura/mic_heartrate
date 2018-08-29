import serial
import csv
import heartbeat as hb
import matplotlib.pyplot as plt

# serial connection
ser = serial.Serial('/dev/ttyACM0', 9600)

# sample rate in Hz, we magically know this by peeking at the Arduino file :B
sample_rate = 50  # must match Arduino code
max_samples = 1000 # a setting we can tweak

filename = "latest_data.csv"

s = [] # samples saved here
N = 0 # number of samples. should match size(s) but don't want to call that like all the time

while N < max_samples:
    read_serial = ser.readline()
    try:
        sample = float(read_serial)
        s.append(sample)
        print N, ' ', sample
        N = N + 1
    except:
        pass

plt.ylabel("Amplitude")
plt.plot(s[300:])
plt.show()

with open(filename, 'w') as output:
    writer = csv.writer(output)
    for val in s[300:]:
        writer.writerow([val])

# data = hb.get_data(filename)
# measures = hb.process(data, sample_rate)

# print measures['bpm']

