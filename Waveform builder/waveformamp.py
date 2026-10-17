import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv("DSP_GuitarPedal_Waveform.csv")

fig, axes = plt.subplots(2, 1, figsize=(12, 7), sharex=True)

axes[0].plot(data["TimeSeconds"], data["Input"])
axes[0].set_title("Original Input Signal")
axes[0].set_ylabel("Amplitude")
axes[0].grid(True)

axes[1].plot(data["TimeSeconds"], data["Output"])
axes[1].set_title("Processed Output Signal")
axes[1].set_xlabel("Time (seconds)")
axes[1].set_ylabel("Amplitude")
axes[1].grid(True)

plt.tight_layout()
plt.savefig("DSP_Waveform.png", dpi=300)
plt.show()