
# DIY Teensy/Arduino-Based Quadcopter Flight Controller

This repository contains the hardware and firmware design of a DIY quadcopter flight controller based on the Teensy 3.6 microcontroller.

## Background

This project was developed during my second year of college, during the COVID-19 pandemic. At the time, I had not yet taken a formal course in control theory. Therefore, the PID controller was not designed or simulated using MATLAB or similar tools.

Instead, I took a more hands-on approach:
- I built a small seesaw, mounted two motors at each end, and applied the **Ziegler-Nichols method** to find approximate PID values.
- It worked surprisingly well, and turned out to be a fun way to experiment with tuning.
- The quadcopter was flight-tested several times — and while it requires a bit of piloting skill, it flies well!

 A demo video can be found in the [YouTube Demo Video](https://youtube.com/shorts/SQsQxhgbjAk?feature=share) folder. 

---

## Features

- Sensor fusion from MPU6050 accelerometer and gyroscope data
- Simple PID-based stabilization algorithm tuned experimentally
- Teensy 3.6-based firmware written in Arduino IDE
- Manually tunde PID controller using a physical test rig and the Ziegler-Nichols method
- Basic safety indicators via buzzer and LEDs
- Lightweight custom 3D-printed enclosure for controller & power hub

---

## Mechanical Design

A compact case was designed and 3D-printed to hold both:
- The power hub (bottom section)
- The flight controller (top section)
- A snap-on lid

You can find the `.stl` file in the [`docs/`](docs) folder.

---

## Electronics & Wiring

Since I didn’t fabricate a PCB, I designed the schematic using **Fritzing**.  
It may not be the prettiest, but it gets the job done.

Required libraries are included in the [`libraries/`](libraries) folder.

---

## Components

### Flight Controller

- Teensy 3.6 (MK66FX1M0)
- MPU6050 (Accelerometer + Gyroscope)
- Mateksys MINI Power Hub w/ BEC (5V & 12V)
- 2x LEDs (with 3.3kΩ resistors)
- 1x Buzzer (with 100Ω resistor)
- 5x7 cm perfboard

### Quadcopter Frame

- Radiolink AT9s Pro + R12DSM Receiver
- DJI F450 Frame
- Sunnysky X2212 KV1250 3rd Gen x4
- Hobbywing XRotor 40A ESC x4
- Gemfan 9047 Propellers x4
- Profuse 11.1V 65C 1800 mAh LiPo battery

---