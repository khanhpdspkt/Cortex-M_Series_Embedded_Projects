<!-- 

<img src="https://render.githubusercontent.com/render/math?math=\LARGE XXX" />

-->

# Fourier Transform

![](https://i.imgur.com/1azPCn2.png)


|   | Time domain | frequency domain |
| -------- | -------- | -------- |
| Fourier Transfrom     | continuous, aperiodic     | continuous, aperiodic      |
| Fourier Series     | continuous, aperiodic <br/> (or continus, only the value in a finite duration is known)    | discrete, aperiodic       |
| Discrete Time Fourier Transfrom     | discrete, aperiodic     | continuous, periodic      |
| **Discrete Fourier Transfrom**     | discrete, aperiodic <br/> (or discrete, **only the value in a finite duration is known**)     | discrete, periodic      |



## Discrete Fourier Transfrom

![](https://i.imgur.com/11AypPZ.png)

> This is **real** DFT

<img src="https://render.githubusercontent.com/render/math?math=\LARGE X[k] = \sum^{N - 1}_{n=0}x[n] \cdot e^{-j\frac{2 \pi kn}{N}} = \sum^{N - 1}_{n=0}x[n] \cdot [cos(\frac{2 \pi kn}{N}) - j \cdot sin(\frac{2 \pi kn}{N})]" /><br/>

* The output of DFT is a set of **sine** and **cosine** waves with unity amplitude.
    * <img src="https://render.githubusercontent.com/render/math?math=ReX[k]" />: <img src="https://render.githubusercontent.com/render/math?math=C_{k}[i] = cos(\frac{2\pi ki}{N})" />
    * <img src="https://render.githubusercontent.com/render/math?math=ImX[k]" />: <img src="https://render.githubusercontent.com/render/math?math=S_{k}[i] = sin(\frac{2\pi ki}{N})" />

e.g.

* Input <img src="https://render.githubusercontent.com/render/math?math=N = 32" /> points signal, <img src="https://render.githubusercontent.com/render/math?math=DFT" /> will output
    1. <img src="https://render.githubusercontent.com/render/math?math=\frac{N}{2} %2B 1 = 17" /> cosine waves - <img src="https://render.githubusercontent.com/render/math?math=ReX[0], ReX[1], \cdots, ReX[16]" />
    2. <img src="https://render.githubusercontent.com/render/math?math=\frac{N}{2} %2B 1 = 17" /> sine waves - <img src="https://render.githubusercontent.com/render/math?math=ImX[0], ImX[1], \cdots, ImX[16]" />




### Inverse DFT (IDFT)

<br/><br/>

<img src="https://render.githubusercontent.com/render/math?math=\LARGE x[i] = \sum^{N/2}_{k=0}Re\bar{X}[k] cos({\color{Orange} \frac{2\pi ki}{N}}) %2B \sum^{N/2}_{k=0}Im\bar{X}[k] sin({\color{Orange} \frac{2\pi ki}{N}}), 0 \leq i \leq N -1" />

<br/><br/>

<img src="https://render.githubusercontent.com/render/math?math=Re\bar{X}[k]" /> means cosine wave amplitude
* <img src="https://render.githubusercontent.com/render/math?math=Re\bar{X}[k] = \frac{ReX[k]}{N/2}" /><br/>
    * <img src="https://render.githubusercontent.com/render/math?math=Re\bar{X}[0] = \frac{ReX[k]}{N}" />
* <img src="https://render.githubusercontent.com/render/math?math=Im\bar{X}[k] = \frac{ImX[k]}{N/2}" /><br/>
    * <img src="https://render.githubusercontent.com/render/math?math=Im\bar{X}[0] = \frac{ImX[k]}{N}" />



### DFT Implementation Methods

1. Simultaneous equations
2. **Correlation**
3. FFT - <img src="https://render.githubusercontent.com/render/math?math=\Theta (NlogN)" />



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










































###### tags: `ARM` `Electrical Engineering` `DSP`