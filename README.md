# Maze Game - ATmega128

An embedded systems maze game developed for the ATmega128 microcontroller. Navigate through procedurally defined mazes using a joystick or keyboard controls, displayed on a GLCD screen.

## Overview

This project is an embedded game written in C for the ATmega128 microcontroller. Players navigate a circular player icon through maze levels of varying difficulty, with the goal of reaching the exit as quickly as possible. The game features multiple difficulty levels, joystick and keyboard controls, and a timer to track completion time.

## Features

- **4 Difficulty Levels**: Easy, Medium, Difficult, and Random
- **Dual Control Options**: Joystick (analog) and keyboard (WASD via UART)
- **GLCD Display**: 128x64 pixel graphical LCD for maze visualization
- **Timer System**: Tracks time spent completing each maze
- **Touch Sensor**: Quick exit from current game
- **Reset Button**: External interrupt for game reset

## Hardware Requirements

- ATmega128 microcontroller
- 128x64 GLCD (Graphical LCD)
- Analog joystick (connected to ADC channels 3 & 4)
- Touch sensor (connected to PC3)
- Reset button (connected to INT0)
- UART connection for keyboard input (optional)

## Controls

### Joystick
- Move the joystick in any direction to navigate the player through the maze

### Keyboard (via UART)
| Key | Action |
|-----|--------|
| W | Move Up |
| A | Move Left |
| S | Move Down |
| D | Move Right |

### Menu Navigation
- Use joystick up/down to select difficulty level (1-4)
- Press PD7 button to start the selected level

## Game Flow

1. **Banner Screen**: Displays game title and team member IDs
2. **Level Selection**: Choose from 4 difficulty levels
3. **Gameplay**: Navigate the maze to reach the exit (bottom-right corner)
4. **Victory Screen**: Shows completion time in seconds

## Maze Levels

| Level | Description |
|-------|-------------|
| 1 - Easy | Simple serpentine path |
| 2 - Medium | More complex corridors with dead ends |
| 3 - Difficult | Intricate maze with multiple paths (2 variations) |
| 4 - Random | Randomly selects from levels 1-3 |

## Technical Details

- **Display Resolution**: 128x64 pixels
- **Player Size**: 2-pixel radius circle
- **Maze Representation**: 64-bit integers per row (128 rows total)
- **Joystick Dead Zone**: 10 units (prevents drift)
- **Timer Interrupt**: ~60Hz for second counting

## Project Structure

```
maze-game-atmega128/
├── Main/
│   ├── Main.c              # Main entry point with mode selection
│   ├── main_project.c      # Maze game implementation
│   ├── config.h            # Configuration and includes
│   ├── _glcd.c/h           # GLCD driver
│   ├── _adc.c/h            # ADC driver (joystick)
│   ├── _uart.c/h           # UART driver (keyboard)
│   ├── _timer2.c/h         # Timer driver
│   ├── _interrupt.c/h      # Interrupt handlers
│   └── ...                 # Other hardware drivers
├── Main.atsln              # Atmel Studio solution file
├── Simulator.sim1          # SimulIDE simulation file
└── README.md
```

## Building

1. Open `Main.atsln` in Atmel Studio
2. Define `EMBEDDED_PROJECT` in `config.h` to enable maze game mode
3. Build the project (F7)
4. Flash to ATmega128 microcontroller

## Simulation

The project includes SimulIDE simulation files (`Simulator.sim1`, `Simulator.simu`) for testing without physical hardware.

## Team

- U2110077
- U2110222
- U2110283
- U2110285

## References

- [ATmega128 Datasheet](https://ww1.microchip.com/downloads/en/DeviceDoc/doc2467.pdf)
