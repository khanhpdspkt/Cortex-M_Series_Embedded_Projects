# Rectangular to Polar Conversion

<!-- 

<img src="https://render.githubusercontent.com/render/math?math=\LARGE XXX" />

-->




```c

void rect_to_polar_conversion( 
	float32_t* sig_src_ReX,     // [in]
	float32_t* sig_src_ImX,     // [in]
	float32_t* sig_out_Mag,     // [out]
	float32_t* sig_out_Phase,   // [out]
	uint32_t   sig_src_length   // [in]
){
	
	for(int k = 0; k < sig_src_length; k++) {

		sig_out_Mag[k] = sqrt(powf(sig_src_ReX[k], 2) + powf(sig_src_ImX[k], 2));

		if(sig_src_ReX[k] == 0) 
			sig_src_ReX[k] = pow(10, -20);

		sig_out_Phase[k] = atan(sig_src_ImX[k] / sig_src_ReX[k]);

		if((sig_src_ReX[k] < 0) && (sig_src_ImX[k] < 0)) 
			sig_out_Phase[k] -= PI;

		if((sig_src_ReX[k] < 0) && (sig_src_ImX[k] >= 0)) 
			sig_out_Phase[k] += PI;

	}
	
}


void polar_to_rect_conversion( 
	float32_t* sig_out_ReX,     // [out]
	float32_t* sig_out_ImX,     // [out]
	float32_t* sig_src_Mag,     // [in]
	float32_t* sig_src_Phase,   // [in]
	uint32_t   sig_src_length   // [in]
){
	
	for(int k = 0; k < sig_src_length; k++) {

		sig_out_ReX[k] = sig_src_Mag[k] * cosf(sig_src_Phase[k]);
		sig_out_ImX[k] = sig_src_Mag[k] * sinf(sig_src_Phase[k]);
	}
	
}
```














###### tags: `ARM` `Electrical Engineering` `DSP`
