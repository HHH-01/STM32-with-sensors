/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <string.h>
#include <stdio.h>

// LCD related functions
void LCD_init(void);
void LCD_write(unsigned char data);
void place_lcd_cursor(unsigned char lineno);
void LCD_write_word(char data[], int length);
void LCD_write_decimal(double data, int length);
void LCD_Clear(void);

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#

#define RS GPIO_PIN_1
#define EN GPIO_PIN_7

#define DB4 GPIO_PIN_6
#define DB5 GPIO_PIN_5
#define DB6 GPIO_PIN_4
#define DB7 GPIO_PIN_3

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */
 
 // Start the LCD
	LCD_init();
	place_lcd_cursor(1);
	
	LCD_write_word("Starting", 8);


  
	
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5 
                          |GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pins : PD1 PD3 PD4 PD5 
                           PD6 PD7 */
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5 
                          |GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/*******************************
 * LCD_init()
 * Inputs: NONE
 * Outputs: NONE
 * LCD Initialization
 * Read the manual carefully
 * We are doing initialization by instruction
 * Don't rush it.
 *******************************
 */

void LCD_init(){

// STEP 1: Wait for 100ms for power-on-reset to take effect
	HAL_Delay(100);
// STEP 2: Set RS pin LOW to send instructions
	HAL_GPIO_WritePin(GPIOD, RS, 0);
// Send instructions using following format:
// Set EN=HIGH; Send 4-bit instruction; Set EN=low; delay 20ms;
	
// STEP 3a-3d: Set 4-bit mode (takes a total of 4 steps)
	HAL_GPIO_WritePin(GPIOD, EN, 1);
	
	HAL_GPIO_WritePin(GPIOD, DB7, 0);
	HAL_GPIO_WritePin(GPIOD, DB6, 0);
	HAL_GPIO_WritePin(GPIOD, DB5, 1);
	HAL_GPIO_WritePin(GPIOD, DB4, 1);
	
	HAL_GPIO_WritePin(GPIOD, EN, 0);
	HAL_Delay(20);
	
	HAL_GPIO_WritePin(GPIOD, EN, 1);
	
	HAL_GPIO_WritePin(GPIOD, DB7, 0);
	HAL_GPIO_WritePin(GPIOD, DB6, 0);
	HAL_GPIO_WritePin(GPIOD, DB5, 1);
	HAL_GPIO_WritePin(GPIOD, DB4, 1);
	
	HAL_GPIO_WritePin(GPIOD, EN, 0);
	HAL_Delay(20);
	
	HAL_GPIO_WritePin(GPIOD, EN, 1);
	
	HAL_GPIO_WritePin(GPIOD, DB7, 0);
	HAL_GPIO_WritePin(GPIOD, DB6, 0);
	HAL_GPIO_WritePin(GPIOD, DB5, 1);
	HAL_GPIO_WritePin(GPIOD, DB4, 1);
	
	HAL_GPIO_WritePin(GPIOD, EN, 0);
	HAL_Delay(20);
	
	HAL_GPIO_WritePin(GPIOD, EN, 1);
	
	HAL_GPIO_WritePin(GPIOD, DB7, 0);
	HAL_GPIO_WritePin(GPIOD, DB6, 0);
	HAL_GPIO_WritePin(GPIOD, DB5, 1);
	HAL_GPIO_WritePin(GPIOD, DB4, 0);
	
	HAL_GPIO_WritePin(GPIOD, EN, 0);
	HAL_Delay(20);
// STEP 4: Set 2 line display -- treats 16 char as 2 lines
	HAL_GPIO_WritePin(GPIOD, EN, 1);
	
	HAL_GPIO_WritePin(GPIOD, DB7, 0);
	HAL_GPIO_WritePin(GPIOD, DB6, 0);
	HAL_GPIO_WritePin(GPIOD, DB5, 1);
	HAL_GPIO_WritePin(GPIOD, DB4, 0);
	
	HAL_GPIO_WritePin(GPIOD, EN, 0);
	HAL_Delay(20);
	
	HAL_GPIO_WritePin(GPIOD, EN, 1);
	
	HAL_GPIO_WritePin(GPIOD, DB7, 1);
	HAL_GPIO_WritePin(GPIOD, DB6, 0);
	HAL_GPIO_WritePin(GPIOD, DB5, 0);
	HAL_GPIO_WritePin(GPIOD, DB4, 0);
	
	HAL_GPIO_WritePin(GPIOD, EN, 0);
	HAL_Delay(20);
// STEP 5: Set DISPLAY to OFF
	HAL_GPIO_WritePin(GPIOD, EN, 1);
	
	HAL_GPIO_WritePin(GPIOD, DB7, 0);
	HAL_GPIO_WritePin(GPIOD, DB6, 0);
	HAL_GPIO_WritePin(GPIOD, DB5, 0);
	HAL_GPIO_WritePin(GPIOD, DB4, 0);
	
	HAL_GPIO_WritePin(GPIOD, EN, 0);
	HAL_Delay(20);
	
	HAL_GPIO_WritePin(GPIOD, EN, 1);
	
	HAL_GPIO_WritePin(GPIOD, DB7, 1);
	HAL_GPIO_WritePin(GPIOD, DB6, 0);
	HAL_GPIO_WritePin(GPIOD, DB5, 0);
	HAL_GPIO_WritePin(GPIOD, DB4, 0);
	
	HAL_GPIO_WritePin(GPIOD, EN, 0);
	HAL_Delay(20);
// STEP 6: CLEAR DISPLAY
	HAL_GPIO_WritePin(GPIOD, EN, 1);
	
	HAL_GPIO_WritePin(GPIOD, DB7, 0);
	HAL_GPIO_WritePin(GPIOD, DB6, 0);
	HAL_GPIO_WritePin(GPIOD, DB5, 0);
	HAL_GPIO_WritePin(GPIOD, DB4, 0);
	
	HAL_GPIO_WritePin(GPIOD, EN, 0);
	HAL_Delay(20);
	
	HAL_GPIO_WritePin(GPIOD, EN, 1);
	
	HAL_GPIO_WritePin(GPIOD, DB7, 0);
	HAL_GPIO_WritePin(GPIOD, DB6, 0);
	HAL_GPIO_WritePin(GPIOD, DB5, 0);
	HAL_GPIO_WritePin(GPIOD, DB4, 1);
	
	HAL_GPIO_WritePin(GPIOD, EN, 0);
	HAL_Delay(20);
// STEP 7: SET ENTRY MODE - Auto increment; no scrolling
	HAL_GPIO_WritePin(GPIOD, EN, 1);
	
	HAL_GPIO_WritePin(GPIOD, DB7, 0);
	HAL_GPIO_WritePin(GPIOD, DB6, 0);
	HAL_GPIO_WritePin(GPIOD, DB5, 0);
	HAL_GPIO_WritePin(GPIOD, DB4, 0);
	
	HAL_GPIO_WritePin(GPIOD, EN, 0);
	HAL_Delay(20);
	
	HAL_GPIO_WritePin(GPIOD, EN, 1);
	
	HAL_GPIO_WritePin(GPIOD, DB7, 0);
	HAL_GPIO_WritePin(GPIOD, DB6, 1);
	HAL_GPIO_WritePin(GPIOD, DB5, 1);
	HAL_GPIO_WritePin(GPIOD, DB4, 0);
	
	HAL_GPIO_WritePin(GPIOD, EN, 0);
	HAL_Delay(20);
// STEP 8: Set Display to ON with Cursor and Blink.
	HAL_GPIO_WritePin(GPIOD, EN, 1);
	
	HAL_GPIO_WritePin(GPIOD, DB7, 0);
	HAL_GPIO_WritePin(GPIOD, DB6, 0);
	HAL_GPIO_WritePin(GPIOD, DB5, 0);
	HAL_GPIO_WritePin(GPIOD, DB4, 0);
	
	HAL_GPIO_WritePin(GPIOD, EN, 0);
	HAL_Delay(20);
	
	HAL_GPIO_WritePin(GPIOD, EN, 1);
	
	HAL_GPIO_WritePin(GPIOD, DB7, 1);
	HAL_GPIO_WritePin(GPIOD, DB6, 1);
	HAL_GPIO_WritePin(GPIOD, DB5, 1);
	HAL_GPIO_WritePin(GPIOD, DB4, 1);
	
	HAL_GPIO_WritePin(GPIOD, EN, 0);
	HAL_Delay(20);
	
	HAL_GPIO_WritePin(GPIOD, RS, 1);
}

