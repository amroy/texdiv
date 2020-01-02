#version 400

in vec2 st;

uniform float		M; // Number of models
uniform float		D; // Number of features in each model
uniform sampler2D	models;

out vec4 FragColor;
  
#define PI      3.14159265358979324  /* $\pi$ */
#define LOG_2PI 1.83787706640934548  /* $\log 2\pi$ */
#define N       8

#define B0  1                 /* Bernoulli numbers */
#define B1  (-1.0 / 2.0)
#define B2  ( 1.0 / 6.0)
#define B4  (-1.0 / 30.0)
#define B6  ( 1.0 / 42.0)
#define B8  (-1.0 / 30.0)
#define B10 ( 5.0 / 66.0)
#define B12 (-691.0 / 2730.0)
#define B14 ( 7.0 / 6.0)
#define B16 (-3617.0 / 510.0)

float loggamma(float x)  /* the natural logarithm of the Gamma function. */
{
    double v, w;

    v = 1;
    while (x < N) {  v *= x;  x++;  }
    w = 1 / (x * x);
    return ((((((((B16 / (16 * 15))  * w + (B14 / (14 * 13))) * w
                + (B12 / (12 * 11))) * w + (B10 / (10 *  9))) * w
                + (B8  / ( 8 *  7))) * w + (B6  / ( 6 *  5))) * w
                + (B4  / ( 4 *  3))) * w + (B2  / ( 2 *  1))) / x
                + 0.5 * LOG_2PI - log(v) - x + (x - 0.5) * log(x);
}

//float tgamma(float x)  /* Gamma function */
//{
//    if (x == 0.0) { /* Pole Error */
//        errno = ERANGE;
//        return 1/x < 0 ? -HUGE_VAL : HUGE_VAL;
//    }
//    if (x < 0) {
//        int sign;
//        float zero = 0.0f;
//        double i, f;
//        f = modf(-x, &i);
//        if (f == 0.0) { /* Domain Error */
//            errno = EDOM;
//            return zero/zero;
//        }
//        sign = (fmod(i, 2.0) != 0.0) ? 1 : -1;
//        return sign * PI / (sin(PI * f) * exp(loggamma(1 - x)));
//    }
//    return exp(loggamma(x));
//}

void main()  
{
//	float dx = 1.0 / D;
//	float dy = 1.0 / M;
//    int i = (int) (st.x / dy); // The current row
//    int j = (int) (st.y / dy); // The current column
//    float a1, b1, a2, b2, d = 0.0f, lambda = 0.577f;

    /**
     * The weibull model is coded as follows {a00 b00 a01 b01 a02 b02 ... aij bij ... aLJ bLJ}
     * with i the scale index and j the subband index.
     */
//    for (int k=0; k<D; k++) {
//    	a1 = texture2D(models, vec2(st.x, k*dx);
//    	b1 = texture2D(models, vec2(st.x, (k+1)*dx);
//    	a2 = texture2D(models, vec2(st.y, k*dx);
//    	b2 = texture2D(models, vec2(st.y, (k+1)*dx);
//    	d += pow(b1/b2, a2)*tgamma(a2/a1 + 1) + log(a1/(pow(b1,a1)))
//            - log(a2/pow(b2,a2)) + log(b1)*a1 - log(b1)*a2 + lambda*a2/a1 - lambda - 1;
//    }

//    int test = (int) d * 256.0f * 256.0f;
//    float A = float(1.0) / 255.0;
//	float B = float((test) % 256) / 255.0;
//	float G = float((test / 256) % 256) / 255.0;
//	float R = float(test / 256 / 256) / 255.0;

	FragColor = vec4(12.0f, 0.0f, 0.0f, 1.0f);
}  