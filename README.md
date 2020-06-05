# Jarvis Smart Home Assistant

## Introduction
Jarvis, a smart home assistant, is a smart system that make your home more
convenient to live by connecting sensors, camera, smart appliances, light bulbs,
and a GUI application for monitoring and managements. Jarvis is operating mainly
at two areas which are front door area and personal room. The system provides
users capabilities to monitor front door area when they are away from home,
interacts with either visitors or delivery guys, monitor personal room conditions
and control remotely connected appliances.

## Download/Install
Download project as .zip file from GitHub or uing Git command 'Git clone https://github.com/NightKing9/jarvis.git' 

### Packages/Libraries Prerequisite
Project is created with:
* PyQt5 version 5.14.2
* PyParticleIO version 0.1.0
* RPLCD version 1.3.0
* picamera version 1.13
* opencv version 4.0.1
* RPi
* threading
* Adafruit.h libabry (Particle Web IDE)

## Project components
### Raspberry Pi files
* UI layout files (applayout.ui, start_camera_button.ui)
* Application program files (jarvis_window.py, camera_controller.py)

### Particle Argon files
* Argon folder: roomcontroller.ino

## Setup
To run this project by following steps:
1. Connect hardware components to main boards (Raspberry Pi, Particle Argon) following the project artefact instructions.
2. On Particle Web IDE, import/load/copy the source code (roomcontroller.ino).
3. Create associated integrations: Webhook (ThinkSpeak channel), Applet (IFTTT trigger).
4. Flash and run the code on Argon device.
5. On Raspberry Pi, install Python packages using 'pip install <package name>' command on local virtual environment (Python IDE).
6. Locate Python files (jarvis_window.py, camera_controller.py) and UI files (applayout.ui, start_camera_button.ui) in the same folder.
7. Run the program (jarvis_window.py) to start the jarvis application; run seperately program 'camera_controller.py' to manage pi camera.
8. Test the system using scenario in the project artefact.
  
## Documentation
* Project Artefacts: Documentation folder.
* Project Demo Video: https://youtu.be/w6MGwcngjZQ
