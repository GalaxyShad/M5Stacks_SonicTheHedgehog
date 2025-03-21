# M5Stack-ESP32-ILI9341-Sonic-The-Hedgehog-Port
![image](https://github.com/user-attachments/assets/d0e0c718-04f0-4c17-8eb0-e5c9bedab156)<br/>
A highly accurate port of the first level of *Sonic the Hedgehog* from the Sega Mega Drive to the M5Stack (ESP32 and ILI9341 device)<br/>
<img width="449" alt="image" src="https://github.com/user-attachments/assets/f1b4dbee-5947-4ae2-93e9-42e190ff0b3a" align="center" /><br/>


---

## Why Archived?
This project is no longer under active development. It will remain in its original state, but the codebase has been used as the foundation for the [Open-Sonic-1-Recreation](https://github.com/GalaxyShad/Open-Sonic-1-Recreation) project.

---

## Gameplay
Watch the gameplay here:  
[![Sonic Gameplay](https://img.youtube.com/vi/hCu9-snmJkE/0.jpg)](https://www.youtube.com/watch?v=hCu9-snmJkE)

---

## Controls
- **Left/Right Button**: Move Sonic left or right.
- **Middle Button**: Jump.
- **Left + Right Button (while moving)**: Roll.
- **Left + Right Button (while standing)**: Perform a spindash (Sonic CD style).

---

## Rendering System
The rendering system is based on a palette and index buffer. Here's a simplified example of how it works:  
![image](https://github.com/user-attachments/assets/8c3fd5eb-c604-46b8-b0dd-2188ffddb996)

---

## Settings
### Input
You can configure key mappings and other settings in the `GameSettings.h` file.

### Screen Resolution
The game supports resizable screens. Configure the resolution in `GameSettings.h`:
- **Optimal Resolution**: 160x120 (30 FPS).
- **Max Resolution**: 320x200 (9 FPS).
- **High FPS (50+ FPS)**: 80x80 (harder to play due to small screen size).

---

## Features Implemented
- 360-degree movement.
- Objects and enemies.
- Animated background.
- Visual effects.
- Character animations.

---

## Missing Features
- Monitors (power-ups).
- Some enemies.
- Background scrolling.
- Music and sound effects.
- Spikes.

---

## Development Article on Hackster.IO
Read more about the development process on Hackster.IO:  
[**M5Stack Sonic the Hedgehog Port**](https://www.hackster.io/galaxyshad/m5stack-sonic-the-hedgehog-port-32fd83)

---

## Disclaimer
This project is a fan-made creation intended for educational purposes. All characters, graphics, and assets are owned by Sega.

---

![image](https://github.com/user-attachments/assets/8175cb53-f4c1-42bf-8062-dd635870caf4)  
*Image by [M5Stack](https://cyrillic.m5stack.com/)*
