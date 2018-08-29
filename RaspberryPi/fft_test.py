import numpy as np
import matplotlib.pyplot as plt

t = np.linspace(0, 10.0, 500)
s = np.sin(1 * 2 * np.pi * t) + 0.5 * np.sin(1.3 * 2 * np.pi * t)

plt.ylabel("Amplitude")
plt.xlabel("Time")
plt.plot(t, s)
plt.show()

fft = np.fft.fft(s)

T = t[1] - t[0]
N = s.size
freqs = np.linspace(0, 1 / T, N)

combined = zip(freqs[:N // 2], np.abs(fft)[:N // 2] * 1/N)
print combined

# plt.ylabel("Amplitude")
# plt.xlabel("Frequency [Hz]")
# plt.bar(freqs[:N // 2], np.abs(fft)[:N // 2] * 1/N, width=1.5)
# plt.show()