/*******************************
 * place_lcd_cursor()
 * Inputs: unsigned character
 * Outputs: NONE
 * sets Cursor position to
 * Line 1, character 1 (hex address 0x80)
 * or Line 2, character 1 (hex addres 0xC0)
 *
 *******************************
 */

void place_lcd_cursor(unsigned char lineno){
	HAL_GPIO_WritePin(GPIOD, RS, 0);
	if(lineno == 1){					//To place at line 1, send address 0x80
		HAL_GPIO_WritePin(GPIOD, EN, 1);
		
		HAL_GPIO_WritePin(GPIOD, DB7, 1);
		HAL_GPIO_WritePin(GPIOD, DB6, 0);
		HAL_GPIO_WritePin(GPIOD, DB5, 0);
		HAL_GPIO_WritePin(GPIOD, DB4, 0);
		
		HAL_GPIO_WritePin(GPIOD, EN, 0);
		HAL_Delay(20);
		
		HAL_GPIO_WritePin(GPIOD, EN, 1);
		
		HAL_GPIO_WritePin(GPIOD, DB7, 0);
		HAL_GPIO_WritePin(GPIOD, DB6, 0);
		HAL_GPIO_WritePin(GPIOD, DB5, 0);
		HAL_GPIO_WritePin(GPIOD, DB4, 0);
		
		HAL_GPIO_WritePin(GPIOD, EN, 0);
		HAL_Delay(1);
	}
	else{											//Place at line two, send address 0xC0
		HAL_GPIO_WritePin(GPIOD, EN, 1);
		
		HAL_GPIO_WritePin(GPIOD, DB7, 1);
		HAL_GPIO_WritePin(GPIOD, DB6, 1);
		HAL_GPIO_WritePin(GPIOD, DB5, 0);
		HAL_GPIO_WritePin(GPIOD, DB4, 0);
		
		HAL_GPIO_WritePin(GPIOD, EN, 0);
		HAL_Delay(20);
		
		HAL_GPIO_WritePin(GPIOD, EN, 1);
		
		HAL_GPIO_WritePin(GPIOD, DB7, 0);
		HAL_GPIO_WritePin(GPIOD, DB6, 0);
		HAL_GPIO_WritePin(GPIOD, DB5, 0);
		HAL_GPIO_WritePin(GPIOD, DB4, 0);
		
		HAL_GPIO_WritePin(GPIOD, EN, 0);
		HAL_Delay(1);
	}
	HAL_GPIO_WritePin(GPIOD, RS, 1);
}



