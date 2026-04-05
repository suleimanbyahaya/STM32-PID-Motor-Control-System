#include "main.h"
#include <stdio.h>
#include <string.h>

/* PID Parameters */
float Kp = 1.0, Ki = 0.5, Kd = 0.1;
float setpoint = 0, measured_speed = 0;
float error = 0, previous_error = 0, integral = 0;
float control_signal = 0;

char uart_msg[100];

ADC_HandleTypeDef hadc1;
UART_HandleTypeDef huart2;
TIM_HandleTypeDef htim2;

/* PID Function */
float PID_Controller(float setpoint, float measured)
{
  error = setpoint - measured;
  integral += error;
  float derivative = error - previous_error;

  float output = (Kp * error) + (Ki * integral) + (Kd * derivative);

  previous_error = error;

  return output;
}

/* Sensor Task */
void SensorTask(void *argument)
{
  while (1)
  {
    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, 10);
    setpoint = HAL_ADC_GetValue(&hadc1);

    measured_speed = setpoint; // estimation

    osDelay(50);
  }
}

/* PID Task */
void PIDTask(void *argument)
{
  while (1)
  {
    control_signal = PID_Controller(setpoint, measured_speed);

    if (control_signal < 0) control_signal = 0;
    if (control_signal > 1000) control_signal = 1000;

    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, control_signal);

    osDelay(50);
  }
}

/* UART Task */
void UARTTask(void *argument)
{
  while (1)
  {
    sprintf(uart_msg, "SP: %.2f Speed: %.2f PWM: %.2f\r\n",
            setpoint, measured_speed, control_signal);

    HAL_UART_Transmit(&huart2, (uint8_t*)uart_msg, strlen(uart_msg), 100);

    osDelay(1000);
  }
}

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_TIM2_Init();
  MX_USART2_UART_Init();

  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);

  osKernelInitialize();

  osThreadNew(SensorTask, NULL, NULL);
  osThreadNew(PIDTask, NULL, NULL);
  osThreadNew(UARTTask, NULL, NULL);

  osKernelStart();

  while (1)
  {
  }
}
