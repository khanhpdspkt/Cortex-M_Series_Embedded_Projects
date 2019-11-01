#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "arm_math.h"                   // ARM::CMSIS:DSP
#include "low_pass_filter.h"
#include "sine_generator.h"
#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX


// Thread IDs
osThreadId sineId, noiseId, disturbedId, filteredId, syncId;


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

// Thread handler prototypes
void sine_thread(void const *argument);
void noise_thread(void const *argument);
void disturbed_thread(void const *argument);
void filtered_thread(void const *argument);
void sync_thread(void const *argument);

// Thread definition
osThreadDef(sine_thread, osPriorityNormal, 1, 0);
osThreadDef(noise_thread, osPriorityNormal, 1, 0);
osThreadDef(disturbed_thread, osPriorityNormal, 1, 0);
osThreadDef(filtered_thread, osPriorityNormal, 1, 0);
osThreadDef(sync_thread, osPriorityNormal, 1, 0);

// 
uint32_t t;

int main() {
	
	HAL_Init();
	SystemClock_Config();
	
	freq = HAL_RCC_GetHCLKFreq();

	// 1.
	sine_generator_init_q15(&signal_set, SIGNAL_FREQ, SAMPLING_FREQ);
	sine_generator_init_q15(&noise_set, NOISE_FREQ, SAMPLING_FREQ);

	// 2.
	low_pass_filter_init();

	// 3. Create threads
	sineId      = osThreadCreate(osThread(sine_thread), NULL);
	noiseId     = osThreadCreate(osThread(noise_thread), NULL);
	disturbedId = osThreadCreate(osThread(disturbed_thread), NULL);
	filteredId  = osThreadCreate(osThread(filtered_thread), NULL);
	syncId      = osThreadCreate(osThread(sync_thread), NULL);

	
	while(1) {}

}


void SysTick_Handler(void) {
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

// thread handlers
void sine_thread(void const *argument) {

	while(1) {
		osSignalWait(
			        0x0001, // wait until all specified signal flags set or 0 for any single signal flag.
					0       // timout value or 0 in case of no time-out.
					);
		osDelay(t);
		sine  = sine_calc_sample_q15(&signal_set) / 2;
	}

}

void noise_thread(void const *argument) {

	while(1) {
		osSignalWait(0x0001, 0);
		osDelay(t);
		noise = sine_calc_sample_q15(&noise_set) / 6;
	}

}

void disturbed_thread(void const *argument) {

	while(1) {
		osSignalWait(0x0001, 0);
		osDelay(t);
		disturbed = sine + noise;
	}

}

void filtered_thread(void const *argument) {

	while(1) {
		osSignalWait(0x0001, 0);
		osDelay(t);
		filtered = low_pass_filter(&disturbed);
	}

}

void sync_thread(void const *argument) {

	while(1) {
		osDelay(t);
		osSignalWait(0x0001, 0);
		osSignalSet(sineId, 0x0001);
	}

}
