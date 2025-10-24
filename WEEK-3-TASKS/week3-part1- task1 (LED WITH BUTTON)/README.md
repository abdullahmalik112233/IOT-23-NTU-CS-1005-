# Week 3 Part 1 - Timer Controlled LED

**Name:** Abdullah
**Roll No:** 23-NTU-CS-1005  

## Description
This project uses an ESP32 hardware timer to blink an LED every 0.5 seconds using timer interrupts.  
The LED toggles only when the button is enabled — pressing the button toggles the LED on/off functionality.

## Components
- ESP32 Development Board
- On-board LED (GPIO 5)
- Push Button (GPIO 34)

## Working
- The hardware timer runs at 1 MHz.
- An interrupt service routine toggles the LED every 0.5 seconds.
- Another ISR detects button presses and enables or disables LED blinking.
- Software debounce prevents false triggers.

## Learning Outcomes
- Using ESP32 hardware timers
- Working with interrupts and debounce logic
- Combining multiple ISRs safely
