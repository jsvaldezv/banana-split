# 🍌 Banana Split

Banana Split is a two-part project consisting of:

1. A FM Synthesizer VST/AU plug-in, developed in JUCE and C++
2. A custom-built MIDI controller, using Arduino and Makey Makey with conductive gummies

## 🎹 FM Synthesizer Plug-in

https://github.com/user-attachments/assets/e24bfa4b-439c-4c78-ba60-799686325975

The synthesizer is an FM-based virtual instrument built using the JUCE framework and C++. Its features include:

1. One oscillator with selectable waveforms: Sine, Saw, Triangle, and Square
2. Gain control for the oscillator
3. ADSR envelope (Attack, Decay, Sustain, Release)
4. Built-in audio effects: Reverb, Delay, Chorus, Distortion

## 🎛️ DIY MIDI Controller

![WhatsApp Image 2022-06-03 at 12 24 42 AM](https://user-images.githubusercontent.com/47612276/171791873-331c2f56-c4bf-4697-a04e-f2e5aea18518.jpeg)

The MIDI controller was built using Arduino and Makey Makey, allowing for a playful and tactile interaction using conductive candies.

### Components Used:

* Arduino MEGA
* Protoboard
* 12 push buttons
* Jumpers or cables
* USB Cable
* 6 pots
* Makey Makey
* 6 conductive objects (gummies)
* Arduino IDE
* Hairless MIDI

The Arduino sends MIDI messages via serial using Hairless MIDI, enabling real-time control of the synthesizer parameters.
