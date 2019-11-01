#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "arm_math.h"                   // ARM::CMSIS:DSP
#include "low_pass_filter.h"
#include "sine_generator.h"

// frequencies
#define SAMPLING_FREQ  1000
#define SIGNAL_FREQ    10
#define NOISE_FREQ     50


extern void SystemClock_Config(void);

uint32_t freq;

// sets
sine_generator_q15_t signal_set;
sine_generator_q15_t noise_set;

// placeholder
q15_t sine, noise, disturbed, filtered;

int main() {
	
	HAL_Init();
	SystemClock_Config();
	
	freq = HAL_RCC_GetHCLKFreq();

	// 1.
	sine_generator_init_q15(&signal_set, SIGNAL_FREQ, SAMPLING_FREQ);
	sine_generator_init_q15(&noise_set, NOISE_FREQ, SAMPLING_FREQ);

	// 2.
	low_pass_filter_init();


	
	while(1) {
		sine  = sine_calc_sample_q15(&signal_set) / 2;
		noise = sine_calc_sample_q15(&noise_set) / 6;
		disturbed = sine + noise;
		filtered = low_pass_filter(&disturbed);
		HAL_Delay(1);
	}

}


void SysTick_Handler(void) {
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

