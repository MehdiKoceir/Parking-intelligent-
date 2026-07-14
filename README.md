# 🚗 Smart Parking System with Directional Guidance

<div align="center">

![ESP32](https://img.shields.io/badge/ESP32-Microcontroller-red?style=for-the-badge&logo=espressif)
![Arduino](https://img.shields.io/badge/Arduino-C++-00979D?style=for-the-badge&logo=arduino)
![IoT](https://img.shields.io/badge/IoT-Smart%20Parking-blue?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

### 🚦 Intelligent Smart Parking System using ESP32

Automatic vehicle counting, intelligent parking guidance, and automated barrier control.

</div>


# 📖 Overview

Finding a parking space can be frustrating, especially when drivers do not know whether spaces are available or which direction to take after entering a parking lot. Traditional parking systems rely on manual supervision, causing traffic congestion, inaccurate vehicle counting, and unnecessary delays.

This project presents a **Smart Parking System** powered by an **ESP32 microcontroller** capable of automatically counting vehicles, controlling the entrance barrier, monitoring parking occupancy, and guiding drivers toward available parking zones using ultrasonic sensors.

The system provides real-time information through an LCD display while reducing human intervention and improving parking efficiency.

---

# ✨ Features

- 🚗 Automatic vehicle detection
- 🚦 Automatic entrance barrier
- 📊 Real-time vehicle counting
- 🅿️ Parking capacity management
- 🧭 Directional guidance (Zone A / Zone B)
- 📟 LCD information display
- 🟢 Parking Available indicator
- 🔴 Parking Full indicator
- 🚘 Zone occupancy monitoring
- ⚡ Real-time embedded processing
- 🔄 Debounce protection against false detections
- 🎯 Smooth servo motor movement

---

# 🛠 Hardware Components

| Component | Quantity |
|------------|---------:|
| ESP32 Development Board | 1 |
| HC-SR04 Ultrasonic Sensor | 4 |
| SG90 Servo Motor | 1 |
| LCD 16x2 I2C Display | 1 |
| Green LED | 1 |
| Red LED | 1 |
| Zone A LED | 1 |
| Zone B LED | 1 |
| Breadboard | 1 |
| Jumper Wires | Several |
| USB Cable | 1 |

---

# ⚙ System Architecture

```text
                   Vehicle Entry
                        │
                        ▼
              Entry Ultrasonic Sensor
                        │
                        ▼
                  ESP32 Controller
      ┌────────────┬────────────┬────────────┐
      ▼            ▼            ▼
 Servo Motor    LCD Display     LEDs
      │            │            │
      ▼            ▼            ▼
Automatic     Parking Info    Status
Barrier

                 │
       ┌─────────┴─────────┐
       ▼                   ▼

 Zone A Sensor        Zone B Sensor
```

---

# 🚘 System Workflow

```text
Vehicle Arrives
      │
      ▼
Entry Sensor Detects Vehicle
      │
      ▼
Is Parking Full?

      │
 ┌────┴────┐
 │         │
Yes        No
 │          │
 ▼          ▼

Keep      Increment
Barrier   Counter
Closed
           │
           ▼
Calculate Free Spaces

Check Zone A

Check Zone B

Display Direction

Open Barrier

Vehicle Enters

Close Barrier
```

---

# 📟 LCD Output

### Parking Available

```text
SMART PARKING

Free: 4 GO LEFT
```

### Alternative Route

```text
SMART PARKING

Free: 2 GO RIGHT
```

### Parking Full

```text
SMART PARKING

Free:0 PARK FULL
```

---

# 🚦 LED Status

| LED | Description |
|------|-------------|
| 🟢 Green | Parking Available |
| 🔴 Red | Parking Full |
| 🟡 Zone A | Zone A Occupied |
| 🟡 Zone B | Zone B Occupied |

---

# 🔌 Pin Configuration

| Device | GPIO |
|---------|------|
| Servo Motor | GPIO 13 |
| Green LED | GPIO 26 |
| Red LED | GPIO 27 |
| Zone A LED | GPIO 25 |
| Zone B LED | GPIO 33 |
| Shared Trigger | GPIO 3 |
| Entry Echo | GPIO 15 |
| Zone A Echo | GPIO 2 |
| Zone B Echo | GPIO 4 |
| Exit Echo | GPIO 5 |
| LCD SDA | GPIO 21 |
| LCD SCL | GPIO 22 |

---

# 📂 Project Structure

```text
Smart-Parking-System/
│
├── code/
│   └── smart_parking.ino
│
├── report/
│   └── Smart_Parking_Report.pdf
│
├── images/
│   ├── wiring.png
│   ├── simulation.png
│   ├── lcd.png
│   └── architecture.png
│
├── mockups/
│   ├── cover.png
│   ├── system.png
│   ├── barrier.png
│   ├── lcd.png
│   └── wiring.png
│
└── README.md
```

---

# 🚀 Installation

### Clone the Repository

```bash
git clone https://github.com/yourusername/Smart-Parking-System.git
```

### Install Arduino Libraries

- ESP32 Board Package
- LiquidCrystal_I2C
- ESP32Servo

### Select Board

```
ESP32 Dev Module
```

### Upload

Compile and upload the project using Arduino IDE.

Open the Serial Monitor at **115200 baud**.

---

# 🧪 Simulation

The project can be simulated using **Wokwi** before deploying it to physical hardware.

Simulation validates:

- Vehicle detection
- Entry and exit counting
- Servo barrier operation
- LCD updates
- LED indicators
- Parking availability
- Direction guidance

---

# 📈 Future Improvements

- 📱 Mobile Application
- 🌐 Web Dashboard
- ☁ Cloud Database Integration
- 📡 MQTT Communication
- 🤖 AI Parking Prediction
- 📷 License Plate Recognition
- 💳 Smart Payment System
- 📍 Individual Parking Space Sensors
- 🔔 Notifications
- 📊 Analytics Dashboard

---

# 📊 Project Summary

| Feature | Status |
|----------|--------|
| Vehicle Counting | ✅ |
| Automatic Barrier | ✅ |
| LCD Display | ✅ |
| Parking Guidance | ✅ |
| Zone Detection | ✅ |
| LED Indicators | ✅ |
| ESP32 Integration | ✅ |
| HC-SR04 Sensors | ✅ |
| Servo Motor | ✅ |

---

# 👨‍💻 Author

**Mehdi Koceir**

Master's Student in Computer Systems & Networks (SIR)

University of Blida

GitHub: **https://github.com/MehdiKoceir**

---

# ⭐ Support

If you enjoyed this project:

⭐ Star this repository

🍴 Fork it

📢 Share it with others

---

<div align="center">

### 🚗 Smart Parking System

**An ESP32-based Embedded System for Intelligent Parking Management**

Made with ❤️ using **ESP32, Arduino, C++, and IoT Technologies**

</div>
