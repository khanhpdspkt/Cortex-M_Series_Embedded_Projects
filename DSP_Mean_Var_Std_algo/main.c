#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "arm_math.h"                   // ARM::CMSIS:DSP

#define SIGNAL_LEN    320

extern void SystemClock_Config(void);
// sine wave
extern float32_t inputSignal_f32_1kHz_15kHz[SIGNAL_LEN]; // calculate mean of this sine wave

uint32_t freq;

// placeholder
float32_t inputSample;
float32_t inputMean;
float32_t inputVariance;
float32_t inputStandardDeviation;

// prototype
void plot_input_signal(void);
float32_t signal_mean(float32_t *signal_src, uint32_t signal_length);
float32_t signal_variance(float32_t *signal_src, uint32_t signal_length, float32_t signal_mean);
float32_t signal_standard_deviation (float32_t signal_variance);


int main() {

	HAL_Init();
	SystemClock_Config();
	freq = HAL_RCC_GetHCLKFreq();
	
	//
	// plot_input_signal();
	
	/* Mean */
	// inputMean = signal_mean((float32_t *)&inputSignal_f32_1kHz_15kHz[0], (uint32_t)SIGNAL_LEN); // type casting for readability
	// ARM API
	arm_mean_f32(inputSignal_f32_1kHz_15kHz, SIGNAL_LEN, &inputMean);
  // [Note] &inputSignal_f32_1kHz_15kHz[0] and inputSignal_f32_1kHz_15kHz are the same address.
	
	/* Variance */
	// inputVariance = signal_variance((float32_t *)inputSignal_f32_1kHz_15kHz, (uint32_t) SIGNAL_LEN, (float32_t) inputMean); // type casting for readability
	arm_var_f32(inputSignal_f32_1kHz_15kHz, SIGNAL_LEN, &inputVariance);
	
	/* Standard Deviation */
	// inputStandardDeviation = signal_standard_deviation(inputVariance);
	arm_std_f32(inputSignal_f32_1kHz_15kHz, SIGNAL_LEN, &inputStandardDeviation);
	
	while(1) {}
}




void SystemTickHandler(void) {
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}





void plot_input_signal(void) {
	int i, j;
	for(i = 0; i < SIGNAL_LEN; i++) {
		inputSample = inputSignal_f32_1kHz_15kHz[i];
		for(j = 0; j < 3000; j++) {}
	}
}

// use loop the calculate mean of signal, better way is using arm_mean_f32 
float32_t signal_mean(float32_t *signal_src, uint32_t signal_length) {
	float32_t mean = 0.0;
	uint32_t i;
	for(i = 0; i < signal_length; i++) {
		mean = mean + signal_src[i];
	}
	mean /= (float32_t)signal_length;
	
	return mean;
}

float32_t signal_variance(float32_t *signal_src, uint32_t signal_length, float32_t signal_mean) {
	
	float32_t variance = 0.0;
	uint32_t i;
	for(i = 0; i < signal_length; i++) {
		variance = variance + pow((signal_src[i] - signal_mean), 2);
	}
	variance /= (signal_length - 1);
	
	return variance;
}

float32_t signal_standard_deviation (float32_t signal_variance) {
	float32_t std = sqrtf(signal_variance);
	
	return std;
}

