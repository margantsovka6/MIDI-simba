# MIDI-Simba 🎹⚡

Turn a toy **SIMBA** children's keyboard into a fully functional **USB MIDI controller** using an **Arduino Pro Micro**!

This project gives a second life to a toy synthesizer by interfacing its keyboard matrix directly with an Arduino Pro Micro board to communicate with any modern Digital Audio Workstation (DAW) over USB MIDI.

---

## 📸 Overview

![SIMBA Toy Keyboard](images/5271965660722437379.jpg)

---

## 🚀 Features

- **Plug-and-Play USB MIDI**: Recognized as a native MIDI device by FL Studio, Ableton Live, Logic Pro, Reaper, and other DAWs.
- **Full Matrix Scan**: Translates the 4x8 ribbon cable matrix into 32 distinct MIDI note events.
- **Compact & Budget-Friendly**: Utilizes the ATmega32U4-based Arduino Pro Micro.

---

## ⚠️ Important Note: Ghosting / Phantom Key Presses

Due to the internal wiring and design of the original toy synthesizer keyboard matrix (which lacks isolation diodes for each key), **phantom key presses (ghosting) may occur when pressing more than 3 keys simultaneously**. 

This device works best for monophonic lines, simple chords, or melismatic playing.

---

## 🗂 Ribbon Cable & Note Mapping

The keyboard uses a **4-row × 8-column** matrix (12 ribbon lines total). 

### Note Layout
The keyboard matrix covers a 32-note range starting from **C6** down to **F3**:

| Ribbon Line | Key / Note |
| :---: | :---: |
| **1** | C6 |
| **2** | B5 |
| **3** | A#5 |
| **4** | A5 |
| **5** | G#5 |
| **6** | G5 |
| **7** | F#5 |
| **8** | F5 |
| **9** | E5 |
| **10** | D#5 |
| **11** | D5 |
| **12** | *...and so on down to F3* |

---

## 🎹 MIDI Note Matrix Table

Below is the 4x8 MIDI note map array corresponding to the matrix rows and columns:

```cpp
const uint8_t noteMap[4][8] = {
    {72, 71, 70, 69, 68, 67, 66, 65}, // Row 1 (C6 - F5)
    {64, 63, 62, 61, 60, 59, 58, 57}, // Row 2 (E5 - A4)
    {56, 55, 54, 53, 52, 51, 50, 49}, // Row 3 (G#4 - C#4)
    {48, 47, 46, 45, 44, 43, 42, 41}  // Row 4 (C4 - F3)
};


