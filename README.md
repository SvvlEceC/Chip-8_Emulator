# CHIP-8 Emulator (SDL)

A simple **CHIP-8 emulator** implemented in **C/C++** using **SDL2** for
graphics, audio, and input handling.

This project was developed to gain hands-on experience with low-level systems,
CPU emulation, and real-time rendering.

> Educational project – not intended to be cycle-accurate.

---

## Features
- Full CHIP-8 instruction set
- 4 KB memory
- 16 8-bit registers (V0–VF)
- Index register, program counter, and stack
- Delay and sound timers
- SDL 64×32 monochrome display
- SDL keyboard input
- SDL audio output

---

## Architecture Overview
- **CPU**: Fetch–decode–execute loop with bitwise opcode decoding
- **Graphics**: Framebuffer mapped to SDL texture
- **Input**: CHIP-8 keypad mapped to keyboard keys via SDL
- **Audio**: Simple beep sound generated through SDL audio callbacks
