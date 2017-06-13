#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <errno.h>

#define PI 3.1415926535897f

#ifndef LOOPCOUNT
#define LOOPCOUNT 1000
#endif

#ifndef API
#define API sinf
#define APINAME "sinf"
#endif

/*
 * Read the PMU cycles counter
 */
static inline uint64_t
rte_rdtsc(void)
{
	uint64_t tsc;
	asm volatile("mrs %0, pmccntr_el0" : "=r"(tsc));
	return tsc;
}

#define PRINTCYCLES(ARG)					\
	do {							\
		uint64_t start, stop;				\
		float t = ARG;					\
		int i = LOOPCOUNT;				\
								\
		start = rte_rdtsc();				\
		/* Run the API for LOOPCOUNT iterations */	\
		while (i--)					\
			API(t);					\
		stop = rte_rdtsc();				\
								\
		printf("%10s %15s\t=%0.2lf\n", APINAME, #ARG,	\
			(double)(stop - start)/LOOPCOUNT);	\
	} while(0)


int main()
{
	float pio4, pio8;
	float zero, twopown28, twopown6, pio4xpt6, pio8x13, pio8x17;
	float pio4x1000, twopow51;
	float inf, nan;

	/* Initialize the values */
	zero = 0.0f;
	pio8 = PI / 8.0f;
	pio4 = PI / 4.0f;
	twopown28 = powf(2.0f, -28.0f);
	twopown6 = powf(2.0f, -6.0f);
	pio4xpt6 = 0.6f * pio4;
	pio8x13 = 13.0f * pio8;
	pio8x17 = 17.0f * pio8;
	pio4x1000 = 1000.0f * pio4;
	twopow51 = powf(2.0f, 51.0f);
	inf = INFINITY;
	nan = NAN;

	/* Warmup */
	API(zero);
	API(twopown28);
	API(twopown6);
	API(pio4xpt6);
	API(pio8x13);
	API(pio8x17);
	API(pio4x1000);
	API(twopow51);
	API(inf);
	API(nan);

	/* Start Benchmarking */
	PRINTCYCLES(zero);
	PRINTCYCLES(twopown28);
	PRINTCYCLES(twopown6);
	PRINTCYCLES(pio4xpt6);
	PRINTCYCLES(pio8x13);
	PRINTCYCLES(pio8x17);
	PRINTCYCLES(pio4x1000);
	PRINTCYCLES(twopow51);
	PRINTCYCLES(inf);
	PRINTCYCLES(nan);

	return 0;
}
