# Moving Average Filters

<!-- 
<img src="https://latex.codecogs.com/gif.latex?" /> 

<img src="https://render.githubusercontent.com/render/math?math=e^{i \pi} = -1">
-->

<!-- 

<img src="https://render.githubusercontent.com/render/math?math=\LARGE XXX" />

-->


<img src="https://render.githubusercontent.com/render/math?math=\LARGE y[i] = \frac{1}{M} \sum^{M-1}_{j = 0} x[i %2B j]" /><br/>

* <img src="https://render.githubusercontent.com/render/math?math=\large x[i]" />: Input signal
* <img src="https://render.githubusercontent.com/render/math?math=\large y[i]" />: Output signal
* <img src="https://render.githubusercontent.com/render/math?math=\large M" />: Numbers of points

e.g.

Point 50 in a **5-point** moving average

<img src="https://render.githubusercontent.com/render/math?math=\large y[50] = \frac{x[50] %2B x[51] %2B x[52] %2B x[53] %2B x[54]}{5}" /><br/>



Frequency reponse of the Moving Average Filter

<img src="https://render.githubusercontent.com/render/math?math=\LARGE H[f] = \frac{sin(\pi fM)}{Msin(\pi f)}" /><br/>
 

* <img src="https://render.githubusercontent.com/render/math?math=\large M" />: Numbers of points
* <img src="https://render.githubusercontent.com/render/math?math=\large f" />: Runs between 0 and 0.5
    * <img src="https://render.githubusercontent.com/render/math?math=\large H[f] = 1" /> if <img src="https://render.githubusercontent.com/render/math?math=\large f=0" />


![](https://i.imgur.com/xPM2alR.png)



```c
void moving_average(
	float32_t* sig_src,       // [in]
	float32_t* sig_dest,      // [out]
	uint32_t   signal_length, // [in]
	uint32_t   filter_points  // [in]
) {
	int i, j;
	for(i = floor(filter_points / 2); i < (signal_length - (filter_points / 2)) - 1; i++) {

		sig_dest[i] = 0;

		for(j = -(floor(filter_points / 2)); j < floor(filter_points / 2); j++) {
			sig_dest[i] += sig_src[i + j];
		}

		sig_dest[i] /= filter_points; 
	}

}
```






















































###### tags: `ARM` `Electrical Engineering` `DSP`
