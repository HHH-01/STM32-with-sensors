
## Version
* Info: Connect STM32 with different sensors such as Temp or PIR and display to an LCD
* Developer: HHH
* Date: 4/2021

## Introduction
Task:
1. Read the temperature via debugging window
* Temp sensor: PA3
2. Display the temperature via LCD
* RS	PD1
* EN	PD7
* DB4	PD6
* DB5	PD5
* DB6	PD4
* DB7	PD3
3. Set up PIR at PB8 as an Interrrupt. When detecting motion, turn all 3 LEDs on
* PIR: PC8 | Use as an Interruput with Repeattable Trigger Enable by HW
* 3x on-board LED: PB0, PB7, PB14
		
## Component
1. STM Nucleo STM32F429ZI
2. Temperature MCP9700A
3. LCD HC16102
4. PIR: 31227SC (Enable Repeattable Trigger to prevent a defaut reset by HW)

## Focus on
1. EXTI9_5_IRQHandler in stm32f4xx_it.c for PIR Interrupt
2. main.c for everything else

## Picture for reference
![STM32CubeMX](https://github.com/HHH-01/STM32/blob/f028fc426ff353cd08ee4fa8f19110355a3476b8/Images/STM32CubeMx.PNG)

![Circuit Set up](https://github.com/HHH-01/STM32/blob/f028fc426ff353cd08ee4fa8f19110355a3476b8/Images/Circuit.jpg)

![Debugging Window](https://github.com/HHH-01/STM32/blob/63101e5e8e58ca9a7d79cf8a742d6c34a3291a6b/Images/DebuggingWindow.PNG)