/*******************************
 * LCD_write()
 * Inputs: unsigned character data (8-bit)
 * Outputs: NONE
 * writes the character to LCD.
 *
 *******************************
 */

void LCD_write(unsigned char data)
{
	HAL_GPIO_WritePin(GPIOD, RS, 1);
	
	HAL_GPIO_WritePin(GPIOD, EN, 1);
		//For each bit check if it is a one or zero and send output accordingly
		if(data & 0x80){
			HAL_GPIO_WritePin(GPIOD, DB7, 1);
		}
		else{
			HAL_GPIO_WritePin(GPIOD, DB7, 0);
		}
		if(data & 0x40){
			HAL_GPIO_WritePin(GPIOD, DB6, 1);
		}
		else{
			HAL_GPIO_WritePin(GPIOD, DB6, 0);
		}
		if(data & 0x20){
			HAL_GPIO_WritePin(GPIOD, DB5, 1);
		}
		else{
			HAL_GPIO_WritePin(GPIOD, DB5, 0);
		}
		if(data & 0x10){
			HAL_GPIO_WritePin(GPIOD, DB4, 1);
		}
		else{
			HAL_GPIO_WritePin(GPIOD, DB4, 0);
		}
		
		HAL_GPIO_WritePin(GPIOD, EN, 0);
		HAL_Delay(1);
		
		HAL_GPIO_WritePin(GPIOD, EN, 1);
		
		if(data & 0x08){
			HAL_GPIO_WritePin(GPIOD, DB7, 1);
		}
		else{
			HAL_GPIO_WritePin(GPIOD, DB7, 0);
		}
		if(data & 0x04){
			HAL_GPIO_WritePin(GPIOD, DB6, 1);
		}
		else{
			HAL_GPIO_WritePin(GPIOD, DB6, 0);
		}
		if(data & 0x02){
			HAL_GPIO_WritePin(GPIOD, DB5, 1);
		}
		else{
			HAL_GPIO_WritePin(GPIOD, DB5, 0);
		}
		if(data & 0x01){
			HAL_GPIO_WritePin(GPIOD, DB4, 1);
		}
		else{
			HAL_GPIO_WritePin(GPIOD, DB4, 0);
		}
		
		HAL_GPIO_WritePin(GPIOD, EN, 0);
		HAL_Delay(1);
		
	HAL_GPIO_WritePin(GPIOD, RS, 0);
}


