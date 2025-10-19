# Bachelor’s Thesis – Portable Health Monitoring and Navigation Device Based on Arduino and Flutter

This project is a smartwatch designed to remain constantly connected to the internet. If the device loses internet connectivity, it will attempt to reconnect, and if no network is available, it will activate Bluetooth, allowing the Android app developed in Flutter to send new credentials so the ESP32-S3 microcontroller can connect to the internet.

The watch is equipped with a 9-axis IMU sensor (MPU9250), a MAX30102 sensor for measuring heart rate and blood oxygen levels, and an RTC module to keep track of time even when the watch has no power. Using the MPU, specifically accelerometer data, the device can calculate the number of steps taken in a day. It also computes the distance traveled and calories burned. Navigation functionality is provided through a built-in compass.

Heart rate, blood oxygen levels, steps, distance, and calories burned are stored in a Firebase real-time database.

# Connection Diagram for the Watch

![pinning_proiect_2](https://github.com/user-attachments/assets/77ffd26c-529c-4fa0-a6c6-646aebf71d60)

# UI for the Watch

![image](https://github.com/user-attachments/assets/918e2c23-8301-4bb9-ae0a-a2471fd15064)


# UI Mobile App

![image](https://github.com/user-attachments/assets/633c5f1d-4780-4616-b320-bd0f9e005896)
