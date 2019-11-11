#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "arm_math.h"                   // ARM::CMSIS:DSP

#define	SIGNAL_LEN       200


// signals
extern void SystemClock_Config(void);
extern float32_t inputSignal_f32_1kHz_15kHz[SIGNAL_LEN];


float32_t output_signal_ReX[SIGNAL_LEN / 2];
float32_t output_signal_ImX[SIGNAL_LEN / 2];
float32_t output_signal_Meg[SIGNAL_LEN / 2];
float32_t output_signal_Pha[SIGNAL_LEN / 2];


// prototypes
void plot_input_signal(void);

// placeholder
float32_t inputSample;


void calc_sig_dft(float32_t* sig_src, float32_t* sig_dest_ReX, float32_t* sig_dest_ImX, uint32_t sig_src_length);
void calc_sig_idft(float32_t* idft_out, float32_t* sig_src_ReX, float32_t* sig_src_ImX, uint32_t idft_length);
void rect_to_polar_conversion(float32_t* sig_src_ReX, float32_t* sig_src_ImX, float32_t* sig_out_Mag, float32_t* sig_out_Phase, uint32_t   sig_src_length);
void rect_to_polar_conversion(float32_t* sig_src_ReX, float32_t* sig_src_ImX, float32_t* sig_out_Mag, float32_t* sig_out_Phase,uint32_t   sig_src_length);

uint32_t freq;


int main() {
	
	HAL_Init();
	SystemClock_Config();
	freq = HAL_RCC_GetHCLKFreq();

	// plot_ecg_signal();


	calc_sig_dft(
		(float32_t*) inputSignal_f32_1kHz_15kHz, // [in]
		(float32_t*) output_signal_ReX,          // [out]
		(float32_t*) output_signal_ImX,          // [out]
		(uint32_t)   SIGNAL_LEN                  // [in]
	);
	
	rect_to_polar_conversion( 
		(float32_t*) output_signal_ReX,     // [in]
		(float32_t*) output_signal_ImX,     // [in]
		(float32_t*) output_signal_Meg,     // [out]
		(float32_t*) output_signal_Pha,     // [out]
		(uint32_t)   SIGNAL_LEN             // [in]
	);


	while(1){}
		
}




// 1.
void calc_sig_idft(
	float32_t* idft_out,     // [out] time domain
	float32_t* sig_src_ReX,  // [in]  freq domain
	float32_t* sig_src_ImX,  // [in]  freq domain
	uint32_t   idft_length   // [in]
){
	
	for(int k = 0; k < (idft_length / 2); k++) {
		sig_src_ReX[k] =  sig_src_ReX[k] / (idft_length / 2);
		sig_src_ImX[k] = -sig_src_ImX[k] / (idft_length / 2);
	}
	
	sig_src_ReX[0] =  sig_src_ReX[0] / (idft_length / 2);
	sig_src_ImX[0] = -sig_src_ImX[0] / (idft_length / 2);
	
	for(int i = 0; i < idft_length; i++)
	{
		idft_out[i] = 0;
	}
	
	for(int k = 0; k < (idft_length / 2); k++)
	{
		for(int i = 0; i < idft_length; i++)
		{

			idft_out[i] =  idft_out[i] + sig_src_ReX[k] * cos(2*PI*k*i / idft_length);
			idft_out[i] =  idft_out[i] + sig_src_ImX[k] * sin(2*PI*k*i / idft_length);

		}
	}
}



// 2.
void calc_sig_dft(
    float32_t* sig_src,       // [in]   time domain
    float32_t* sig_dest_ReX,  // [out]  freq domain
    float32_t* sig_dest_ImX,  // [out]  freq domain
    uint32_t   sig_src_length // [in]
) {
    int n, k, i;
    // Initialize
    for(i = 0; i < sig_src_length / 2; i++) {
        sig_dest_ReX[i] = 0;
        sig_dest_ImX[i] = 0;
    }

    for(k = 0; k < sig_src_length / 2; k++) {

        for(n = 0; n < sig_src_length; n++) {

            sig_dest_ReX[k] += sig_src[n] * cos(2*PI*k*n / sig_src_length);
            sig_dest_ImX[k] -= sig_src[n] * sin(2*PI*k*n / sig_src_length);

        }

    }
}


// 3.
void plot_input_signal() {
	for(int i = 0; i < SIGNAL_LEN; i++) {
		inputSample = inputSignal_f32_1kHz_15kHz[i];
		for(int j = 0; j < 3000; j++) {}
	}
}

// 4.
void rect_to_polar_conversion( 
	float32_t* sig_src_ReX,     // [in]
	float32_t* sig_src_ImX,     // [in]
	float32_t* sig_out_Mag,     // [out]
	float32_t* sig_out_Phase,   // [out]
	uint32_t   sig_src_length   // [in]
){
	
	for(int k = 0; k < sig_src_length; k++) {

		sig_out_Mag[k] = sqrt(powf(sig_src_ReX[k], 2) + powf(sig_src_ImX[k], 2));

		if(sig_src_ReX[k] == 0) 
			sig_src_ReX[k] = pow(10, -20);

		sig_out_Phase[k] = atan(sig_src_ImX[k] / sig_src_ReX[k]);

		if((sig_src_ReX[k] < 0) && (sig_src_ImX[k] < 0)) 
			sig_out_Phase[k] -= PI;

		if((sig_src_ReX[k] < 0) && (sig_src_ImX[k] >= 0)) 
			sig_out_Phase[k] += PI;

	}
	
}

// 5.
void polar_to_rect_conversion( 
	float32_t* sig_out_ReX,     // [out]
	float32_t* sig_out_ImX,     // [out]
	float32_t* sig_src_Mag,     // [in]
	float32_t* sig_src_Phase,   // [in]
	uint32_t   sig_src_length   // [in]
){
	
	for(int k = 0; k < sig_src_length; k++) {

		sig_out_ReX[k] = sig_src_Mag[k] * cosf(sig_src_Phase[k]);
		sig_out_ImX[k] = sig_src_Mag[k] * sinf(sig_src_Phase[k]);
	}
	
}



/////////////////////

void SysTick_Handler(void){
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
	
}

