/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "board.h"
#include "rng.h"
#include "st7735.h"
#include "lcd.h"
#include "printf.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
uint8_t  text[20] = "Hello, World!";
uint32_t tick,tick_now;
/* USER CODE END Variables */
/* Definitions for BlinkTask */
osThreadId_t BlinkTaskHandle;
const osThreadAttr_t BlinkTask_attributes = {
  .name = "BlinkTask",
  .stack_size = 200 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for HelloWorldTask */
osThreadId_t HelloWorldTaskHandle;
const osThreadAttr_t HelloWorldTask_attributes = {
  .name = "HelloWorldTask",
  .stack_size = 200 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartBlinkTask(void *argument);
void StartTaskHelloWorld(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of BlinkTask */
  BlinkTaskHandle = osThreadNew(StartBlinkTask, NULL, &BlinkTask_attributes);

  /* creation of HelloWorldTask */
  HelloWorldTaskHandle = osThreadNew(StartTaskHelloWorld, NULL, &HelloWorldTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartBlinkTask */
/**
  * @brief  Function implementing the BlinkTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartBlinkTask */
void StartBlinkTask(void *argument)
{
  /* USER CODE BEGIN StartBlinkTask */
  board_button_init();
  board_led_init();
  tick = HAL_GetTick() + 200;
  tick_now = HAL_GetTick();
  uint32_t rng;
  /* Infinite loop */
  for(;;)
  {  
    tick_now = HAL_GetTick();
    if(board_button_getstate())
    {
      if(tick_now >= tick)
      {
        tick = tick_now + 200;
        board_led_toggle();
      }
    }
    else
    {
      if(tick_now >= tick)
      {
		    HAL_RNG_GenerateRandomNumber(&hrng,&rng);
        tick = tick_now + rng%600;
        board_led_toggle();
      }
    }
    osDelay(1);
  }
  /* USER CODE END StartBlinkTask */
}

/* USER CODE BEGIN Header_StartTaskHelloWorld */
/**
* @brief Function implementing the HelloWorldTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTaskHelloWorld */
void StartTaskHelloWorld(void *argument)
{
  /* USER CODE BEGIN StartTaskHelloWorld */
  
  /* Infinite loop */
  for(;;)
  {
    LCD_ShowString(4, 58, 160, 16, 16, text);
    osDelay(1);
  }
  /* USER CODE END StartTaskHelloWorld */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

