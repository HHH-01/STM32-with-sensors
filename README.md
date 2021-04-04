
# Version
Developer: Harry Hoa Huynh
Email: harry.hoa.huynh.01@gmail.com
Date: 4/4/2021

# Introduction
Task:
1. Read the temperature via debugging window
		*Temp sensor: PA3
2. Display the temperature via LCD
		 RS	PD1
			EN	PD7
			DB4	PD6
			DB5	PD5
			DB6	PD4
			DB7	PD3
3. Set up PIR at PB8 as an Interrrupt. When detecting motion, turn all 3 LEDs on
		*PIR: PC8 | Use as GPIO_Input (not Interrupt)
		*3x on-board LED: PB0, PB7, PB14
		
		Component:
		1. STM Nucleo STM32F429ZI
		2. Temperature MCP9700A
		3. LCD HC16102
		4. PIR: 31227SC 
