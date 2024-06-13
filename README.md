# Traffic Light Control System

## Overview

This project implements a traffic light control system using a finite state machine approach. Designed to manage an intersection, the system controls four traffic lights displayed on an LCD. The system is developed for platforms that support the ESP32 microcontroller, using a custom Hardware Access Layer (HAL) for the ST7789V LCD controller and utilizes the ESP-IDF for efficient data handling and fast transfers.

## Features

- **Traffic Light Control**: Manages two sets of traffic lights (top/bottom and left/right) with standard traffic light sequences (Green -> Orange -> Red).
- **Pedestrian Button Interaction**: Includes functionality for pedestrian buttons that influence the traffic light logic, ensuring that lights respond dynamically to pedestrian requests.
- **Efficient Data Transfer**: Utilizes the ESP-IDF's SPI master driver to perform high-speed data transfers to the LCD, allowing for quick updates to the display.
- **System Monitoring**: Monitors the system's stack usage and logs warnings if the available stack space is low.

## Hardware Requirements

- ESP32 microcontroller
- ST7789V LCD display
- Standard push buttons (for pedestrian interaction)
- Appropriate wiring and resistors for connections

## Software Dependencies

- ESP-IDF for utilizing ESP32 features and SPI communication
