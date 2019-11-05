#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "arm_math.h"                   // ARM::CMSIS:DSP

#define	SIGNAL_LEN       200
#define	ECG_LENGTH       640

// signals
extern void SystemClock_Config(void);
extern float32_t inputSignal_f32_1kHz_15kHz[SIGNAL_LEN];
extern float32_t _640_points_ecg_[640];

float32_t output_signal_ReX[SIGNAL_LEN / 2];
float32_t output_signal_ImX[SIGNAL_LEN / 2];

float32_t ecg_REX[ECG_LENGTH / 2];
float32_t ecg_IMX[ECG_LENGTH / 2];

float32_t idft_output_sig[ECG_LENGTH];


// prototypes
void plot_input_signal(void);
void plot_both_signal(void);
void plot_ecg_signal(void);
void plot_ecg_rex_signal(void);
void get_ecg_dft_output_mag(void);
void plot_ecg_idft_signal(void);
void plot_original_sig_and_idft_sig(void);
void plot_rex_signal(void);
void get_dft_output_mag(void);

// placeholder
float32_t inputSample;
float32_t rexSample;
float32_t imxSample;
float32_t ecgSample;
float32_t ecg_rexSample;
float32_t idft_output_ecgSample;


void calc_sig_dft(float32_t* sig_src, float32_t* sig_dest_ReX, float32_t* sig_dest_ImX, uint32_t sig_src_length);
void calc_sig_idft(float32_t* idft_out, float32_t* sig_src_ReX, float32_t* sig_src_ImX, uint32_t idft_length);



uint32_t freq;

int main()
{
	HAL_Init();
	SystemClock_Config();
	freq = HAL_RCC_GetHCLKFreq();

	plot_ecg_signal();

	// calc_sig_dft(_640_points_ecg_, ecg_REX, ecg_IMX, ECG_LENGTH);
	// calc_sig_idft(idft_output_sig, ecg_REX, ecg_IMX, ECG_LENGTH);

	// plot_original_sig_and_idft_sig();


	while(1){}
		
}


// 1.
void calc_sig_idft(
	float32_t* idft_out,     
	float32_t* sig_src_ReX,
	float32_t* sig_src_ImX,
	uint32_t   idft_length
){
	
	for(int k = 0; k < (idft_length / 2); k++) {
		sig_src_ReX[k] =  sig_src_ReX[k] / (idft_length / 2);
		sig_src_ImX[k] = -sig_src_ImX[k]/ (idft_length / 2);
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

			idft_out[i] =  idft_out[i] + sig_src_ReX[k]*cos(2*PI*k*i / idft_length);
			idft_out[i] =  idft_out[i] + sig_src_ImX[k]*sin(2*PI*k*i / idft_length);

		}
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
						
					  for(int j = 0; j < 5000; j++) {}
        }

    }
}

// 3. 
void get_dft_output_mag(void) {
    for(int k = 0; k < SIGNAL_LEN / 2; k++)
        output_signal_ReX[k] = fabs(output_signal_ReX[k]); //  absolute value of float
}

// 4.
void get_ecg_dft_output_mag(void) {
	for(int k = 0; k < (ECG_LENGTH/2); k++){
		ecg_REX[k] = fabs(ecg_REX[k]);
	}
}

// 5.
void plot_ecg_signal(void) {

	int i,j;
	for(i = 0; i < ECG_LENGTH; i++)
	{
		ecgSample = _640_points_ecg_[i];
		for(j = 0; j < 3000; j++){}
			if(i == ECG_LENGTH - 1) i=0;
	}
}

// 6.
void plot_ecg_idft_signal(void) {
	int i,j;
	for(i = 0; i < ECG_LENGTH; i++)
	{
		idft_output_ecgSample  = idft_output_sig[i];
		for(j = 0; j < 6000; j++){}
			if(i == ECG_LENGTH - 1) i = 0;
	}
}

// 7.
void plot_original_sig_and_idft_sig(void) {

	int i,j;
	for(i = 0; i < ECG_LENGTH; i++)
	{
		idft_output_ecgSample  = idft_output_sig[i];
		ecgSample  = _640_points_ecg_[i];

		for(j = 0; j < 6000; j++){}
			if(i == ECG_LENGTH - 1) i = 0;
	}
}

// 8.
void plot_ecg_rex_signal(void) {

	int i,j;
	for(i = 0; i < (ECG_LENGTH / 2); i++)
	{
		ecg_rexSample = ecg_REX[i];
		for(j=0;j<3000;j++){}
	}
}

// 9.
void plot_rex_signal(void) {

	int i,j;
	for(i = 0; i < (SIGNAL_LEN / 2); i++)
	{
		rexSample = output_signal_ReX[i];
		for(j = 0; j < 3000; j++){}
	}
}




/////////////////////

void SysTick_Handler(void){
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
	
}

