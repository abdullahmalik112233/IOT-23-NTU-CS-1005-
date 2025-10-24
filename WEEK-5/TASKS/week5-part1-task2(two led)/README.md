# Week 4 Part 2 - OLED Display Text

**Name:** Abdullah  
**Roll No:** 23-NTU-CS-1005  

## Description
This project demonstrates how to use an OLED display (SSD1306) with an ESP32 via the I2C protocol.  
It shows how to initialize the display, draw graphics, and print text messages using the Adafruit GFX and SSD1306 libraries.

## Components
- ESP32 Development Board  
- 0.96" or 1.3" OLED Display (SSD1306, 128x64)  
- I2C Connection (SDA = GPIO 21, SCL = GPIO 22)

## Working
1. The OLED display is initialized using the I2C address `0x3C`.  
2. Two diagonal lines are drawn to form an “X” on the screen.  
3. The display then clears and prints two text messages:
   - `"Hello"` in small font at the top.
   - `"CS-A"` in larger font in the center.  
4. The display alternates between graphics and text every 2 seconds.

## Learning Outcomes
- Interfacing an SSD1306 OLED display with ESP32  
- Using Adafruit GFX and SSD1306 libraries  
- Drawing shapes and rendering text on an OLED  
- Managing display buffers and refresh cycles

## Code Author
**Abdullah**  
**Roll No:** 23-NTU-CS-1005
