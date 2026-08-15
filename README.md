# STM32 Nucleo-F103RB ADC-Based 3-Level LED Control

## 📌 Project Overview

This project demonstrates **Analog-to-Digital Conversion (ADC)** using the **STM32 Nucleo-F103RB** development board. A potentiometer is connected to the ADC input, and its analog voltage is converted into a 12-bit digital value.

Based on the ADC value, one of three LEDs is turned ON. The LEDs represent **Low, Medium, and High** input levels.

## 🎯 Objectives

* Understand the basic working principle of ADC.
* Configure **ADC1** using the STM32 HAL Library.
* Read an analog signal from a potentiometer.
* Convert the analog input into a 12-bit digital value.
* Control three LEDs according to ADC thresholds.
* Practice GPIO and ADC interfacing using STM32CubeIDE.

## 🔧 Hardware Used

| Component           | Connection | Function         |
| ------------------- | ---------- | ---------------- |
| STM32 Nucleo-F103RB | —          | Main Controller  |
| Potentiometer       | PA0        | ADC Analog Input |
| LED1                | PA5        | Low ADC Level    |
| LED2                | PA6        | Medium ADC Level |
| LED3                | PA7        | High ADC Level   |

## 🔌 Pin Configuration

```text
Potentiometer
    └── Middle Pin → PA0 (ADC1_IN0)

LED1 → PA5
LED2 → PA6
LED3 → PA7
```

## 📊 ADC Thresholds

The STM32F103RB ADC provides a **12-bit conversion**, giving values from **0 to 4095**.

| ADC Range | Level  | LED           |
| --------: | ------ | ------------- |
|    0–1364 | Low    | LED1 (PA5) ON |
| 1365–2729 | Medium | LED2 (PA6) ON |
| 2730–4095 | High   | LED3 (PA7) ON |

## ⚙️ Working Principle

The potentiometer produces a variable analog voltage between approximately 0 V and 3.3 V. This voltage is applied to **PA0**, which is configured as **ADC1 Channel 0**.

The ADC converts the analog voltage into a digital value between **0 and 4095**. The program compares this value with predefined thresholds:

```c
if (ADC_Value < ADC_LOW_THRESHOLD)
{
    LED_On(&LED);
    LED_Off(&LED1);
    LED_Off(&LED2);
}
else if (ADC_Value < ADC_HIGH_THRESHOLD)
{
    LED_Off(&LED);
    LED_On(&LED1);
    LED_Off(&LED2);
}
else
{
    LED_Off(&LED);
    LED_Off(&LED1);
    LED_On(&LED2);
}
```

As the potentiometer is rotated, the active LED changes according to the ADC level.

## 🛠️ Software Used

* **STM32CubeIDE**
* **STM32 HAL Library**
* **C Programming Language**
* **STM32F103RB**
* **GitHub**

## 📁 Project Structure

```text
STM32-ADC-LED-Control/
│
├── Core/
│   ├── Inc/
│   │   ├── main.h
│   │   └── ADC_HAL.h
│   │
│   └── Src/
│       ├── main.c
│       └── ADC_HAL.c
│
├── Drivers/
│   └── STM32F1xx_HAL_Driver/
│
├── README.md
└── STM32_ADC_LED_Control.ioc
```

## ▶️ How to Run

1. Clone or download this repository.
2. Open the project in **STM32CubeIDE**.
3. Connect the STM32 Nucleo-F103RB board to the computer.
4. Connect the potentiometer and three LEDs according to the pin configuration.
5. Build the project.
6. Flash the program to the STM32 board.
7. Rotate the potentiometer and observe the three LED levels.

## ✅ Result

The system successfully reads the potentiometer voltage using the STM32 ADC and controls three LEDs according to the ADC value.

* **Low input → LED1 ON**
* **Medium input → LED2 ON**
* **High input → LED3 ON**

## 📝 Conclusion

This project successfully demonstrates the practical use of **ADC and GPIO peripherals** on the STM32 Nucleo-F103RB. The potentiometer's analog signal is converted into a 12-bit digital value, which is then used to control three LEDs at different input levels. The project provides a basic understanding of ADC configuration, HAL functions, threshold-based decision making, and hardware interfacing.

## 👤 Author

**Ahsan Basharat Ali**

If you have any queries or suggestions, feel free to contact:

**Email:** [ahsanbasharatali38@gmail.com](mailto:ahsanbasharatali38@gmail.com)


If you find this project useful, consider giving the repository a **⭐ Star** on GitHub.
