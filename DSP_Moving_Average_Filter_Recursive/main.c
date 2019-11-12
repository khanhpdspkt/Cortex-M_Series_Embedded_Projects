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
void recursive_moving_average(float32_t* sig_src, float32_t* sig_dest, uint32_t  signal_length, uint32_t filter_points);


int main() {

	HAL_Init();
	SystemClock_Config();
	freq = HAL_RCC_GetHCLKFreq();
	
	
	// plot_input_signal();
	recursive_moving_average(
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

	for(int i = floor(filter_points / 2); i < (signal_length - (filter_points / 2)) - 1; i++) {

		sig_dest[i] = 0;

		for(int j = -(floor(filter_points / 2)); j < floor(filter_points / 2); j++) {
			sig_dest[i] += sig_src[i + j];
		}

		sig_dest[i] /= filter_points; 
	}

}

// 2.
void recursive_moving_average(
	float32_t* sig_src,       // [in]
	float32_t* sig_dest,      // [out]
	uint32_t   signal_length, // [in]
	uint32_t   filter_points  // [in]
) {

	float64_t acc = 0;
	for(int i = 0; i < filter_points - 1; i++) {
		acc += sig_src[i];
	}

	sig_dest[(filter_points - 1) / 2] = acc / filter_points;

	for(int i = ceil(filter_points / 2); i < (signal_length - (filter_points / 2)) - 1; i++) {
		acc += sig_src[i + (filter_points - 1) / 2] - sig_src[i - ((uint8_t)ceil(filter_points / 2))];
		sig_dest[i] = acc / filter_points;
	}

}

// 3.
void plot_input_signal(void) {
	int i, j;
	for(i = 0; i < SIGNAL_LEN; i++) {
		inputSample = inputSignal_f32_1kHz_15kHz[i];
		for(j = 0; j < 3000; j++) {}
	}
}

// 4.
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

