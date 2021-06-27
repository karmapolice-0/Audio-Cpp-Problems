#include <x86intrin.h>
#include <emmintrin.h>
#include <cstdio>
#include <cmath>
#include <time.h>

/**
 * Разностное уравнение КИХ фильтра:
 * out[j] = sum(H[i] * in[j + i]) i = 0 to m
 * Ких фильтр порядка N имеет N+1 коэф.
 * Длина импульсной хар-ки = кол-во коэф.
*/
constexpr double PI = 3.14159265358979323846f;

void filter()
{
    clock_t t = clock();
    int sizeIn = 180;
    int N = 20;

    double H[] = {-0.000000, 0.000357, 0.001565, 0.003931, 0.007688, 0.012719, 
			0.018426, 0.023798, 0.027699, 0.029231, 0.028045, 0.024457, 0.019322,
			0.013737, 0.008690, 0.004800, 0.002235, 0.000807, 0.000166, -0.0000000};
    double out[sizeIn];
    double in[sizeIn];
    for (int i = 0; i < sizeIn; i++)
        in[i] = sin(2 * PI * i);
    
    // Фильтрация
    for (int j = 0; j < sizeIn; j++)
    {
        double s = 0;
        for (int i = 0; i < N; i++)
            if (i > j)
                s += H[i] * in[i - j];
        out[j] = s;
    }
    t = clock() - t;
    printf("Without SIMD: %li clocks\n", t);
}

void simd_filter()
{
    clock_t t;
	t = clock();

	int sizeIn = 180;
	int N = 20;
	//коэффициенты фильтра
	double H[] = {-0.000000, 0.000357, 0.001565, 0.003931, 0.007688, 0.012719, 
			0.018426, 0.023798, 0.027699, 0.029231, 0.028045, 0.024457, 0.019322,
			0.013737, 0.008690, 0.004800, 0.002235, 0.000807, 0.000166, -0.0000000};

	__m128d m_out[sizeIn];
    double in[sizeIn];
	for (int i = 0; i <= sizeIn; i++)
		in[i] = sin(2 * PI * i);


	for (int j = 0; j < sizeIn; j++)
    {
		__m128d s = _mm_set_pd1(0);
		for (int i = 0; i <= N; i++)
			if (i > j)
            {
			    __m128d p0= _mm_loadu_pd(&H[i]);
			    __m128d p1= _mm_loadu_pd(&in[i - j]);
			    s =_mm_add_pd(s, _mm_mul_pd(p0, p1));
		    }
        
		m_out[j] = s;
	}
	t = clock() - t;
	printf("SIMD: %li clocks\n", t);
}

int main()
{
    filter();
    simd_filter();
    return 0;
}