# Week 3 Part 2 - Timer Interrupt Blink

**Name:** Abdullah  
**Roll No:** 23-NTU-CS-1005

## Description
This program sets up an ESP32 hardware timer to toggle an LED every 1 second using an interrupt.  
It demonstrates non-blocking LED control without using `delay()` functions.

## Components
- ESP32 Development Board  
- On-board LED (GPIO 5)

## Working
- The timer runs at a frequency of 1 MHz (1 tick = 1 microsecond).  
- An interrupt service routine (ISR) is attached to the timer.  
- Every 1,000,000 microseconds (1 second), the ISR executes and toggles the LED.  
- The `loop()` function remains empty, allowing the ESP32 to handle other tasks or enter low-power modes.

## Learning Outcomes
- Configuring hardware timers on ESP32  
- Writing and attaching interrupt service routines (ISRs)  
- Implementing non-blocking LED control using interrupts

## Code Author
**Abdullah**  
**Roll No:** 23-NTU-CS-1005
