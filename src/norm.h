#ifndef NORM_H
#define NORM_H

#include <math.h>

#include "compact3.h"

double L1(data_t *d1, data_t *d2)
{
	// WARNING: no size check
	int i, N = d1->m->size;
	double n = 0.0;
	double ne = 0.0;
	for (i = 0; i < N; i++) {
		int i1 = ((i + N)-1) % N;
		int i2 = ((i + N)+1) % N;
		double dx = (d1->m->x[i2] - d1->m->x[i1]) / 2.0;
		//printf("%f\n", dx);
		n += ABS(d1->u[i] - d2->u[i]);
	}
	return n;
}

double L2(data_t *d1, data_t *d2)
{
	// WARNING: no size check
	int i, N = d1->m->size;
	double n = 0.0;
	double ne = 0.0;
	for (i = 0; i < N; i++) {
		int i1 = ((i + N)-1) % N;
		int i2 = ((i + N)+1) % N;
		double dx = (d1->m->x[i2] - d1->m->x[i1]) / 2.0;
		double du = d1->u[i] - d2->u[i];
		n += du * du;
	}
	return sqrt(n);
}

double Linf(data_t *d1, data_t *d2)
{
	// WARNING: no size check
	int i, N = d1->m->size;
	double n = 0.0;
	for (i = 0; i < N; i++) {
		double du = d1->u[i] - d2->u[i];
		double v = ABS(du);
		if (n < v) n = v;
	}
	return n;
}

#endif // NORM_H
