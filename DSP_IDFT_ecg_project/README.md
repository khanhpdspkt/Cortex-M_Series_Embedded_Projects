# DFT and IDFT Algorithms for ECG Signal 

> [DSP_Discrete_Fourier_Transform](https://github.com/syokujinau/Cortex-M_Series_Embedded_Projects/tree/master/DSP_Discrete_Fourier_Transform)

 
![](https://i.imgur.com/zw35rNm.png) 

Implement DFT and IDFT algorithm, input an ECG signal in DFT to produce frequency domain signal and use IDFT to get the original ecg signal back.

## DFT

```c
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
```

Magnitude of real part frequency domain signal

![](https://i.imgur.com/fqJGsBo.png)
