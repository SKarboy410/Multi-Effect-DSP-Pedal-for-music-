This project was for digital signal processing class. This is basically a digital guitar(or vocal too) processor akin to the software neuralDSP or other audio companies make. But the "technical" name of it would be Real-Time Digital Audio Effects Processor. This was made using C++ framework JUCE which is a framework which can used for anything music related. I have implemented 18 effects and also UI which has device selector and the effects with their respective control knobs. 

The hardware used for this project are:
- Electric guitar or microphone or any other electric instrument
- M-Audio M-Track Duo USB Audio Interface
- Cables(for mic to interface and 3.5mm to 6.5mm jack for earphones or headphones)

The 18 effects are as follows:
### 1. Gain

Multiply input with gain factor.

### 2. Noise Gate

Reduce unwanted low-level background noise by introducing a threshold, if the noise reaches or goes beyond the threshold then open the gate and let it through, otherwise close the gate.

Also used **attack** and **release** to control the gate opening and close times and reactions.

### 3. Distortion

Introduce a non-linear function (`tanh` used here) which compresses or clips the waveform toward a limit to get distortion.

### 4. Compressor

If a signal reaches a certain sounds threshold then reduce its gain, also used attack and release concepts here.

### 5. Auto Wah

My favorite, so first find absolute magnitude of the signal and then smoothen it, this creates an envelope. You can use attack, release and sensitivity to manipulate the shape further.

Then convert the envelope into the filter cutoff frequency, pass it through a band-pass filter and get the good wah-wah.

### 6. Equalizer (EQ)

Essentially modifies the frequency balance of the signal, I implemented a basic 3 channel EQ where you can control lows, mids and highs.

### 7. Delay

Uses memory here via a circular buffer.

So the process goes like:

```text
input -> write to circular buffer -> read old sample -> mix current and previous input -> output
```

### 8. Chorus

This is also a delay but it is modulated and shorter, instead of keeping a fixed delay we continuously change it using a low frequency oscillator (LFO).

So process is:

```text
LFO -> delay time -> variable delay -> mix
```

### 9. Flanger

Also very similar to chorus, but delay is shorter and feedback is added. Gives a weird metallic sound.

### 10. Reverb

This uses multiple delays, feedback and mixing to emulate a real acoustic reverb where sound reflects back and forth becoming denser each time.

### 11. Tremolo

This changes the amplitude over time, uses LFO to achieve.

### 12. Vibrato

This changes the pitch overtime using read positions.

So:

```text
LFO -> delay/read position -> small time variation -> pitch variation
```

### 13. Echo

Repeated delay, where feedback is used to determine number of repeats and damping is used to make sure the echo fades.

### 14. 3-Tap Echo

Same thing as echo but using 3 different delay taps to get more complex echoes.

### 15. Ring Modulator

Here a carrier sine wave is generated and is multiplied with the input singal to get new frequency, typically output sounds alieny or metallic.

### 16. Vocal Doubler

Basically take the input dry signal, modify it with small pitch shift and time delay and mix with dry signal to get the multiple people performing effect.

### 17. Pitch Shift

This didn't really work for me due to the bare-bones implementation.

But it uses the fundamental pitch ratio:

```text
Fout = Fin * 2^(semitones/12)
```

The implementation goes as follows:

```text
input -> delay buffer(to get frequency shift) -> move read position(to get the time same) -> interpolate -> output
```

So higher read speed is higher pitch and lower read speed is lower pitch.

### 18. Harmonizer

Here 3 pitch shifters are used to create two kinds of harmony: **Major** and **minor** harmonies.

Knowing a bit of music theory will help, but in layman terms, music theory represents pitch using semitones as the above equation suggests.

So for a major harmony, we take the dry input, add with **+4 (major third)** and **+7 (perfect fifth)** semitone signals creating a major harmony.

For minor harmony, dry input, add with **+3 (minor or flat third)** and **+7 (perfect fifth)** semitone signals.

---
<details>
<summary><strong>Installation and Setup</strong></summary>

### Requirements

Before building the project, install:

* **Git**
* **JUCE**
* **CMake**
* **Visual Studio 2022** with the **Desktop development with C++** workload
* An **audio interface** for real-time audio processing

### 1. Install JUCE

Download JUCE from the official website:

