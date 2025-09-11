# AuraGuard
### Smart Child Safety Wristband - The invisible link of Love

<img width="512" height="512" alt="ChatGPT Image Jul 30, 2025, 11_11_29 PM" src="https://github.com/user-attachments/assets/5d74a0cd-1f6b-485d-a1d0-5fbc269bdfe5" />


## Project Overview
**AuraGuard** _is a wearable safety wristband(system) designed to protect children in crowded or open spaces or indoors by maintaining a secure Bluetooth Low Energy (BLE) proximity link between a parent and child. When the child moves beyond a predefined distance (based on signal strength), the parent’s wristband immediately vibrates to alert them._

### Component specification

| Component                                        | Quantity | Notes                                           |
| ------------------------------------------------ | -------- | ----------------------------------------------- |
| ESP32 Dev Module  | 1        | For parenet device                 |
|  DW1000 NodeMCU-BU01 Development Board | 2 | For accurate distance measurement |
| 3.7V Li-ion or Li-Po battery                     | 2        | For powering the ESP32                          |
| TP4056 Charging Module                           | 2        | USB charging circuit for battery                |
| Vibration Motor Module                           | 1        | On the parent band to alert                     |
| Buttons                                          | 4        | Powering  ON/OFF, UP, DOWN, OK                  |
| OLED display                          | 1 | For parent device |
|  100 ohm resistors | 4 | |
|Swithces | 2 | |
| Enclosure/Band                                   | 2        | Wristband or case for both units                |

### Project timeline

| Week  | Task                                                                                                                                |
| ----- | ------------------------------------------------------------------------------------------------------------------------------------|
| 1–2   | Research BLE + RSSI behavior + Filtering techniques, finalize components, Requirement specification                                 |
| 3–4   | Ordering or buying components and Build BLE communication between devices and UWB development boards                                                           |
| 5–6   |Implement version 1 using BLE rssi.(Implement range detection + vibration trigger  + Improve the noise immunity of the system)   |
| 7–8   |Implement version 2 using UWB technology                                                                                                  |
| 9–10  | Testing and calibration in real-world scenarios and documentation of the finding.                                                          |
| 11–12 | Documentatig and demo preparation                                                                                      |

### Version 1 - BLE RSSI based Wristband implementation


<img width="512" height="512" alt="ChatGPT Image Jul 30, 2025, 11_11_29 PM" src="https://github.com/user-attachments/assets/ddc0eaf6-9653-45a6-9e58-a90505d7f58c" />


### Version 2 - UWB based Wristband implementation

#### Parent's wristband

![WhatsApp Image 2025-09-11 at 13 28 04_df5b8549](https://github.com/user-attachments/assets/4f7a53cc-87c4-4a84-907f-26ea92704072)

#### Child's wrist band

![WhatsApp Image 2025-09-11 at 13 40 55_cc82fbab](https://github.com/user-attachments/assets/21339f17-ae87-4d12-b4f4-8965e27080f9)


