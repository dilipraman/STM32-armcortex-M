# STM32F411RE Learning Journey 🚀

Welcome to my embedded systems learning repository!  
This project documents my hands-on learning with the **STM32F411RE** microcontroller based on the **ARM Cortex-M4 processor** using the **Nucleo-F411RE development board**.

I'm a passionate beginner (a.k.a. "new bee") exploring embedded firmware development using **STM32CubeIDE**.

---

## 📘 What I'm Learning

### 💡 Microcontroller: STM32F411RE
- Based on ARM Cortex-M4 core.
- Developed using STMicroelectronics’ Nucleo platform.
- I'm diving deep into understanding how the microcontroller operates — starting from registers to low-level programming.

### 🛠️ Development Environment
- **STM32CubeIDE** – official IDE for STM32 development.
- Register-level programming with reference to STM32F411RE datasheet and RM0383 reference manual.

---

## 🚀 Project 1: LED Blinking

**Goal:** Blink an LED using GPIO with direct register access.

### 🔍 What I Learned:
- How to enable **GPIO** using **RCC (Reset and Clock Control)**.
- Understanding of **RCC registers** and how to enable the clock for GPIO peripherals.
- Accessing **GPIO registers** using memory mapping.
- Practical usage of datasheet and reference manual to control the hardware directly.
- How the **AHB1ENR** and **MODER/ODR** registers work.

### 📂 Code Location:
Check the `led_blink_gpio_register` folder for the full source code and step-by-step comments.

---

## 📚 References
- STM32F411RE Datasheet  
- RM0383 Reference Manual  
- STM32CubeIDE Documentation

---

## 🛤️ On the Way…
This is just the beginning of my embedded journey. I’ll be sharing:
- More register-level examples
- UART, Timers, Interrupts
- Peripherals and driver development

Stay tuned for more learning logs and code experiments! 😎  
**Let’s blink, debug, and build!**

---

## 🤝 Connect with Me

I'm always up for learning and collaboration.  
Feel free to star⭐, fork 🍴, or suggest improvements!

