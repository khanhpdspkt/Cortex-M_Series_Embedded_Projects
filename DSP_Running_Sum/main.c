#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "arm_math.h"                   // ARM::CMSIS:DSP



#define SIGNAL_LEN      200


extern void SystemClock_Config(void);

// Signals and impules response
// 1. input
extern float32_t inputSignal_f32_1kHz_15kHz[SIGNAL_LEN];
// 2. output
float32_t output_signal[SIGNAL_LEN];


uint32_t freq;

// placeholder
float32_t inputSample, 
          outputSample;

// prototypes
void plot_input_signal(void);
void plot_output_signal(void);
void calc_running_sum(float32_t* sig_src, float32_t* sig_dest, uint32_t sig_length);
void plot_IO(void);


int main() {

	HAL_Init();
	SystemClock_Config();
	freq = HAL_RCC_GetHCLKFreq();
	
	calc_running_sum(inputSignal_f32_1kHz_15kHz, output_signal, SIGNAL_LEN);
	// plot_output_signal();
	plot_IO();
	
	while(1) {}
}



// 1.
void plot_input_signal(void) {
	
	int i, j;
	for(i = 0; i < SIGNAL_LEN; i++) {
		inputSample = inputSignal_f32_1kHz_15kHz[i];
		for(j = 0; j < 3000; j++) {};
	}
	
}



// 2.
void plot_output_signal(void) {
	
	int i, j;
	for(i = 0; i < SIGNAL_LEN; i++) {
		outputSample = output_signal[i];
		for(j = 0; j < 3000; j++) {};
	}
	
}

// 3.
void calc_running_sum(float32_t* sig_src, float32_t* sig_dest, uint32_t sig_length) {
	int i;
	sig_dest[0] = sig_src[0];
	for(i = 1; i < sig_length; i++) {
		sig_dest[i] = sig_dest[i - 1] + sig_src[i];
	}
}

// 4. 
void plot_IO(void) {
	int i, j;
	for(i = 0; i < SIGNAL_LEN; i++) {
		inputSample = inputSignal_f32_1kHz_15kHz[i];
		outputSample = output_signal[i];
		for(j = 0; j < 30000; j++) {}
	}
}



///// end 

void SysTick_Handler(void) {
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}




