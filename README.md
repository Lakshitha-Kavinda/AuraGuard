# AuraGuard
### Smart Child Safety Wristband - The invisible link of Love

<img width="1024" height="1024" alt="ChatGPT Image Jul 30, 2025, 11_11_29 PM" src="https://github.com/user-attachments/assets/5d74a0cd-1f6b-485d-a1d0-5fbc269bdfe5" />


## Project Overview
**AuraGuard** _is a wearable safety wristband(system) designed to protect children in crowded or open spaces or indoors by maintaining a secure Bluetooth Low Energy (BLE) proximity link between a parent and child. When the child moves beyond a predefined distance (based on signal strength), the parent’s wristband immediately vibrates to alert them._

### Component specification

| Component                                        | Quantity | Notes                                           |
| ------------------------------------------------ | -------- | ----------------------------------------------- |
| ESP32 Dev Module / ESP32 with integrated display | 2        | One for parent, one for child                   |
| 3.7V Li-ion or Li-Po battery                     | 2        | For powering the ESP32                          |
| TP4056 Charging Module                           | 2        | USB charging circuit for battery                |
| Vibration Motor Module                           | 1        | On the parent band to alert                     |
| Buttons                                          | 4        | Powering  ON/OFF, UP, DOWN, OK                  |
| LED or OLED (optional)                           | Optional | If the ESP32 doesn't have a integrated display. |
| Enclosure/Band                                   | 2        | Wristband or case for both units                |

### Project timeline

| Week  | Task                                                                                                                                |
| ----- | ------------------------------------------------------------------------------------------------------------------------------------|
| 1–2   | Research BLE + RSSI behavior + Filtering techniques, finalize components, Requirement specification                                 |
| 3–4   | Ordering or buying components and Build BLE communication between devices                                                           |
| 5–6   | Implement range detection + vibration trigger  + Improve the noise immunity of the system (Trying different filtering techniques)   |
| 7–8   | Enclosure design + power circuit + PCB design (if possible)                                                                                                   |
| 9–10  | Testing and calibration in real-world scenarios                                                                                     |
| 11–12 | Documentatig and demo preparation                                                                                      |
