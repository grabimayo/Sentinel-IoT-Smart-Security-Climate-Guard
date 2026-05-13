# 🛡️ Sentinel-IoT: Smart Security & Climate Guard

## 📝 Project Description
The **Sentinel-IoT** is a multi-functional IoT node built on the **ESP32** platform. It combines environmental monitoring with an autonomous security system. The project features a custom web dashboard for live telemetry and manual actuator control, alongside localized automation logic that enables the system to react instantly to physical movement.

---

## 🚀 "Two-Way" System Features
To fulfill the Assignment 1 rubric, this project implements:
1. **Live Telemetry (Upstream):** Constant streaming of Temperature, Humidity, and Motion status to a web browser.
2. **Web-to-Physical Control (Downstream):** A manual toggle button on the web UI to trigger the **Buzzer** remotely.
3. **Local Automation (Autonomous):** A hardware-level logic loop where the **PIR Sensor** automatically triggers the **LED** and **Buzzer** upon detecting motion, independent of the network.

---

## 🛠️ Hardware Specification
| Component | Function | GPIO Pin |
| :--- | :--- | :--- |
| **ESP32 DevKit V1** | Microcontroller & Web Server | - |
| **DHT11** | Temperature & Humidity Sensor | **GPIO 26** |
| **PIR Sensor** | Human Motion Detection | **GPIO 34** |
| **Active Buzzer** | Audible Alarm (Manual & Auto) | **GPIO 27** |
| **LED** | Visual Warning Light (Autonomous) | **GPIO 25** |

---

## 🔌 Wiring Details
* **DHT11:** VCC to 3.3V, GND to GND, Data to **D26**.
* **PIR Sensor:** VCC to Vin (5V), GND to GND, Data to **D34**.
* **Buzzer:** Red (+) to **D27**, Black (-) to GND.
* **LED:** Long leg (+) to **D25** (via 220Ω resistor), Short leg (-) to GND.

---

## 💻 Software Setup
1. **SSID/Password:** Open the `.ino` file and update your Wi-Fi credentials.
2. **Libraries:** Ensure `DHT Sensor Library` by Adafruit is installed.
3. **Serial Monitor:** Set baud rate to `115200`.
4. **Access:** Copy the IP address from the Serial Monitor into any browser on the same network.

---

## 📁 Repository Contents
* `Smart_Security_System.ino` - Main source code.
* `Circuit_Diagram.png` - Visual wiring map.
* `README.md` - Documentation.

---

## 👤 Author
* **Name:** JESLYN SAMINATHAN
* **Student ID:** A202747
* **Course:** TR3163 Internet of Things