/*******************************
 * LCD_write_word()
 * Inputs: string data and int length
 * Outputs: NONE
 * writes the string to LCD.
 *
 *******************************
 */

void LCD_write_word(char data[], int length){
	int i;
	//Send first 8 characters
	for(i = 0; i<length && i<8; i++){
		LCD_write(data[i]);
	}
	//If it is longer than 8 characters then change the line
	if(length > 8){
		place_lcd_cursor(2);
	}
	//Place remaining characters
	for(i = 8; i<length; i++){
		LCD_write(data[i]);
	}
	
}

/*******************************
 * LCD_write_decimal()
 * Inputs: double data and int length
 * Outputs: NONE
 * writes the data to LCD.
 *
 *******************************
 */

void LCD_write_decimal(double data, int length){
	char string[17];
	snprintf(string,length+1,"%f",data);
	LCD_write_word(string,length);
}

/*******************************
 * LCD_Clear()
 * Inputs: NONE
 * Outputs: NONE
 * clears the LCD and resets cursor
 *
 *******************************
 */
void LCD_Clear(void){
	//Send clear command, same as when initializing
	HAL_GPIO_WritePin(GPIOD, RS, 0);
	
	HAL_GPIO_WritePin(GPIOD, EN, 1);
	
	HAL_GPIO_WritePin(GPIOD, DB7, 0);
	HAL_GPIO_WritePin(GPIOD, DB6, 0);
	HAL_GPIO_WritePin(GPIOD, DB5, 0);
	HAL_GPIO_WritePin(GPIOD, DB4, 0);
	
	HAL_GPIO_WritePin(GPIOD, EN, 0);
	HAL_Delay(20);
	
	HAL_GPIO_WritePin(GPIOD, EN, 1);
	
	HAL_GPIO_WritePin(GPIOD, DB7, 0);
	HAL_GPIO_WritePin(GPIOD, DB6, 0);
	HAL_GPIO_WritePin(GPIOD, DB5, 0);
	HAL_GPIO_WritePin(GPIOD, DB4, 1);
	
	HAL_GPIO_WritePin(GPIOD, EN, 0);
	HAL_Delay(20);
	HAL_GPIO_WritePin(GPIOD, RS, 1);
}


/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
