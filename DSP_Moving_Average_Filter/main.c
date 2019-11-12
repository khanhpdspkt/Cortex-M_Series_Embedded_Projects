#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "arm_math.h"                   // ARM::CMSIS:DSP

#define SIGNAL_LEN    320

extern void SystemClock_Config(void);
// sine wave
extern float32_t inputSignal_f32_1kHz_15kHz[SIGNAL_LEN]; // calculate mean of this sine wave
float32_t output_signal[SIGNAL_LEN];

uint32_t freq;

// placeholder
float32_t inputSample;
float32_t outputSample;

// prototype
void plot_input_signal(void);
void plot_IO(void);
void moving_average(float32_t* sig_src, float32_t* sig_dest, uint32_t  signal_length, uint32_t filter_points);



int main() {

	HAL_Init();
	SystemClock_Config();
	freq = HAL_RCC_GetHCLKFreq();
	
	
	// plot_input_signal();
	moving_average(
		(float32_t*) inputSignal_f32_1kHz_15kHz,
		(float32_t*) output_signal,
		(uint32_t)   SIGNAL_LEN,
		(uint32_t)   11
	);
	
	plot_IO();
	
	while(1) {}
}




// 1. 
void moving_average(
	float32_t* sig_src,       // [in]
	float32_t* sig_dest,      // [out]
	uint32_t   signal_length, // [in]
	uint32_t   filter_points  // [in]
) {
	int i, j;
	for(i = floor(filter_points / 2); i < (signal_length - (filter_points / 2)) - 1; i++) {

		sig_dest[i] = 0;

		for(j = -(floor(filter_points / 2)); j < floor(filter_points / 2); j++) {
			sig_dest[i] += sig_src[i + j];
		}

		sig_dest[i] /= filter_points; 
	}

}


// 2.
void plot_input_signal(void) {
	int i, j;
	for(i = 0; i < SIGNAL_LEN; i++) {
		inputSample = inputSignal_f32_1kHz_15kHz[i];
		for(j = 0; j < 3000; j++) {}
	}
}

// 3.
void plot_IO(void) {
	int i, j;
	for(i = 0; i < SIGNAL_LEN; i++) {
		inputSample = inputSignal_f32_1kHz_15kHz[i];
		outputSample = output_signal[i];
		for(j = 0; j < 3000; j++) {}
	}
}


//////////////////// END

void SysTick_Handler(void){
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
	
}

