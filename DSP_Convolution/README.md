
<!-- 
<img src="https://latex.codecogs.com/gif.latex?" /> 

<img src="https://render.githubusercontent.com/render/math?math=e^{i \pi} = -1">
-->

<!-- 

<img src="https://render.githubusercontent.com/render/math?math=\LARGE XXX" />

--> 

# Convolution

<img src="https://render.githubusercontent.com/render/math?math=\LARGE y[n] = \sum^{\infty}_{i = - \infty} x[i]h[n - i]" />


```c
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
            sig_dest[i + j] += (sig_src[i] * imp_resp[i]);
        }
    }
}
```











###### tags: `ARM` `Electrical Engineering` `DSP`
