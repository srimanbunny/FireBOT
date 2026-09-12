# 🔥 FireBOT

**IoT-Based Autonomous Fire-Extinguishing Robot**

FireBOT is a diploma project that combines embedded systems, robotics, sensors, motor control and IoT communication into a mobile fire-detection and extinguishing prototype.

The robot uses an **ATmega328P** as its main controller and an **ESP8266-01 (ESP-01)** for Wi-Fi communication with a **Blynk** mobile application. Three flame sensors are positioned at the left, center and right of the robot to help determine the direction of a detected flame. An MQ-2 sensor provides smoke readings. The robot can operate in automatic and manual modes, and uses a relay-controlled water pump with an SG90 servo for nozzle movement.

> **Project status:** Working diploma-project prototype.
>
> **Safety:** FireBOT is an educational prototype, not certified firefighting or life-safety equipment. Do not rely on it for real emergency response.

## Features

- 🔥 Three-direction flame sensing
- 💨 MQ-2 smoke sensing
- 🤖 Automatic fire tracking
- 🚗 DC motor movement through L298N
- 💧 Relay-controlled water pump
- 🎯 Servo-controlled nozzle sweep
- 📱 Wi-Fi remote control through Blynk
- 🔔 Buzzer status indication
- 🔌 ATmega328P + ESP8266 serial communication
- 🧩 Custom PCB design and fabrication

## System Overview

![FireBOT block diagram](hardware\block_digram.png)

The ATmega328P acts as the central controller. Sensor inputs are processed by the microcontroller, which controls the motors, pump, servo and buzzer. The ESP-01 provides the wireless link to the Blynk application.

## How It Works

### Automatic mode

1. FireBOT initializes its sensors, motors, pump, servo and communication interface.
2. The three flame sensors continuously provide readings from the left, center and right directions.
3. The ATmega328P compares the readings to determine the direction of the fire.
4. The robot turns or moves forward toward the detected source.
5. When the center flame reading reaches the stop condition, the robot stops.
6. The water pump is activated through the relay.
7. The servo sweeps the nozzle to spread the water spray.
8. Smoke readings and status messages are sent through the ESP-01 to Blynk.

### Manual mode

The Blynk application can be used to send movement, pump and nozzle-related commands to the robot through the ESP-01 and serial link.

## Hardware

- ATmega328P DIP microcontroller
- ESP8266-01 Wi-Fi module
- 3 × flame sensor modules
- MQ-2 smoke sensor
- L298N motor driver
- DC motors and 4-wheel chassis
- SG90 servo motor
- Mini DC water pump
- 5V relay module
- 11.1V 2500mAh battery pack
- Buzzer
- Custom PCB

See the complete bill of materials in [`hardware/BOM.md`](hardware\bill_of_materials.png).

## Circuit Diagram

![FireBOT circuit diagram](hardware\circuit_schematic.png)

## The Prototype

![Working FireBOT prototype](hardware\firebot_prototype.png)

The photograph above is taken from the original diploma project report and shows the assembled four-wheel FireBOT with its flame sensors, electronics and ESP-01 module.

## PCB Fabrication

The original project included PCB layout and physical PCB fabrication as part of the hardware work.

![PCB fabrication top layer](hardware\pcb_top.png)
![PCB fabrication bottem layer](hardware\pcb_bottom.png)

## Software

The source code is split into two sketches:

- [`src/FireBOT_ATmega.ino`](src\FireBOT_ATmega\FireBOT_ATmega.ino) — robot control and automatic fire logic
- [`src/FireBOT_ESP01.ino`](src\FireBOT_ESP01\FireBOT_ESP01.ino) — Blynk/Wi-Fi bridge and mobile controls

The original project used the Arduino IDE and Blynk IoT.

### Credentials

The original report contains real Wi-Fi and Blynk credentials. They have **not** been included in this public repository. Replace the placeholders in `FireBOT_ESP01.ino` with your own credentials when running the project locally.

**Never commit real Wi-Fi passwords, Blynk auth tokens, API keys or other secrets to GitHub.**

## Limitations

The original project identified several limitations:

- Flame and smoke sensors have limited detection range and can be affected by ambient conditions and sensor placement.
- The prototype is intended for flat and smooth surfaces.
- Manual control and real-time monitoring depend on Wi-Fi connectivity.

## Future Improvements

The original report proposed several possible improvements:

- Thermal cameras or infrared imaging for more advanced fire detection
- Image processing and AI for fire/obstacle analysis
- Obstacle avoidance using ultrasonic or LiDAR sensors
- Improved communication such as LTE or mesh networking
- Higher-capacity batteries or smart battery management
- Alternative extinguishing agents where appropriate

## Project Documentation

The complete academic report is kept separately from this public repository because it contains personal/team information and embedded credentials. The technical diagrams and project photograph included here are extracted from that report.

## Credits

Diploma in Automation & Robotics Engineering project — **FireBOT**.

Built as an academic robotics and IoT prototype.
