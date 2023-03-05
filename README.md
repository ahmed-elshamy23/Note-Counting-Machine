# Note-Counting-Machine

#### Required Hardware:
- Arduino UNO
- Raspberry Pi 3
- Pi Camera
- Push Button
- 20x4 LCD
- Keypad

#### Required Modules:
- argparse
- pathlib
- openCV
- torch
- numpy

#### Overview:
- The user is asked to enter a password followed by '=' through the keypad
- Arduino UNO verifies the password <i>(123456 by default)<i/> and sends UART frame to raspberry pi to start operation
- The user puts the money in front of the camera and pushes the push button to start operation
- The raspberry pi captures an image through a camera, runs an AI image classification model and calculates the amount of money
- A UART frame is sent back to arduino UNO to display the amount of money on the LCD

---
**NOTE**

<i>Make sure to install the required python modules on your raspberry pi and check the project description document for further information.<i/>

---
