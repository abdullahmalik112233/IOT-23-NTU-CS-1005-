# Week 4 Part 1 - Hardware Timer LED

**Name:** Abdullah  
**Roll No:** 23-NTU-CS-1005  

## Description
This project demonstrates how to toggle an LED every 1 second using one of the ESP32’s hardware timers.  
It’s a simple example of interrupt-driven LED blinking without using any delay functions, keeping the main loop free for other tasks.

## Components
- ESP32 Development Board  
- On-board or external LED (GPIO 2)

## Working
1. The ESP32 hardware timer is initialized with a 1 MHz tick (using a prescaler of 80).  
2. An interrupt service routine (ISR) toggles the LED every 1,000,000 microseconds (1 second).  
3. The `loop()` remains empty, demonstrating non-blocking code.  
4. This method allows precise timing without affecting other running tasks.

## Learning Outcomes
- Configuring and using ESP32 hardware timers  
- Understanding timer prescalers and microsecond intervals  
- Implementing non-blocking LED toggling  
- Working with timer interrupts on ESP32

## Code Author
**Abdullah**  
**Roll No:** 23-NTU-CS-1005
