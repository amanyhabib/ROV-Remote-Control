<h1 align="center" id="title">ROV-Remote-Control</h1>

This repository is developed by the **ROV Team** to control an underwater Remotely Operated Vehicle (ROV). 
The system is designed to carry out underwater tasks using an **Arduino Mega** and a **Raspberry Pi**,
with controls managed through a joystick and potentiometer interface.
The **Arduino Mega** drives four **DC motors** for directional movement and
two **brushless T100 thrusters** for vertical control.

## Contributors

<!-- ALL-CONTRIBUTORS-LIST:START - Do not remove or modify this section -->
<!-- prettier-ignore-start -->
<!-- markdownlint-disable -->
<table>
  <tbody>
    <tr> https://avatars.githubusercontent.com/u/159341041?s=96&v=4
      <td align="center" valign="top" width="14.28%"><a href="https://github.com/amanyhabib"><img src="https://avatars.githubusercontent.com/u/159341041?s=96&v=4" width="100px;" alt="Amany Habib"/><br /><sub><b>Amany Habib</b></sub></a><br /><a href="#infra-Amany-Habib" title="Code">💻</a></td>
      <td align="center" valign="top" width="14.28%"><a href="https://github.com/shahdnasr1"><img src="https://avatars.githubusercontent.com/u/111206091?v=4?s=100" width="100px;" alt="Shahd Nasr"/><br /><sub><b>Shahd Nasr</b></sub></a><br /><a href="#tests-Shahd-Nasr" title="Tests">⚠</a> <a href="#code-Shahd-Nasr" title="Code">💻</a></td>
      <td align="center" valign="top" width="14.28%"><a href="https://github.com/Ayamohamed2003"><img src="https://avatars.githubusercontent.com/u/160287704?v=4?s=100" width="100px;" alt="Aya Mohamed"/><br /><sub><b>Aya Mohamed</b></sub></a><br /><a href="#code-Aya-Mohamed" title="Code">💻</a></td>
      <td align="center" valign="top" width="14.28%"><a href="https://github.com/AmiraSayedMohamed"><img src="https://avatars.githubusercontent.com/u/99215076?v=4?s=100" width="100px;" alt="Amira Sayed Mohamed"/><br /><sub><b>Amira Sayed Mohamed</b></sub></a><br /><a href="#code-Amira-Sayed-Mohamed" title="Code">💻</a></td>
    </tr>
  </tbody>
</table>

<!-- markdownlint-restore -->
<!-- prettier-ignore-end -->

<!-- ALL-CONTRIBUTORS-LIST:END -->


## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Hardware Requirements](#hardware-requirements)
- [Software Requirements](#software-requirements)
- [Hardware Setup and Connections](#hardware-setup-and-connections)
- [Installation and Setup](#installation-and-setup)
- [Usage](#usage)
- [Example Commands on Raspberry Pi](#example-commands-on-raspberry-pi)
- [File Descriptions](#file-descriptions)
- [License](#license)

## Overview
This code is part of a dual-board control system. The **Arduino Mega** manages the motor control,
executing commands for movement, while the **Raspberry Pi** interprets inputs from a controller
(joystick and potentiometer) and sends serial commands to the Arduino Mega for execution. 

The system includes:
- **DC Motors** for horizontal movement
- **T100 Thrusters** with **ESCs** for vertical movement
- **Cytron Motor Driver** for DC motor control
- **Joystick and Potentiometer** for navigation and speed control

<h2>🧐 Features</h2>
- **Directional Control**: Supports forward, backward, left, and right movements.
- **Vertical Movement**: T100 thrusters allow controlled ascent and descent.
- **Speed Adjustment**: Potentiometer adjusts motor speeds dynamically.
- **Serial Communication**: Uses Raspberry Pi to communicate user inputs to the Arduino Mega.
- **Hardware Safety**: Stop command ensures safe handling in emergency situations.

<h2>🛠️ Hardware Requirements</h2>
- **Arduino Mega 2560**
- **Raspberry Pi** (any version with GPIO and serial communication)
- **4 DC Motors** for movement in four directions (forward, backward, left, right)
- **2 T100 Thrusters** with **ESCs** for vertical movement
- **Cytron Motor Driver** for controlling DC motors
- **Joystick and Potentiometer** for navigation and speed control
- **Power Supply** for motors and thrusters
- **Wiring and Connectors** for hardware setup

<h2>💻 Software Requirements</h2>
- **Arduino IDE**: For uploading code to Arduino Mega
- **Python 3** (on Raspberry Pi): For serial communication control script
- **Python Serial Library**: For enabling serial communication between Raspberry Pi and Arduino
  - Install using: `pip install pyserial`

<h2>🔌 Hardware Setup and Connections</h2>
1. **DC Motors**:
   - Connect the DC motors to the **Cytron Motor Driver**.
   - Motor Driver input pins should connect to the digital pins on **Arduino Mega** as defined in `motorcontrol.cpp`.
2. **T100 Thrusters**:
   - Connect the ESC signal wires of the T100 thrusters to **Arduino pins 10 and 11**.
3. **Joystick and Potentiometer**:
   - Connect the joystick and potentiometer to the **Raspberry Pi GPIO pins**.
   - Potentiometer is connected to **analog pin A0** on the **Arduino Mega** for speed control.
4. **Serial Communication**:
   - Connect **Raspberry Pi's Tx and Rx** pins to **Arduino Mega's Rx and Tx** pins (crossed over).
   - Ensure both devices share a common ground for reliable serial communication.

<h2>🚀 Installation and Setup</h2>
### Arduino Setup
1. Open `ROV-V5.ino` in the **Arduino IDE**.
2. Place `motorcontrol.cpp` and `motorcontrol.h` in the same project directory.
3. Compile and upload the code to the **Arduino Mega**.

### Raspberry Pi Setup
1. Install **Python Serial Library**:
   ```bash
   pip install pyserial
2. Save the provided Raspberry Pi control code to your Pi, and modify the serial port if necessary.

<h2>📜 Usage</h2>
### Control the ROV:

1. Run the Python script on the Raspberry Pi to control the ROV.
2. Enter serial commands in the terminal to move the ROV in different directions.

### Arduino Commands:

The Arduino Mega receives the commands from the Raspberry Pi and adjusts the motor control accordingly:

- **W**: Move Forward
- **S**: Move Backward
- **A**: Turn Left
- **D**: Turn Right
- **U**: Move Up (vertical)
- **Q**: Move Down (vertical)
- **X**: Stop (emergency stop or stop all movement)

<h2>📍 Example Commands on Raspberry Pi</h2>
To control the ROV from the Raspberry Pi, run the Python control script and use the following commands:

#### Available Commands:
- **W**: Move Forward
- **S**: Move Backward
- **A**: Turn Left
- **D**: Turn Right
- **U**: Move Up (vertical movement)
- **Q**: Move Down (vertical movement)
- **X**: Stop (emergency stop or stop all movement)

#### Example Control Session:
1. Start the Python script:
    ```bash
    python rov_control.py
    ```
2. Enter the commands as needed:

- To move forward: Press **W**
- To move backward: Press **S**
- To turn left: Press **A**
- To turn right: Press **D**
- To move up (vertical movement): Press **U**
- To move down (vertical movement): Press **Q**
- To stop the ROV: Press **X**

The Raspberry Pi will send the respective serial command to the Arduino Mega, which will control the motors and thrusters accordingly.

<h2>📂 File Descriptions Pi</h2>
- **ROV-V5.ino**: Main Arduino sketch to control motors and receive serial commands.
- **motorcontrol.cpp**: Contains the MotorControl class for managing motor directions and speed.
- **motorcontrol.h**: Header file defining motor control functions and pin configurations.
- **Raspberry Pi Control Script**: Python script (`control_rov.py`) for Raspberry Pi to send commands to the Arduino based on joystick input.

<h2>📜 License Pi</h2>
This project is licensed under the MIT License. See the LICENSE file for details.
