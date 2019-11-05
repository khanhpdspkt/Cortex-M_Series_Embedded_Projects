#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "arm_math.h"                   // ARM::CMSIS:DSP

#define SIGNAL_LEN           320

extern void SystemClock_Config(void);

// Signals and impules response
// 1. input
extern float32_t inputSignal_f32_1kHz_15kHz[SIGNAL_LEN];
// 2. output 
float32_t output_signal_ReX[SIGNAL_LEN / 2];
float32_t output_signal_ImX[SIGNAL_LEN / 2];

uint32_t freq;

// placeholder
float32_t inputSample, 
          output_signal_ReXSample;

// prototypes
void plot_input_signal(void);
void calc_sig_dft(float32_t* sig_src, float32_t* sig_dest_ReX, float32_t* sig_dest_ImX, uint32_t sig_src_length);
void plot_output_signal(void);
void plot_ReX(void);
void get_dft_output_mag(void);

int main() {

    HAL_Init();
    SystemClock_Config();
    freq = HAL_RCC_GetHCLKFreq();
    
    //
    plot_input_signal();
    
	  calc_sig_dft(
        (float32_t*) inputSignal_f32_1kHz_15kHz, 
        (float32_t*) output_signal_ReX, 
        (float32_t*) output_signal_ImX, 
        (uint32_t)   SIGNAL_LEN
    );

    // get_dft_output_mag();

    plot_ReX();
    
    
    while(1) {
        
    }
}



// 1.
void plot_input_signal(void) {
    
    int i, j;
    for(i = 0; i < SIGNAL_LEN; i++) {
        inputSample = inputSignal_f32_1kHz_15kHz[i];
        for(j = 0; j < 5000; j++) {};
    }

}

// 2.
void calc_sig_dft(
    float32_t* sig_src,       // [in]
    float32_t* sig_dest_ReX,  // [out]
    float32_t* sig_dest_ImX,  // [out]
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

void get_dft_output_mag(void) {
    int k = 0;
    for(k = 0; k < SIGNAL_LEN / 2; k++)
        output_signal_ReX[k] = fabs(output_signal_ReX[k]); //  absolute value of float
}

// 3.
void plot_ReX(void) {
    int i, j;
    for(i = 0; i < SIGNAL_LEN / 2; i++) {
        output_signal_ReXSample = output_signal_ReX[i];
        for(j = 0; j < 5000; j++) {}
    }
}

///// end 

void SysTick_Handler(void) {
    HAL_IncTick();
    HAL_SYSTICK_IRQHandler();
}




