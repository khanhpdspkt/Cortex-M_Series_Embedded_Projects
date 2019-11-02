# Signal Statistics and Noise

## Mean and Standard Deviation

* Mead 平均數
    * $\mu = \frac{1}{N}\sum^{N-1}_{i=0}x_i = \frac{x_0 + x_1 + \dots + x_{N-1}}{N}$
    * 物理意義: DC signal (Direct current) 直流分量
* Deviation
    * $i$ deviates from the mean: $|x_i - \mu|$
    * Average deviation: $\frac{1}{N-1}\sum^{N-1}_{i=0}|x_i - \mu|$
    * 物理意義: 訊號樣本點與平均之距離
* Standard Deviation 標準差
    * ${\color{Red} P} \propto {\color{Orange} V^{{\color{Orange}2}}}$
    * ${\color{Red} \sigma} = R.M.S = \sqrt{\frac{1}{N-1}\sum^{N-1}_{i=0}(x_i - {\color{Orange} \mu})^{\color{Orange} 2}}$
    * 物理意義: 顯示單一個測量值(電壓)與平均值間可能偏差的程度(功率)
* Variance 變異數
    * ${\color{Red} \sigma^{\color{Red}2}}$ = $\frac{1}{N-1}\sum^{N-1}_{i=0}(x_i - {\color{Orange} \mu})^{\color{Orange} 2}$
    * 物理意義: 描述訊號的波動範圍，表示訊號中交流分量的強弱，即交流訊號的平均功率
* Signal ro Noise ratio (SNR)
    * $SNR = \frac{\mu}{\sigma}$
* Coefficient of Variation
    * $CV = \frac{\mu}{\sigma} \times 100$

### Implementation

```c
float32_t signal_mean(float32_t *signal_src, uint32_t signal_length) {
    float32_t mean = 0.0;
    uint32_t i;
    for(i = 0; i < signal_length; i++) {
        mean = mean + signal_src[i];
    }
    mean /= (float32_t)signal_length;
    
    return mean;
}
```

```c
float32_t signal_variance(float32_t *signal_src, uint32_t signal_length, float32_t signal_mean) {
    
    float32_t variance = 0.0;
    uint32_t i;
    for(i = 0; i < signal_length; i++) {
        variance = variance + pow((signal_src[i] - signal_mean), 2);
    }
    variance /= (signal_length - 1);
    
    return variance;
}
```
```c
float32_t signal_standard_deviation (float32_t signal_variance) {
    float32_t std = sqrtf(signal_variance);
    
    return std;
}
```


> CMSIS為DSP應用處理數值(多使用`float32_t`等浮點數)，並最佳化，例如用迴圈做320樣本點`float32_t`訊號做平均數計算常常無法算出，使用函式庫則能做高效率的運算。


### ARM Math APIs

* `arm_mean_f32`
* `arm_var_f32`
* `arm_std_f32`


## ADC

ADC consists of **Sample/Hold** and **Quantizer** to convert analog to digital.
* Sample/Hold: convert independent variable of signal from continuous to discrete 
* Quantizer: convert dependent variable of signal from continuous to discrete

### Sampling theorem

Reconstructing original analog signal from sample points, the sample rate must satisfy $f_s \geq 2f_{max}$, also called Nyquist theorem.





###### tags: `ARM` `Electrical Engineering` `DSP`
