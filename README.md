# Bachelor’s Thesis – Portable Health Monitoring and Navigation Device Based on Arduino and Flutter

Built a functional prototype of a wearable health monitoring system similar to a smartwatch using C/C++ and the ESP32-S3 microcontroller. The device measures heart rate, blood oxygen level, steps, and includes a compass for navigation, integrating multiple sensors: a 9-axis IMU (MPU9250), a MAX30102 pulse oximeter, and an RTC module. The device also features a touchscreen display with a custom-created UI interface.

The system is managed with multiple concurrent tasks under FreeRTOS. For debugging concurrency issues and random crashes, the GCC toolchain was used. Custom C++ classes were implemented for interfacing with the I2C MPU9250 and MAX30102 sensors, following OOP principles and interpreting datasheets to configure the devices at the register level. A calibration algorithm for the IMU was developed and validated using Python to process serial data and create visualizations.

Sensor data is transmitted to Firebase via Wi-Fi, with BLE connectivity managed through a custom Android app built in Flutter, allowing configuration and network setup. Power usage is optimized by enabling Wi-Fi and BLE only when needed, balancing connectivity and battery life. 

Comprehensive documentation was created for system design, sensor integration, and firmware functionality.

# Connection Diagram for the Watch

![pinning_proiect_2](https://github.com/user-attachments/assets/77ffd26c-529c-4fa0-a6c6-646aebf71d60)

# UI for the Watch

![image](https://github.com/user-attachments/assets/918e2c23-8301-4bb9-ae0a-a2471fd15064)


# UI Mobile App

![image](https://github.com/user-attachments/assets/633c5f1d-4780-4616-b320-bd0f9e005896)