[Download JUCE](https://juce.com/get-juce/?utm_source=chatgpt.com)

Extract the JUCE folder to a convenient location.

For example:

```text
C:\JUCE
```

### 2. Install CMake

Download and install CMake:

[Download CMake](https://cmake.org/download/?utm_source=chatgpt.com)

During installation, enable the option to **Add CMake to the system PATH** if available.

Verify the installation:

```bash
cmake --version
```

### 3. Install Visual Studio

Download Visual Studio:

[Download Visual Studio](https://visualstudio.microsoft.com/downloads/?utm_source=chatgpt.com)

During installation, select:

**Desktop development with C++**

Make sure the MSVC compiler and Windows SDK are installed.

### 4. Clone the Repository

Open Git Bash, Command Prompt, or PowerShell and run:

```bash
git clone https://github.com/SKarboy410/Multi-Effect-DSP-Pedal-for-music.git
```

Navigate into the project:

```bash
cd Multi-Effect-DSP-Pedal-for-music
```

### 5. Configure the JUCE Path

The project requires JUCE to be available locally.

If the project's `CMakeLists.txt` expects a specific JUCE location, make sure the JUCE path matches your installation.

For example:

```text
C:\JUCE
```

The JUCE installation should contain the required modules:

```text
C:\JUCE
└── modules
```

### 6. Create a Build Directory

From the project root, create a separate build directory:

```bash
mkdir build
cd build
```

Keeping the build files separate from the source files makes it easier to clean and rebuild the project.

### 7. Configure the CMake Project

Run CMake:

```bash
cmake ..
```

If multiple Visual Studio versions are installed, you can explicitly select the Visual Studio generator.

For Visual Studio 2022:

```bash
cmake .. -G "Visual Studio 17 2022"
```

CMake will generate the Visual Studio solution and project files.

### 8. Build the Application

Build the project in Release mode:

```bash
cmake --build . --config Release
```

Alternatively, open the generated Visual Studio solution and build it from Visual Studio.

### 9. Run the Application

After a successful build, run the generated standalone application.

The executable will be located inside the generated build directory, typically under the appropriate `Release` directory.

You can also run the application directly from Visual Studio.

### 10. Connect an Audio Interface

For guitar processing, use the following setup:

```text
Guitar
   ↓
Audio Interface Input
   ↓
Computer
   ↓
Multi-Effect DSP Pedal
   ↓
Audio Interface Output
   ↓
Headphones / Speakers / Amplifier
```

An audio interface is recommended for reliable real-time audio input and output.

### 11. Configure Audio Input and Output

Launch the application and configure the audio device using the application's audio settings.

Select:

* **Input Device:** Audio interface
* **Input Channel:** Channel connected to the guitar
* **Output Device:** Audio interface
* **Output Channel:** Channel connected to headphones/speakers

For example:

```text
Input Channel 1  → Guitar
Output Channel 1 → Headphones
```

### 12. Set the Input Level

Play the guitar and adjust the input gain on the audio interface.

Set the level high enough for a clear signal while avoiding clipping.

Start with a low output volume and increase it gradually.

### 13. Start Processing

Once the audio device is configured:

1. Play the guitar.
2. Confirm that the input signal is being received.
3. Enable the desired effects.
4. Adjust the parameters.
5. Monitor the processed signal through headphones, speakers, or an amplifier.

> **Tip:** Headphones are recommended during initial testing to prevent acoustic feedback.

### Troubleshooting

**CMake cannot find JUCE**

Check the JUCE path expected by the project and make sure it points to your JUCE installation.

**CMake configuration fails**

Make sure CMake and Visual Studio's C++ development tools are installed correctly.

**Visual Studio build fails**

Make sure the **Desktop development with C++** workload and Windows SDK are installed.

**No audio output**

Check the selected input/output device, input channel, audio interface connection, and interface volume.

**No input signal**

Make sure the guitar is connected to the selected input channel and that the audio interface is receiving signal.

**Audio is clipping**

Reduce the input gain on the audio interface.

**Feedback occurs**

Use headphones or reduce the output volume while testing.

</details>

Overall this was pretty fun to make, although there are some big issues, mainly the real time part of it. Due to some driver issues there is noticeable delay between you play and when you hear. This can be fixed with proper drivers but I have found that JUCE crashes when you do that. Other issues include poor optimization/implementation of some effects, they are by no means professional(obviously), there are much better ways to implement these but since I was just doing it for fun and also for my course I didn't wanna go overfill with it(I mean it is very overkill for this course only).

Anyway thank for reading!
