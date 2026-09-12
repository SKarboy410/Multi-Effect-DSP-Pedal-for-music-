This project was for digital signal processing class. This is basically a digital guitar(or vocal too) processor akin to the software neuralDSP or other audio companies make. But the "technical" name of it would be Real-Time Digital Audio Effects Processor. This was made using C++ framework JUCE which is a framework which can used for anything music related. I have implemented 18 effects and also UI which has device selector and the effects with their respective control knobs. 

The hardware used for this project are:
- Electric guitar or microphone or any other electric instrument
- M-Audio M-Track Duo USB Audio Interface
- Cables(for mic to interface and 3.5mm to 6.5mm jack for earphones or headphones)

The 18 effects are as follows:
1. Gain: 
	Multiply input with gain factor
2. Noise gate
	Reduce unwanted low-level background noise by introducing a threshold, if the noise reaches or goes beyond the threshold then open the gate and let it through, otherwise close the gate.
	Also used attack and release to control the gate opening and close times and reactions.
3. Distortion
	Introduce a non-linear function(tanh used here) which compresses or clips the waveform toward a limit to get distortion.
4. Compressor
	If a signal reaches a certain sounds threshold then reduce its gain, also used attack and release concepts here
5. Auto wah
	my favorite, so first find absolute magnitude of the signal and then smoothen it, this creates an envelope. You can use attack, release and sensitivity to manipulate the shape further. Then convert the envelope into the filter cutoff frequency, pass it through a band-pass filter and get the good wah-wah
6. Equalizer(EQ)
	Essentially modifies the frequency balance of the signal, I implemented a basic 3 channel EQ where you can control lows, mids and highs.
7. Delay
	Uses memory here via a circular buffer. So the process goes like:
	input -> write to circular buffer -> read old sample -> mix current and previous input -> output
8. Chorus
	This is also a delay but it is modulated and shorter, instead of keeping a fixed delay we continuously change it using a low frequency oscillator(LFO). So process is:
	LFO -> delay time -> variable delay -> mix
9. Flanger
	Also very similar to chorus, but delay is shorter and feedback is added. Gives a weird metallic sound.
10. Reverb
	This uses multiple delays, feedback and mixing to emulate a real acoustic reverb where sound reflects back and forth becoming denser each time.
11. Tremolo
	This changes the amplitude over time, uses LFO to achieve.
12. Vibrato
	This changes the pitch overtime using read positions.
	so: LFO -> delay/read position -> small time variation -> pitch variation
13. Echo
	Repeated delay, where feedback is used to determine number of repeats and damping is used to make sure the echo fades
14. 3-Tap Echo
	Same thing as echo but using 3 different delay taps to get more complex echoes
15. Ring Modulator
	Here a carrier sine wave is generated and is multiplied with the input singal to get new frequency, typically output sounds alieny or metallic
16. Vocal Doubler
	Basically take the input dry signal, modify it with small pitch shift and time delay and mix with dry signal to get the multiple people performing effect
17. Pitch Shift
	This didn't really work for me due to the bare-bones implementation. But it uses the fundamental pitch ratio $Fout = Fin * 2^(semitones/12)$ 
	The implementation goes as follows: input -> delay buffer(to get frequency shift) -> move read position(to get the time same) ->  interpolate -> output
	so higher read speed is higher pitch and lower read speed is lower pitch 
18. Harmonizer
	Here 3 pitch shifters are used to create two kinds of harmony: Major and minor harmonies. Knowing a bit of music theory will help, but in layman terms, music theory represents pitch using semitones as the above equation suggests. 
	So for a major harmony, we take the dry input, add with +4(major third) and +7(perfect fifth) semitone signals creating a major harmony and for minor harmony, dry input, add with +3(minor or flat third) and +7(perfect fifth) semitone signals.

Overall this was pretty fun to make, although there are some big issues, mainly the real time part of it. Due to some driver issues there is noticeable delay between you play and when you hear. This can be fixed with proper drivers but I have found that JUCE crashes when you do that. Other issues include poor optimization/implementation of some effects, they are by no means professional(obviously), there are much better ways to implement these but since I was just doing it for fun and also for my course I didn't wanna go overfill with it(I mean it is very overkill for this course only).

Anyway thank for reading!
