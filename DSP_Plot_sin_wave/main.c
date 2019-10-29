#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "arm_math.h"                   // ARM::CMSIS:DSP

#define SIG_LENGTH 320

uint32_t freq;

extern void SystemClock_Config(void);
extern float32_t inputSignal_f32_1kHz_15kHz[SIG_LENGTH];
void plot_Sin_wave(void);

float32_t inputSample;

int main (void) {
    
    HAL_Init();
    SystemClock_Config();
    freq = HAL_RCC_GetHCLKFreq();
    
    plot_Sin_wave();
    
    while(1) {
    }
}

void plot_Sin_wave(void) {
    int i = 0, j;
	
	  while(1) {
			
			inputSample = inputSignal_f32_1kHz_15kHz[i];
			for(j = 0; j < 3000; j++) {}; // delay
			
			i = (i == SIG_LENGTH - 1) ? 0 : i + 1;
		}
}

void SysTick_Handler(void) {
    HAL_IncTick();
    HAL_SYSTICK_IRQHandler();
}

