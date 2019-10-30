#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "arm_math.h"                   // ARM::CMSIS:DSP

#define SIG_LENGTH      320
#define NUM_TAPS        29
#define BLOCK_SIZE      32

uint32_t freq;

extern void SystemClock_Config(void);
extern float32_t inputSignal_f32_1kHz_15kHz[SIG_LENGTH];
void plot_Sin_wave(void);
void plot_output_signal(void);
void plot_both(void);

// Variable for logic analyzer
float32_t inputSample;
float32_t outputSample;


/// FIR Low-pass filter
/// Given Coeff
const float32_t firCoeffs32[NUM_TAPS] = {
    -0.0018225230f, -0.0015879294f, +0.0000000000f, +0.0036977508f, +0.0080754303f, +0.0085302217f, -0.0000000000f, -0.0173976984f,
    -0.0341458607f, -0.0333591565f, +0.0000000000f, +0.0676308395f, +0.1522061835f, +0.2229246956f, +0.2504960933f, +0.2229246956f,
    +0.1522061835f, +0.0676308395f, +0.0000000000f, -0.0333591565f, -0.0341458607f, -0.0173976984f, -0.0000000000f, +0.0085302217f,
    +0.0080754303f, +0.0036977508f, +0.0000000000f, -0.0015879294f, -0.0018225230f
};

static float32_t firState_f32[BLOCK_SIZE + NUM_TAPS - 1];

const uint32_t NUM_OF_BLOCKs = SIG_LENGTH / BLOCK_SIZE;

float32_t outputSignal_f32[SIG_LENGTH];



int main (void) {

    HAL_Init();
    SystemClock_Config();
    freq = HAL_RCC_GetHCLKFreq();



/// FIR Low-pass filter
// ARM DSP API
// 1. Create fir object
    arm_fir_instance_f32 _1Khz_Khz_sig;
// 2. Initialize
    arm_fir_init_f32(
                &_1Khz_Khz_sig,               // points to an instance of the floating-point FIR filter structure
                NUM_TAPS,                     // number of filter coefficients in the filter
                (float32_t *)&firCoeffs32[0], // points to the filter coefficients buffer
                &firState_f32[0],             // points to the state buffer
                BLOCK_SIZE                    // number of samples processed per call
                );
// 3. Calculate 
    for(int i = 0; i < NUM_OF_BLOCKs; i++) {
        arm_fir_f32(
            &_1Khz_Khz_sig, 
                &inputSignal_f32_1kHz_15kHz[0] + (i * BLOCK_SIZE), // filter out block by block
                &outputSignal_f32[0] + (i * BLOCK_SIZE),           // store output block by block
                BLOCK_SIZE
                );
    }


// plot_Sin_wave();
// plot_output_signal();
    plot_both();

    while(1) {};
}

void plot_Sin_wave(void) {
    int i = 0, j;

    while(1) {

        inputSample = inputSignal_f32_1kHz_15kHz[i];
for(j = 0; j < 3000; j++) {}; // delay

    i = (i == SIG_LENGTH - 1) ? 0 : i + 1;
}
}


void plot_output_signal (void) {
    int i = 0, j;

    for(i = 0; i < SIG_LENGTH; i++) {
        outputSample = outputSignal_f32[i];

        for(j = 0; j < 3000; j++) {}

    }
}

void plot_both(void) {
    int i, j;

    for(i = 0; i < SIG_LENGTH; i++) {
        inputSample = inputSignal_f32_1kHz_15kHz[i];
        outputSample = outputSignal_f32[i];

        for(j = 0; j < 8000; j++) {}
//if(i == SIG_LENGTH - 1) i = 0;
    }
}

void SysTick_Handler(void) {
    HAL_IncTick();
    HAL_SYSTICK_IRQHandler();
}
