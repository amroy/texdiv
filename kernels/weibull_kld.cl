__kernel void weibull_kld(__global const double *models, __global double *divs, int M, int D) {
 
    // Get the index of the current element to be processed
    int idx = get_global_id(0);
    int i = idx % D; // The current row
    int j = idx / D; // The current column
    double a1, b1, a2, b2, div = 0, I1, I2, lambda = 0.577;

    /**
     * The weibull model is coded as follows {a00 b00 a01 b01 a02 b02 ... aij bij ... aLJ bLJ}
     * with i the scale index and j the subband index.
     */
    for (int k=0; k<D; k++) {
    	a1 = models[i + k*D]; b1 = models[i + (k+1)*D];
    	a2 = models[j + k*D]; b2 = models[j + (k+1)*D];
    	div += pow(b1/b2, a2)*tgamma(a2/a1 + 1) + log(a1/(pow(b1,a1)))
            - log(a2/pow(b2,a2)) + log(b1)*a1 - log(b1)*a2 + lambda*a2/a1 - lambda - 1;
    }
 
    divs[idx] = div;
}
