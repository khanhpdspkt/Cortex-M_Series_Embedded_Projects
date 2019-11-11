# DFT and IDFT Algorithms for ECG Signal 

> [DSP_Discrete_Fourier_Transform](https://github.com/syokujinau/Cortex-M_Series_Embedded_Projects/tree/master/DSP_Discrete_Fourier_Transform)

 
![](https://i.imgur.com/zw35rNm.png) 

Implement DFT and IDFT algorithm, input an ECG signal in DFT to produce frequency domain signal and use IDFT to get the original ecg signal back.



## DFT

<img src="https://render.githubusercontent.com/render/math?math=\LARGE X[k] = \sum^{N - 1}_{n=0}x[n] \cdot e^{-j\frac{2 \pi kn}{N}} = \sum^{N - 1}_{n=0}x[n] \cdot [cos(\frac{2 \pi kn}{N}) - j \cdot sin(\frac{2 \pi kn}{N})]" /><br/><br/>

```c
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
```

**Magnitude** of real part frequency domain signal

![](https://i.imgur.com/fqJGsBo.png)


## IDFT

<img src="https://render.githubusercontent.com/render/math?math=\LARGE x[i] = \sum^{N/2}_{k=0}Re\bar{X}[k] cos({\color{Orange} \frac{2\pi ki}{N}}) %2B \sum^{N/2}_{k=0}Im\bar{X}[k] sin({\color{Orange} \frac{2\pi ki}{N}}), 0 \leq i \leq N -1" /> <br/><br/>

<img src="https://render.githubusercontent.com/render/math?math=Re\bar{X}[k]" /> stands for cosine wave amplitude
* <img src="https://render.githubusercontent.com/render/math?math=Re\bar{X}[k] = \frac{ReX[k]}{N/2}" /><br/>
    * <img src="https://render.githubusercontent.com/render/math?math=Re\bar{X}[0] = \frac{ReX[k]}{N}" />
* <img src="https://render.githubusercontent.com/render/math?math=Im\bar{X}[k] = \frac{ImX[k]}{N/2}" /><br/>
    * <img src="https://render.githubusercontent.com/render/math?math=Im\bar{X}[0] = \frac{ImX[k]}{N}" />


```c
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
	
	for(int i = 0; i < idft_length; i++) {
		idft_out[i] = 0;
	}
	
	for(int k = 0; k < (idft_length / 2); k++) {
		for(int i = 0; i < idft_length; i++) {

			idft_out[i] =  idft_out[i] + sig_src_ReX[k] * cos(2*PI*k*i / idft_length);
			idft_out[i] =  idft_out[i] + sig_src_ImX[k] * sin(2*PI*k*i / idft_length);

		}
	}
}
```

![](https://i.imgur.com/9XXNfNR.png)


<!-- 

<img src="https://render.githubusercontent.com/render/math?math=\LARGE XXX" />

-->



















###### tags: `ARM` `Electrical Engineering` `DSP`