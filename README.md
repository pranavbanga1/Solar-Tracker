# ☀️ Solar Tracker – Dual Axis Pan Tilt 

This project demonstrates the practical integration of embedded systems and actuators through a working solar tracking system using two servo motors. The tracker adjusts the position of a panel (or sensor array) to follow the sun’s movement using LDR sensors and can optionally be controlled with a joystick for manual override or calibration.

![CWLfzHpvcM9HrFPhp0YtlP0MIWL4egBl6kBqgi_UTQc=_plaintext_638161835270636080](https://github.com/user-attachments/assets/bbd315ef-e1b6-48e0-bda2-8c2f32479f6f)


---

## 🚀 Lessons Learnt

- Real-world application of servo control in embedded systems  
- Analog signal processing using LDRs  
- Use of comparative logic to control pan and tilt mechanisms  
- Optional integration of a joystick module  
- Simple testing and calibration methodology for actuators

---
## 📂 Repository Structure

```
Solar-Tracker/
├── Code_SolarTracker.ino      # Main tracking logic
├── servo_test.ino             # Servo motor testing
├── README.md
```

---

## 🧩 Required Components

- Arduino Uno or similar  
- 2x Servo Motors (SG90 or MG90S)  
- 4x LDR Sensors  
- 4x 10kΩ resistors (pull-down)  
- 2-axis Joystick (optional)  
- Breadboard + jumper wires  
- Solar panel or mount

---

## ⚙️ How It Works

The system uses four Light Dependent Resistors (LDRs) arranged in a cross pattern. Depending on which LDR receives the most sunlight, the corresponding servo (X or Y axis) is adjusted to better align the panel.

- **Servo X** controls horizontal rotation (pan)  
- **Servo Y** controls vertical tilt  
- The analog values from the LDRs are compared using threshold logic  
- The servos are moved slightly in the direction where light is stronger  

### 🧠 Logic Summary

```cpp
// Calculate average light from top vs bottom, left vs right
int avgTop = (ldrTL + ldrTR) / 2;
int avgBottom = (ldrBL + ldrBR) / 2;
int avgLeft = (ldrTL + ldrBL) / 2;
int avgRight = (ldrTR + ldrBR) / 2;

// Move servos based on difference thresholds
if (abs(avgTop - avgBottom) > threshold) {
  servoY.write(currentY + (avgTop < avgBottom ? 1 : -1));
}

if (abs(avgLeft - avgRight) > threshold) {
  servoX.write(currentX + (avgLeft < avgRight ? 1 : -1));
}
```

---

## 🎮 Joystick Control (Optional)

Want to manually adjust your pan/tilt system?  
✅ Uncomment the `joystickMode()` function in `loop()` and comment out `ldrTracking()` to switch modes.

```cpp
// loop() {
//   ldrTracking();    // Automatic tracking
//   joystickMode();   // Uncomment for manual control
// }
```

Use a 2-axis joystick connected to A0 (X) and A1 (Y). The servo angles will adjust based on analog input ranges.

---

## 🛠️ Servo Test

Before running the main tracking code, use `servo_test.ino` to verify motor wiring and range.

```cpp
// Simple sweep to verify pan and tilt movement
servoX.write(0);
delay(1000);
servoX.write(180);
delay(1000);
```

Upload this file and ensure smooth, full-range movement of both motors.

---
<p align="center">
  <img src="https://github.com/user-attachments/assets/0e7957c7-a84c-42c1-a9d6-c04df3fd35dc" width="30%" />
  <img src="https://github.com/user-attachments/assets/30857ec4-3d2a-4fdc-b793-fd024d0040ab" width="30%" />
  <img src="https://github.com/user-attachments/assets/d2642bda-dec8-46d6-b99e-6f001ef62913" width="30%" />
</p>


## 🧠 Future Improvements

- Add OLED or LCD display to show angle data  
- Log solar tracking data with RTC and SD card  
- Use PID control for smoother servo actuation  
- Add remote control via Bluetooth or WiFi

---

## 👨‍💻 Author

Pranav Banga – [@pranavbanga1](https://github.com/pranavbanga1)

---

## 📜 License

MIT License – Free to use and modify with attribution
