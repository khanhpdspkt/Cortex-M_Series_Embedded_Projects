#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "arm_math.h"                   // ARM::CMSIS:DSP



#define SIGNAL_LEN           320
#define NUM_TAPS             29
#define IMPLUSE_RSP_LENGTH   NUM_TAPS

extern void SystemClock_Config(void);

// Signals and impules response
// 1. input
extern float32_t inputSignal_f32_1kHz_15kHz[SIGNAL_LEN];
// 2. impules response
extern const float32_t impules_response[IMPLUSE_RSP_LENGTH];
// 3. output
float32_t output_signal[IMPLUSE_RSP_LENGTH + SIGNAL_LEN];


uint32_t freq;

// placeholder
float32_t inputSample, 
impResSample, 
outputSample;

// prototypes
void plot_input_signal(void);
void plot_impluse_response(void);
void convolution(float32_t *sig_src, float32_t *sig_dest, float32_t *imp_resp, uint32_t  sig_src_length, uint32_t  imp_resp_length);
void plot_output_signal(void);
void plot_IO(void);

int main() {

	HAL_Init();
	SystemClock_Config();
	freq = HAL_RCC_GetHCLKFreq();
	
	//
	// plot_input_signal();
	// plot_impluse_response();
	convolution(
		(float32_t*) inputSignal_f32_1kHz_15kHz,
		(float32_t*) output_signal,
		(float32_t*) impules_response,
		(uint32_t)   SIGNAL_LEN,
		(uint32_t)   IMPLUSE_RSP_LENGTH
		);

	// arm_conv_f32(
	// 		inputSignal_f32_1kHz_15kHz, 
	// 		SIGNAL_LEN, 
	// 		impules_response, 
	// 		IMPLUSE_RSP_LENGTH, 
	// 		output_signal
	// );

	// plot_output_signal();
	plot_IO();
	
	
	while(1) {
		
	}
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
void plot_impluse_response(void) {
	int i, j;
	for(i = 0; i < IMPLUSE_RSP_LENGTH; i++) {
		impResSample = impules_response[i];
		for(j = 0; j < 3000; j++) {};
	}
}

// 3. 
void convolution(
	float32_t *sig_src,
	float32_t *sig_dest,
	float32_t *imp_resp,
	uint32_t  sig_src_length,
	uint32_t  imp_resp_length
	) {
	uint32_t i, j;
	// initailze
	memset(sig_dest, 0, (sig_src_length + imp_resp_length)*sizeof(float32_t));

	//
	for(i = 0; i < sig_src_length; i++) {
		for(j = 0; j < imp_resp_length; j++) {
			sig_dest[i + j] += (sig_src[i] * imp_resp[j]);
		}
	}
}

// 4.
void plot_output_signal(void) {
	
	int i, j;
	for(i = 0; i < (IMPLUSE_RSP_LENGTH + SIGNAL_LEN); i++) {
		outputSample = output_signal[i];
		for(j = 0; j < 3000; j++) {};
	}

}

// 5. 
void plot_IO(void) {
	int i = 0, j = 0, k, l;
	for (l = 0; l < (SIGNAL_LEN + IMPLUSE_RSP_LENGTH); l++) {
		i++;
		j++;
		if(i == SIGNAL_LEN) i = 0;
		if(j == IMPLUSE_RSP_LENGTH) j = 0;
		if(l == IMPLUSE_RSP_LENGTH + SIGNAL_LEN - 1) l = 0;
		outputSample = output_signal[l];
		inputSample = inputSignal_f32_1kHz_15kHz[i];
		impResSample = impules_response[j];

		for(k = 0; k < 10000; k++) {}
	}
}

///// end 

void SysTick_Handler(void) {
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}




