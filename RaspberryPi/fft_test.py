import numpy as np
import matplotlib.pyplot as plt

t = np.linspace(0, 0.5, 500)
s = np.sin(40 * 2 * np.pi * t) + 0.5 * np.sin(90 * 2 * np.pi * t)

fft = np.fft.fft(s)

T = t[1] - t[0]
N = s.size
freqs = np.linspace(0, 1 / T, N)

plt.ylabel("Amplitude")
plt.xlabel("Freq [Hz]")
plt.bar(freqs[:N // 2], np.abs(fft)[:N // 2] * 1/N, width=1.5)
plt.show()
