# STM32-PID-Motor-Control-System
Real-time PID-based motor speed control using STM32F4 with PWM, ADC input and FreeRTOS task management.
# STM32 Real-Time PID Motor Speed Control System

This project implements a real-time motor speed control system using an STM32F4 microcontroller. The system uses a PID controller to regulate motor speed based on a user-defined reference input.

## 📌 Project Overview

A potentiometer is used to set the desired motor speed through ADC. The motor is driven using PWM, and its speed is controlled using a PID algorithm. FreeRTOS is used to manage system tasks, allowing real-time performance and efficient execution.

---

## ⚙️ Features

- ADC-based speed reference input
- PWM motor control
- PID control algorithm
- Real-time UART monitoring
- FreeRTOS task scheduling

---

## 🧰 Hardware Used

- STM32F4 Development Board
- DC Motor
- Motor Driver (L298N or similar)
- Potentiometer (PA0)
- PWM Output (TIM2 - PA5)
- USB Cable

---

## 🔌 System Description

- ADC reads potentiometer value (setpoint)
- PID controller calculates control signal
- PWM adjusts motor speed
- UART transmits real-time data
- FreeRTOS manages system tasks

---

## 🧠 FreeRTOS Tasks

- Task 1: Sensor reading (ADC)
- Task 2: PID computation
- Task 3: UART communication

---

## 💻 Software Used

- STM32CubeIDE
- HAL (Hardware Abstraction Layer)
- FreeRTOS

---

## 📁 Project Structure

---

## 🔁 System Operation

1. ADC reads potentiometer input  
2. Sensor task updates setpoint  
3. PID task computes control signal  
4. PWM output drives motor  
5. UART task reports system data  

---

## 📊 Example UART Output

SP: 1500 Speed: 1400 PWM: 320  
SP: 2000 Speed: 1950 PWM: 450  
SP: 2500 Speed: 2600 PWM: 600  

---

## 📌 Conclusion

This project demonstrates real-time motor control using PID and FreeRTOS. It highlights how multiple peripherals and tasks can be integrated to build an efficient embedded control system.
