# water-monitoring
ESP8266 based Water Quality Monitoring System using ThingSpeak
# 💧 Water Quality Monitoring System

An IoT-based **Water Quality Monitoring System** built using **ESP8266** and **ThingSpeak**.  
The system collects water-quality sensor data and uploads the readings to the ThingSpeak cloud platform for real-time monitoring.

---

## 📌 Project Overview

The Water Quality Monitoring System is designed to monitor important water parameters using sensors connected to an ESP8266 microcontroller.

The ESP8266 connects to Wi-Fi and sends the collected sensor readings to **ThingSpeak**, where the data can be viewed and analyzed remotely.

---

## ✨ Features

- Real-time water quality monitoring
- ESP8266 Wi-Fi connectivity
- Sensor data acquisition
- ThingSpeak cloud integration
- Live data visualization
- Serial Monitor output
- Low-cost IoT monitoring solution
- Easy to expand with additional sensors

---

## 🛠️ Hardware Requirements

- ESP8266 / NodeMCU
- Water Quality Sensors
- Jumper Wires
- Breadboard
- USB Cable
- Power Supply
- Computer with Arduino IDE

Additional sensors can be connected depending on the water parameters that need to be monitored.

---

## 💻 Software Requirements

- Arduino IDE
- ESP8266 Board Package
- ThingSpeak Library
- ESP8266WiFi Library
- ThingSpeak Account

---

## 📚 Required Arduino Libraries

The project uses the following libraries:

```cpp
#include <ESP8266WiFi.h>
#include <ThingSpeak.h>
