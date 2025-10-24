# Week 3 Part 1 - Timer Controlled LED

**Name:** Abdullah  
**Roll No:** 23-NTU-CS-1005  

## Description
This project uses an ESP32 hardware timer and an external button interrupt to control an LED.  
The LED blinks every 0.5 seconds when enabled, and the button toggles the blinking on or off.  
A simple debounce logic is included to avoid false button triggers.

## Components
- ESP32 Development Board  
- On-board LED (GPIO 5)  
- Push Button (GPIO 34)

## Working
- A hardware timer is configured to tick at 1 MHz.  
- The timer interrupt toggles the LED every 500,000 microseconds (0.5 seconds).  
- The button interrupt toggles a flag (`ledEnabled`) to enable or disable the blinking.  
- Debounce is implemented using `millis()` to prevent multiple toggles from one press.  
- The LED automatically resets to LOW when disabled.

## Learning Outcomes
- Using ESP32 hardware timers  
- Configuring and using interrupt service routines (ISRs)  
- Implementing debounce in interrupt-based input handling  
- Combining timer and GPIO interrupts for multitasking behavior

## Code Author
**Abdullah**  
**Roll No:** 23-NTU-CS-1005
