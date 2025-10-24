# Week 3 Part 1 - Q2 Dual LED Button Control

**Name:** Abdullah  
**Roll No:** 23-NTU-CS-1005  

## Description
This project demonstrates how to control two LEDs using a single push button with interrupt functionality on the ESP32.  
Each button press toggles both LEDs simultaneously, turning them ON or OFF together.

## Components
- ESP32 Development Board  
- LED 1 (GPIO 18)  
- LED 2 (GPIO 21)  
- Push Button (GPIO 35)

## Working
1. The push button is connected with an internal pull-up resistor.  
2. A falling-edge interrupt is attached to the button pin.  
3. When the button is pressed, the interrupt triggers the `handleButton()` function.  
4. Inside the ISR, both LEDs are toggled together using a shared `ledState` flag.  
5. The main loop remains empty, allowing for non-blocking operation.

## Learning Outcomes
- Using GPIO interrupts on the ESP32  
- Handling multiple outputs from a single input  
- Writing efficient, non-blocking embedded programs  
- Understanding the role of ISRs in digital I/O control

## Code Author
**Abdullah**  
**Roll No:** 23-NTU-CS-1005
