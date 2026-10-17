
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# Load the CSV exported by your JUCE application
data = pd.read_csv("DSP_GuitarPedal_Waveform.csv")

input_signal = data["Input"].to_numpy(dtype=float)
output_signal = data["Output"].to_numpy(dtype=float)
time = data["TimeSeconds"].to_numpy(dtype=float)

# Estimate sample rate from the recorded timestamps
sample_rate = 1.0 / np.mean(np.diff(time))

def calculate_spectrum(signal, sample_rate):
    # Remove DC offset and reduce spectral leakage
    signal = signal - np.mean(signal)
    window = np.hanning(len(signal))
    windowed_signal = signal * window

    # Calculate the one-sided FFT magnitude
    fft_values = np.fft.rfft(windowed_signal)
    magnitude = np.abs(fft_values) / np.sum(window)

    if len(magnitude) > 2:
        magnitude[1:-1] *= 2

    frequencies = np.fft.rfftfreq(
        len(signal), d=1.0 / sample_rate
    )

    magnitude_db = 20 * np.log10(
        np.maximum(magnitude, 1e-10)
    )

    return frequencies, magnitude_db

freq_in, db_in = calculate_spectrum(input_signal, sample_rate)
freq_out, db_out = calculate_spectrum(output_signal, sample_rate)

# Plot both spectra using the same scale
plt.figure(figsize=(12, 6))
plt.plot(freq_in, db_in, label="Original Input")
plt.plot(freq_out, db_out, label="Auto-Wah Output")

plt.title("Auto-Wah: Input vs Output Frequency Spectrum")
plt.xlabel("Frequency (Hz)")
plt.ylabel("Magnitude (dB)")
plt.xlim(0, min(10000, sample_rate / 2))
plt.grid(True, alpha=0.3)
plt.legend()
plt.tight_layout()
plt.show()
